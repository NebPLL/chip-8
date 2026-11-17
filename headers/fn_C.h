#ifndef FN_C
#define FN_C

#include "../headers/chip8.h"
#include <stdint.h>

void decode_fnC(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode);

#endif
