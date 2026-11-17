#ifndef FN_F
#define FN_F

#include "../headers/chip8.h"
#include <stdint.h>

void decode_fnF(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode);

#endif
