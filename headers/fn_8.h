#ifndef FN_8
#define FN_8

#include "../headers/chip8.h"
#include <stdint.h>

void decode_fn8(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode);

#endif
