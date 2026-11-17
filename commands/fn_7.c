// name = f (first), n (nibble), 1. Es heisst das erste nibble 7 ist.
#include "../headers/fn_7.h"

void decode_fn7(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode) {
  c->V[sliced_opcode.x] += sliced_opcode.nn;
}
