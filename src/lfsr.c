#include <time.h>
#include "lfsr.h"

// Based on https://www.analog.com/en/resources/design-notes/random-number-generation-using-lfsr.html

uint32_t lfsr;
uint32_t initialSeed;

void setSeed(uint32_t seed) {
    if (seed == 0u) {
        seed = time(NULL) & 0xffffffffu;
    }

    lfsr = seed ? seed : 1u;
    initialSeed = lfsr;
}

uint8_t nextRandom() {
    uint8_t feedback = lfsr & 1u;
    lfsr >>= 1;
    lfsr ^= 0xb4bcd35cu * feedback;
    return lfsr & 0xffu;
}