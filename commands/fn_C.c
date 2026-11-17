// name = f (first), n (nibble), 1. Es heisst das erste nibble B ist.
#include "../headers/fn_C.h"
#include <stdlib.h>

void decode_fnC(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode) {
  uint8_t r = rand() % (UINT8_MAX + 1);
  c->V[sliced_opcode.x] = r & sliced_opcode.nn;
}
