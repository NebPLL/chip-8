#ifndef FN_A
#define FN_A

#include "../headers/chip8.h"
#include <stdint.h>

void decode_fnA(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode);

#endif
