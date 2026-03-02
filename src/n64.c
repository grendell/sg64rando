#include <string.h>
#include "n64.h"

uint32_t swapBytes(uint8_t * data) {
    return data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];
}

void findTitleIdentifier(uint8_t * rom, char * titleIdentifier) {
    strncpy(titleIdentifier, (const char *) rom + ROM_OFFSET_TITLE_IDENTIFIER, TITLE_IDENTIFIER_LENGTH);
}