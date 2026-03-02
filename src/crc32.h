#ifndef CRC32_H
#define CRC32_H

#include <stdint.h>

// Based on tiny crc32 by notwa
// https://gist.github.com/notwa/5689243
static const uint32_t CRC32_TABLE[] = {
    0x00000000u, 0x1db71064u, 0x3b6e20c8u, 0x26d930acu,
    0x76dc4190u, 0x6b6b51f4u, 0x4db26158u, 0x5005713cu,
    0xedb88320u, 0xf00f9344u, 0xd6d6a3e8u, 0xcb61b38cu,
    0x9b64c2b0u, 0x86d3d2d4u, 0xa00ae278u, 0xbdbdf21cu,
};

uint32_t crc32(uint8_t * data, uint32_t size);

#endif