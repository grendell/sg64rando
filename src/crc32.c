#include "crc32.h"

// Based on tiny crc32 by notwa
// https://gist.github.com/notwa/5689243
uint32_t crc32(uint8_t * data, uint32_t size) {
    uint32_t crc = 0xffffffffu;

    while (size--) {
        crc = (crc >> 4) ^ CRC32_TABLE[(crc & 0xfu) ^ (*data & 0xfu)];
        crc = (crc >> 4) ^ CRC32_TABLE[(crc & 0xfu) ^ (*(data++) >> 4)];
    }

    return ~crc;
}