#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crc32.h"
#include "items.h"
#include "lfsr.h"
#include "sg64.h"

typedef enum {
    RETURN_CODE_SUCCESS = 0,
    RETURN_CODE_INVALID_ARGS = 1,
    RETURN_CODE_INVALID_ROM = 2,
    RETURN_CODE_INVALID_MODE = 3,
    RETURN_CODE_INVALID_SEED = 4,
    RETURN_CODE_SHUFFLE_FAILED = 5,
    RETURN_CODE_WRITE_FAILED = 6,
} returnCode_t;

const long long int MAX_SEED = 0xffffffffll;

const uint32_t LOOKUP_TABLE_LOCATION = 0x800a0c00u;

extern item_t initialItems[BOOK_END];
extern const char itemNames[BOOK_END][32];
extern uint32_t initialSeed;

uint8_t * readAndConfirmRom(const char * const filename, char * titleIdentifier) {
    fprintf(stdout, "Reading ROM file...\n");

#ifdef _MSC_VER
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif
    FILE * file = fopen(filename, "rb");
#ifdef _MSC_VER
#pragma clang diagnostic pop
#endif

    if (!file) {
        fprintf(stderr, "Failed to open %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    uint32_t size = ftell(file);

    if (size != EXPECTED_SIZE) {
        fprintf(stderr, "Unexpected ROM file size: %u\n", size);
        fclose(file);
        return NULL;
    }

    uint8_t * rom = malloc(size);
    fseek(file, 0, SEEK_SET);
    if (fread(rom, 1, size, file) != size) {
        fprintf(stderr, "Failed to read %s\n", filename);
        fclose(file);
        free(rom);
        return NULL;
    }
    fclose(file);

    uint32_t headerMagic = swapBytes(rom);
    if (headerMagic != EXPECTED_HEADER_MAGIC) {
        fprintf(stderr, "Unrecognized header magic: 0x%08x\n", headerMagic);
        free(rom);
        return NULL;
    }

    uint32_t bootAddress = swapBytes(rom + 0x8);
    if (bootAddress != EXPECTED_BOOT_ADDRESS) {
        fprintf(stderr, "Unexpected boot address: 0x%08x\n", bootAddress);
        free(rom);
        return NULL;
    }

    findTitleIdentifier(rom, titleIdentifier);
    titleIdentifier[TITLE_IDENTIFIER_LENGTH] = '\0';

    if (strncmp(titleIdentifier, "NSG", 3) != 0) {
        fprintf(stderr, "Unrecognized title identifier: %s\n", titleIdentifier);
        free(rom);
        return NULL;
    }

    // TODO: Add support for other regions.
    if (titleIdentifier[OFFSET_CART_COUNTRY_CODE] != 'E') {
        fprintf(stderr, "Unsupported country code: %c\n", titleIdentifier[OFFSET_CART_COUNTRY_CODE]);
        free(rom);
        return NULL;
    }

    uint32_t expectedChecksum1;
    uint32_t expectedChecksum2;
    if (!getExpectedChecksums(titleIdentifier[OFFSET_CART_COUNTRY_CODE],
        &expectedChecksum1, &expectedChecksum2)) {

        fprintf(stderr, "Unrecognized country code: %c\n", titleIdentifier[OFFSET_CART_COUNTRY_CODE]);
        free(rom);
        return NULL;
    }

    uint32_t bootCodeCrc = crc32(rom + ROM_OFFSET_BOOT_CODE, BOOT_CODE_SIZE);
    if (bootCodeCrc != EXPECTED_BOOT_CODE_CRC) {
        fprintf(stderr, "Unrecognized boot code CRC: 0x%08x\n", bootCodeCrc);
        free(rom);
        return NULL;
    }

    uint32_t checksum1 = swapBytes(rom + ROM_OFFSET_CHECKSUM_1);
    uint32_t checksum2 = swapBytes(rom + ROM_OFFSET_CHECKSUM_2);
    if (checksum1 != expectedChecksum1 || checksum2 != expectedChecksum2) {
        fprintf(stderr, "Unrecognized ROM checksums: 0x%08x 0x%08x\n", checksum1, checksum2);
        free(rom);
        return NULL;
    }

    findChecksums(rom + CHECKSUM_DATA_OFFSET, CHECKSUM_DATA_SIZE, &checksum1, &checksum2);
    if (checksum1 != expectedChecksum1 || checksum2 != expectedChecksum2) {
        fprintf(stderr, "Mismatched ROM checksums: 0x%08x 0x%08x\n", checksum1, checksum2);
        free(rom);
        return NULL;
    }

    fprintf(stdout, "\t%s: 0x%08x 0x%08x\n", titleIdentifier, checksum1, checksum2);
    fprintf(stdout, "\tVerified ROM: %s\n\n", rom + ROM_OFFSET_NAME);
    return rom;
}

bool randomize(shuffleMode_t mode, uint32_t seed, itemId_t * shuffled) {
    fprintf(stdout, "Randomizing items...\n");

    preprocessItems(mode);

    item_t items[BOOK_END];
    memcpy(items, initialItems, BOOK_END * sizeof(item_t));
    qsort(items, BOOK_END, sizeof(item_t), compareItems);

    setSeed(seed);

    bool success = false;
    while (!success) {
        success = true;
        memset(shuffled, 0, BOOK_END * sizeof(itemId_t));

        for (int index = 0; index < BOOK_END; ++index) {
            if (!isValidItem(items[index].id) ||
                (mode == MODE_STATIC_BOOKS && isBook(items[index].id))) {

                shuffled[items[index].id] = items[index].id;
                continue;
            }

            bool placed = false;

            for (uint32_t t = 0u; !placed && t < UINT16_MAX; ++t) {
                uint8_t r = nextRandom();

                if (r >= items[index].numPossibilities) {
                    continue;
                }

                itemId_t shuffledIndex = items[index].possibleLocations[r];

                if ((mode == MODE_STATIC_BOOKS || mode == MODE_SHUFFLE_BOOKS_SEPARATELY) &&
                    (isItem(items[index].id) ^ isItem(shuffledIndex))) {

                    continue;
                }

                if (shuffled[shuffledIndex] == EMPTY) {
                    shuffled[shuffledIndex] = items[index].id;
                    placed = true;
                }
            }

            if (!placed) {
                fprintf(stdout, "\tid 0x%02x could not be placed with seed 0x%08x, retrying...\n",
                    items[index].id, initialSeed);
                success = false;
                break;
            }
        }

        if (success) {
            for (int index = 0; index < BOOK_END; ++index) {
                if (isValidItem(index) && shuffled[index] == EMPTY) {
                    fprintf(stdout, "\tid 0x%02x not mapped with seed 0x%08x, retrying...\n",
                        index, initialSeed);
                    success = false;
                    break;
                }
            }
        }
    }

    fprintf(stdout, "\tDone.\n\n");
    return true;
}

void patchRom(uint8_t * rom, itemId_t * shuffledItems) {
    fprintf(stdout, "Updating game logic...\n");

    // update item display
    // prevent item look-up in room 0x01 (Dungeon)
    replaceCommand(rom, 0x80030cc0u, 0x0c028320u); // JAL 0x800a0c80
    replaceCommand(rom, 0x80030cc4u, 0x00000000u); // NOP

    replaceCommand(rom, 0x800a0c80u, 0x3c01800eu); // LUI AT, 0x800e
    replaceCommand(rom, 0x800a0c84u, 0x9421a726u); // LHU AT, 0xa726 (AT)
    replaceCommand(rom, 0x800a0c88u, 0x24070001u); // ADDIU A3, R0, 0x0001
    replaceCommand(rom, 0x800a0c8cu, 0x10270006u); // BEQ AT, A3, 0x800a0ca8
    replaceCommand(rom, 0x800a0c90u, 0x30a700ffu); // ANDI A3, A1, 0x00ff
    replaceCommand(rom, 0x800a0c94u, 0x30a5ff00u); // ANDI A1, A1, 0xff00
    replaceCommand(rom, 0x800a0c98u, 0x3c01800au); // LUI AT, 0x800a
    replaceCommand(rom, 0x800a0c9cu, 0x00270821u); // ADDU AT, AT, A3
    replaceCommand(rom, 0x800a0ca0u, 0x90270c00u); // LBU A3, 0x0c00 (AT)
    replaceCommand(rom, 0x800a0ca4u, 0x00a72825u); // OR A1, A1, A3
    replaceCommand(rom, 0x800a0ca8u, 0x0801ed3cu); // J 0x8007b4f0
    replaceCommand(rom, 0x800a0cacu, 0x00003821u); // ADDU A3, R0, R0

    // default item pickup path
    replaceCommand(rom, 0x800320e8u, 0x0802832cu); // J 0x800a0cb0

    replaceCommand(rom, 0x800a0cb0u, 0x3c01800au); // LUI AT, 0x800a
    replaceCommand(rom, 0x800a0cb4u, 0x00260821u); // ADDU AT, AT, A2
    replaceCommand(rom, 0x800a0cb8u, 0x90260C00u); // LBU A2, 0x0c00 (AT)
    replaceCommand(rom, 0x800a0cbcu, 0x0800c83bu); // J 0x800320ec
    replaceCommand(rom, 0x800a0cc0u, 0x30C200ffu); // ANDI V0, A2, 0x00ff

    // item status update path
    // don't override a clear (0x40), equip (0x20), or placement (0x04) action
    // prevent item look-up in rooms 0x3c (Disciples' Bookshelf) and 0x2e (Destroyed Park)
    replaceCommand(rom, 0x80030dd0u, 0x08028331u); // J 0x800a0cc4
    replaceCommand(rom, 0x80030dd4u, 0x27bdfff8u); // ADDIU SP, SP, -0x08
    //                  0x80030dd8u, 0x14a00008u   // BNEZ A1, 0x80030dfc (unchanged)
    replaceCommand(rom, 0x80030ddcu, 0x00000000u); // NOP

    replaceCommand(rom, 0x800a0cc4u, 0x30856400u); // ANDI A1, A0, 0x6400
    replaceCommand(rom, 0x800a0cc8u, 0x14a0000au); // BNEZ A1, 0x800a0ce4
    replaceCommand(rom, 0x800a0cccu, 0x308600ffu); // ANDI A2, A0, 0x00ff
    replaceCommand(rom, 0x800a0cd0u, 0x3c05800eu); // LUI A1, 0x800e
    replaceCommand(rom, 0x800a0cd4u, 0x94a5a726u); // LHU A1, 0xa726 (A1)
    replaceCommand(rom, 0x800a0cd8u, 0x2402003cu); // ADDIU V0, R0, 0x003c
    replaceCommand(rom, 0x800a0cdcu, 0x10450005u); // BEQ V0, A1, 0x800a0cf4
    replaceCommand(rom, 0x800a0ce0u, 0x2402002eu); // ADDIU V0, R0, 0x002e
    replaceCommand(rom, 0x800a0ce4u, 0x10450003u); // BEQ V0, A1, 0x800a0cf4
    replaceCommand(rom, 0x800a0ce8u, 0x3c02800au); // LUI V0, 0x800a
    replaceCommand(rom, 0x800a0cecu, 0x00461021u); // ADDU V0, V0, A2
    replaceCommand(rom, 0x800a0cf0u, 0x90460c00u); // LBU A2, 0x0c00 (V0)
    replaceCommand(rom, 0x800a0cf4u, 0x0800c376u); // J 0x80030dd8
    replaceCommand(rom, 0x800a0cf8u, 0x3085ff00u); // ANDI A1, A0, 0xff00

    // update inventory checks
    // don't override a clear (0x40), equipped check (0x20), or placement (0x04) action
    // prevent item look-up in room 0x36 (Disciples' Foyer), 0x05 (Keeper's Room), and 0x5f (Trials Crest Room)
    replaceCommand(rom, 0x80032528u, 0x0802833fu); // J 0x800a0cfc
    replaceCommand(rom, 0x8003252cu, 0x00000000u); // NOP
    //                  0x80032530u, 0x9022c3d0u); // LBU V0, 0xc3d0 (AT) (unchanged, but skipped)

    replaceCommand(rom, 0x800a0cfcu, 0x30816400u); // ANDI AT, A0, 0x6400
    replaceCommand(rom, 0x800a0d00u, 0x1420000bu); // BNEZ AT, 0x800a0d30
    replaceCommand(rom, 0x800a0d04u, 0x3c01800eu); // LUI AT, 0x800e
    replaceCommand(rom, 0x800a0d08u, 0x9421a726u); // LHU AT, 0xa726 (AT)
    replaceCommand(rom, 0x800a0d0cu, 0x24060036u); // ADDIU A2, R0, 0x0036
    replaceCommand(rom, 0x800a0d10u, 0x10260007u); // BEQ AT, A2, 0x800a0d30
    replaceCommand(rom, 0x800a0d14u, 0x24060005u); // ADDIU A2, R0, 0x0005
    replaceCommand(rom, 0x800a0d18u, 0x10260005u); // BEQ AT, A2, 0x800a0d30
    replaceCommand(rom, 0x800a0d1cu, 0x2406005fu); // ADDIU A2, R0, 0x005f
    replaceCommand(rom, 0x800a0d20u, 0x10260003u); // BEQ AT, A2, 0x800a0d30
    replaceCommand(rom, 0x800a0d24u, 0x3c01800au); // LUI AT, 0x800a
    replaceCommand(rom, 0x800a0d28u, 0x00220821u); // ADDU AT, AT, V0
    replaceCommand(rom, 0x800a0d2cu, 0x90220c00u); // LBU V0, 0x0c00 (AT)
    replaceCommand(rom, 0x800a0d30u, 0x3c01800fu); // LUI AT, 0x800f
    replaceCommand(rom, 0x800a0d34u, 0x00220821u); // ADDU AT, AT, V0
    replaceCommand(rom, 0x800a0d38u, 0x9022c3d0u); // LBU V0, 0xc3d0 (AT)
    replaceCommand(rom, 0x800a0d3cu, 0x0800c94du); // J 0x80032534
    replaceCommand(rom, 0x800a0d40u, 0x00803021u); // ADDU A2, A0, R0

    fprintf(stdout, "\tDone.\n");

    fprintf(stdout, "Writing item lookup table...\n");

    uint32_t offset = LOOKUP_TABLE_LOCATION - ROM_OFFSET;
    for (itemId_t i = 0; i < BOOK_END; ++i) {
        rom[offset + i] = shuffledItems[i];
    }

    fprintf(stdout, "\tDone.\n\n");
}

void updateChecksums(uint8_t * rom) {
    fprintf(stdout, "Updating ROM checksums...\n");
    uint32_t checksum1;
    uint32_t checksum2;
    findChecksums(rom + CHECKSUM_DATA_OFFSET, CHECKSUM_DATA_SIZE, &checksum1, &checksum2);

    fprintf(stdout, "\tNew checksums: 0x%08x 0x%08x\n", checksum1, checksum2);

    rom[ROM_OFFSET_CHECKSUM_1 + 0] = (checksum1 >> 24) & 0xffu;
    rom[ROM_OFFSET_CHECKSUM_1 + 1] = (checksum1 >> 16) & 0xffu;
    rom[ROM_OFFSET_CHECKSUM_1 + 2] = (checksum1 >>  8) & 0xffu;
    rom[ROM_OFFSET_CHECKSUM_1 + 3] = (checksum1 >>  0) & 0xffu;

    rom[ROM_OFFSET_CHECKSUM_2 + 0] = (checksum2 >> 24) & 0xffu;
    rom[ROM_OFFSET_CHECKSUM_2 + 1] = (checksum2 >> 16) & 0xffu;
    rom[ROM_OFFSET_CHECKSUM_2 + 2] = (checksum2 >>  8) & 0xffu;
    rom[ROM_OFFSET_CHECKSUM_2 + 3] = (checksum2 >>  0) & 0xffu;

    fprintf(stdout, "\tDone.\n\n");
}

bool writePatchedRom(uint8_t * rom, const char * titleIdentifier, shuffleMode_t mode, const itemId_t * shuffled) {
    fprintf(stdout, "Writing randomized ROM file...\n");

    char output[32];
    sprintf(output, "roms/%s_%u_0x%08x.z64", titleIdentifier, mode + 1, initialSeed);

#ifdef _MSC_VER
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif
    FILE * file = fopen(output, "wb");
#ifdef _MSC_VER
#pragma clang diagnostic pop
#endif

    if (!file) {
        fprintf(stderr, "Failed to open %s\n", output);
        return false;
    }

    if (fwrite(rom, 1, EXPECTED_SIZE, file) != EXPECTED_SIZE) {
        fprintf(stderr, "Failed to write %s\n", output);
        fclose(file);
        return false;
    }
    fclose(file);

    fprintf(stdout, "\tDone.\n");

    fprintf(stdout, "Writing report...\n");
    strcpy(strchr(output, '.') + 1, "txt");

#ifdef _MSC_VER
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif
    file = fopen(output, "w");
#ifdef _MSC_VER
#pragma clang diagnostic pop
#endif

    if (!file) {
        fprintf(stderr, "Failed to write report.\n");
        return false;
    }

    for (itemId_t id = 0; id < BOOK_END; ++id) {
        if (!isValidItem(id)) {
            continue;
        }

        fprintf(file, "%s -> %s\n", itemNames[id], itemNames[shuffled[id]]);
    }

    fclose(file);
    fprintf(stdout, "\tDone.\n");
    return true;
}

#define MODE_DOCS \
    fprintf(stderr, "\t1: Static books\n"); \
    fprintf(stderr, "\t2: Shuffle books separately\n"); \
    fprintf(stderr, "\t3: Shuffle books\n"); \
    fprintf(stderr, "\t4: Shuffle books without logic\n"); \
    fprintf(stderr, "\tDefaults to 3: Shuffle books\n");

#define SEED_DOCS \
    fprintf(stderr, "\tMust be an unsigned hexadecimal number within 1 - ffffffff.\n"); \
    fprintf(stderr, "\t0x prefix is optional.\n"); \
    fprintf(stderr, "\tOmit this parameter to use the current time.\n");

int main(int argc, char ** argv) {
    if (argc < 2 || argc > 4) {
        fprintf(stderr, "Usage: %s <rom file> [shuffle mode] [seed]\n", argv[0]);

        fprintf(stderr, "\nShuffle modes:\n");
        MODE_DOCS

        fprintf(stderr, "\nSeed:\n");
        SEED_DOCS

        return RETURN_CODE_INVALID_ARGS;
    }

    char titleIdentifier[TITLE_IDENTIFIER_LENGTH + 1];
    uint8_t * rom = readAndConfirmRom(argv[1], titleIdentifier);
    if (!rom) {
        return RETURN_CODE_INVALID_ROM;
    }

    shuffleMode_t mode = MODE_SHUFFLE_BOOKS;
    if (argc > 2) {
        int m = atoi(argv[2]);
        if (m > MODE_INPUT_MAX || m < MODE_INPUT_MIN) {
            fprintf(stderr, "Invalid mode: %s\n", argv[2]);
            MODE_DOCS
            return RETURN_CODE_INVALID_MODE;
        }

        mode = (shuffleMode_t) (m - 1);
    }

    initialSeed = 0u;
    if (argc > 3) {
        long long int seed = strtoll(argv[3], NULL, 16);

        if (seed > MAX_SEED || seed <= 0) {
            fprintf(stderr, "Invalid seed: %s\n", argv[3]);
            SEED_DOCS
            return RETURN_CODE_INVALID_SEED;
        }

        initialSeed = (uint32_t) seed;
    }

    itemId_t shuffled[BOOK_END];
    if (!randomize(mode, initialSeed, shuffled)) {
        free(rom);
        return RETURN_CODE_SHUFFLE_FAILED;
    }

    patchRom(rom, shuffled);
    updateChecksums(rom);

    if (!writePatchedRom(rom, titleIdentifier, mode, shuffled)) {
        free(rom);
        return RETURN_CODE_WRITE_FAILED;
    }

    free(rom);
    return RETURN_CODE_SUCCESS;
}