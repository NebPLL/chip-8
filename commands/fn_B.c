// name = f (first), n (nibble), 1. Es heisst das erste nibble B ist.
#include "../headers/fn_B.h"

void decode_fnB(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode) {
  c->pc = sliced_opcode.nnn + c->V[sliced_opcode.x];
}
