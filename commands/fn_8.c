// name = f (first), n (nibble), 1. Es heisst das erste nibble 8 ist.
#include "../headers/fn_8.h"
#include <stdint.h>
#include <stdio.h>

void decode_fn8(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode) {
  switch (opcode & 0x000F) {
  case 0:
    c->V[sliced_opcode.x] = c->V[sliced_opcode.y];
    break;

  case 1:
    c->V[sliced_opcode.x] |= c->V[sliced_opcode.y];
    break;

  case 2:
    c->V[sliced_opcode.x] &= c->V[sliced_opcode.y];
    break;
  case 3:
    c->V[sliced_opcode.x] ^= c->V[sliced_opcode.y];
    break;

  case 4:
    if (c->V[sliced_opcode.x] + c->V[sliced_opcode.y] > 255) {
      c->V[0xF] = 1;
    } else {

      c->V[0xF] = 0;
    }
    c->V[sliced_opcode.x] += c->V[sliced_opcode.y];
    break;

  case 5:
    if (c->V[sliced_opcode.x] >= c->V[sliced_opcode.y]) {
      c->V[0xF] = 1;
    } else {

      c->V[0xF] = 0;
    }

    c->V[sliced_opcode.x] = c->V[sliced_opcode.x] - c->V[sliced_opcode.y];
    break;
  case 7:

    if (c->V[sliced_opcode.y] >= c->V[sliced_opcode.x]) {
      c->V[0xF] = 1;
    } else {

      c->V[0xF] = 0;
    }

    c->V[sliced_opcode.x] = c->V[sliced_opcode.y] - c->V[sliced_opcode.x];
    break;

  case 0x6: {
    uint8_t src = c->V[sliced_opcode.x];
    uint8_t flag = src & 0x01;
    c->V[sliced_opcode.x] = src >> 1;
    c->V[0xF] = flag;
    break;
  }

  case 0xE: {
    uint8_t src = c->V[sliced_opcode.x];
    uint8_t flag = (src >> 7) & 0x01;
    c->V[sliced_opcode.x] = src << 1;
    c->V[0xF] = flag;
    break;
  }

  default:
    printf("Opencode not found (8):%i\n", opcode);
  }
}
