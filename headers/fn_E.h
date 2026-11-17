#ifndef FN_E
#define FN_E

#include "../headers/chip8.h"
#include <stdint.h>

void decode_fnE(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode);

#endif
