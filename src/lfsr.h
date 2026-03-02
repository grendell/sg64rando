#ifndef LFSR_H
#define LFSR_H

#include <stdint.h>

void setSeed(uint32_t seed);
uint8_t nextRandom();

#endif