// name = f (first), n (nibble), 1. Es heisst das erste nibble 2 ist.
#include "../headers/fn_2.h"

void decode_fn2(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode) {
  c->stack[c->sp] = c->pc;
  c->sp++;

  c->pc = sliced_opcode.nnn;
}
