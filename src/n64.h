#ifndef N64_H
#define N64_H

#include <stdint.h>

// https://en64.shoutwiki.com/wiki/ROM#Cartridge_ROM_Header
typedef enum {
    ROM_OFFSET_HEADER = 0,
    ROM_OFFSET_BOOT_ADDRESS = 0x8,
    ROM_OFFSET_CHECKSUM_1 = 0x10,
    ROM_OFFSET_CHECKSUM_2 = 0x14,
    ROM_OFFSET_NAME = 0x20,
    ROM_OFFSET_TITLE_IDENTIFIER = 0x3b,
    ROM_OFFSET_BOOT_CODE = 0x40,
    ROM_OFFSET_GAME = 1 << 12,
} romOffset_t;

typedef enum {
    OFFSET_MEDIA_FORMAT = 0,
    OFFSET_CART_ID_0 = 1,
    OFFSET_CART_ID_1 = 2,
    OFFSET_CART_COUNTRY_CODE = 3,
    TITLE_IDENTIFIER_LENGTH = 4,
} titleIdentifierOffset_t;

typedef enum {
    CHECKSUM_DATA_OFFSET = ROM_OFFSET_GAME,
    CHECKSUM_DATA_SIZE = 1 << 20,
} romChecksumData_t;

static const uint32_t BOOT_CODE_SIZE = ROM_OFFSET_GAME - ROM_OFFSET_BOOT_CODE;

uint32_t swapBytes(uint8_t * data);
void findTitleIdentifier(uint8_t * rom, char * titleIdentifier);

#endif