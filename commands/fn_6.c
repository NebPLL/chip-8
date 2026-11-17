// name = f (first), n (nibble), 1. Es heisst das erste nibble 6 ist.
#include "../headers/fn_6.h"

void decode_fn6(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode) {
  c->V[sliced_opcode.x] = sliced_opcode.nn;
}
