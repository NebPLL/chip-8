// name = f (first), n (nibble), 1. Es heisst das erste nibble E ist.
#include "../headers/fn_E.h"
#include <stdint.h>
#include <stdio.h>

void decode_fnE(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode) {
  switch (opcode & 0x00FF) {
  case 0x9E:
    if (getKeys()[c->V[sliced_opcode.x]]) {
      c->pc += 2;
    }

    break;

  case 0xA1:
    if (!getKeys()[c->V[sliced_opcode.x]]) {
      c->pc += 2;
    }

    break;

  default:
    printf("Opencode not found (E):%i\n", opcode);
  }
}
