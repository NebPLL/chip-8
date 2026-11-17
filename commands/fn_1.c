// name = f (first), n (nibble), 1. Es heisst das erste nibble 1 ist.
#include "../headers/fn_1.h"
void decode_fn1(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode) {
  c->pc = sliced_opcode.nnn;
}
