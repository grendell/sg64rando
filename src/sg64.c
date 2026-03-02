#include "sg64.h"

bool getExpectedChecksums(char countryCode, uint32_t * expectedChecksum1, uint32_t * expectedChecksum2) {
    switch (countryCode) {
        case 'E': {
            *expectedChecksum1 = EXPECTED_CHECKSUM_E_1;
            *expectedChecksum2 = EXPECTED_CHECKSUM_E_2;
            return true;
        }
        case 'J': {
            *expectedChecksum1 = EXPECTED_CHECKSUM_J_1;
            *expectedChecksum2 = EXPECTED_CHECKSUM_J_2;
            return true;
        }
        case 'P': {
            *expectedChecksum1 = EXPECTED_CHECKSUM_P_1;
            *expectedChecksum2 = EXPECTED_CHECKSUM_P_2;
            return true;
        }
        case 'X': {
            *expectedChecksum1 = EXPECTED_CHECKSUM_X_1;
            *expectedChecksum2 = EXPECTED_CHECKSUM_X_2;
            return true;
        }
        case 'Y': {
            *expectedChecksum1 = EXPECTED_CHECKSUM_Y_1;
            *expectedChecksum2 = EXPECTED_CHECKSUM_Y_2;
            return true;
        }
    }

    return false;
}

// Based on chksum64 V1.2 by Andreas Sterbenz (stan@sbox.tu-graz.ac.at)
// https://github.com/DragonMinded/libdragon/blob/f43ba72c035f27fff894df44b2453e9d346c3c9a/tools/chksum64.c
void findChecksums(uint8_t * data, uint32_t size, uint32_t * checksum1, uint32_t * checksum2) {
    uint32_t c1;
    uint32_t k1;
    uint32_t k2;
    uint32_t t1 = CHECKSUM_SEED;
    uint32_t t2 = CHECKSUM_SEED;
    uint32_t t3 = CHECKSUM_SEED;
    uint32_t t4 = CHECKSUM_SEED;
    uint32_t t5 = CHECKSUM_SEED;
    uint32_t t6 = CHECKSUM_SEED;

    for (uint32_t i = 0; i < size; i += 4) {
        c1 = swapBytes(data + i);

        k1 = t6 + c1;
        if (k1 < t6) {
            ++t4;
        }
        t6 = k1;
        t3 ^= c1;

        k2 = c1 & 0x1fu;
        k1 = (c1 << k2) | (c1 >> (32u - k2));
        t5 += k1;
        
        if (c1 < t2) {
            t2 ^= k1;
        } else {
            t2 ^= t6 ^ c1;
        }

        t1 += c1 ^ t5;
    }

    *checksum1 = t6 ^ t4 ^ t3;
    *checksum2 = t5 ^ t2 ^ t1;
}

void replaceCommand(uint8_t * rom, uint32_t memoryOffset, uint32_t mipsCommand) {
    uint32_t offset = memoryOffset - ROM_OFFSET;
    rom[offset + 0] = (mipsCommand >> 24) & 0xffu;
    rom[offset + 1] = (mipsCommand >> 16) & 0xffu;
    rom[offset + 2] = (mipsCommand >>  8) & 0xffu;
    rom[offset + 3] = (mipsCommand >>  0) & 0xffu;
}