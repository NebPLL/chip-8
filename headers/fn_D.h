#ifndef FN_D
#define FN_D

#include "../headers/chip8.h"
#include <stdint.h>

void decode_fnD(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode);

#endif
