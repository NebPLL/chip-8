// name = f (first), n (nibble), 1. Es heisst das erste nibble 7 ist.
#include "../headers/fn_9.h"

void decode_fn9(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode) {
  uint8_t vx = c->V[sliced_opcode.x];
  uint8_t vy = c->V[sliced_opcode.y];

  if (vx != vy) {
    c->pc += 2;
  }
}
