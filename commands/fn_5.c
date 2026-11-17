// name = f (first), n (nibble), 1. Es heisst das erste nibble 2 ist.
#include "../headers/fn_5.h"

void decode_fn5(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode) {
  uint8_t vx = c->V[sliced_opcode.x];
  uint8_t vy = c->V[sliced_opcode.y];

  if (vx == vy) {
    c->pc += 2;
  }
}
