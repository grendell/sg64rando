#ifndef SG64_H
#define SG64_H

#include <stdbool.h>
#include <stdint.h>
#include "n64.h"

static const uint32_t EXPECTED_SIZE = 1u << 24;
static const uint32_t EXPECTED_HEADER_MAGIC = 0x80371240u;
static const uint32_t EXPECTED_BOOT_CODE_CRC = 0x90bb6cb5u;
static const uint32_t EXPECTED_BOOT_ADDRESS = 0x80025c00u;

static const uint32_t ROM_OFFSET = EXPECTED_BOOT_ADDRESS - ROM_OFFSET_GAME;

static const uint32_t CHECKSUM_SEED = 0xf8ca4ddcu;

static const uint32_t EXPECTED_CHECKSUM_E_1 = 0x036897ceu;
static const uint32_t EXPECTED_CHECKSUM_E_2 = 0xe0d4fa54u;
static const uint32_t EXPECTED_CHECKSUM_J_1 = 0xccedb696u;
static const uint32_t EXPECTED_CHECKSUM_J_2 = 0xd3883db4u;
static const uint32_t EXPECTED_CHECKSUM_P_1 = 0xd84eea84u;
static const uint32_t EXPECTED_CHECKSUM_P_2 = 0x45b2f1b4u;
static const uint32_t EXPECTED_CHECKSUM_X_1 = 0x2bc1fcf2u;
static const uint32_t EXPECTED_CHECKSUM_X_2 = 0x7b9a0df4u;
static const uint32_t EXPECTED_CHECKSUM_Y_1 = 0x02b46f55u;
static const uint32_t EXPECTED_CHECKSUM_Y_2 = 0x61778d0bu;

bool getExpectedChecksums(char countryCode, uint32_t * expectedChecksum1, uint32_t * expectedChecksum2);
void findChecksums(uint8_t * data, uint32_t size, uint32_t * checksum1, uint32_t * checksum2);
void replaceCommand(uint8_t * rom, uint32_t memoryOffset, uint32_t mipsCommand);

#endif