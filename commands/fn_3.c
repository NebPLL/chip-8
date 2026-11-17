// name = f (first), n (nibble), 1. Es heisst das erste nibble 2 ist.
#include "../headers/fn_3.h"
#include <stdint.h>

void decode_fn3(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode) {
  uint8_t vx = c->V[sliced_opcode.x];

  if (vx == sliced_opcode.nn) {
    c->pc += 2;
  }
}
