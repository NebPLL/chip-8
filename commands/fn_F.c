// name = f (first), n (nibble), 1. Es heisst das erste nibble F ist.
#include "../headers/fn_F.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void decode_fnF(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode) {
  switch (opcode & 0x00FF) {
  case 0x0007:
    c->V[sliced_opcode.x] = c->delay_timer;
    break;

  case 0x0015:
    c->delay_timer = c->V[sliced_opcode.x];
    break;

  case 0x0018:
    c->sound_timer = c->V[sliced_opcode.x];
    break;

  case 0x001E:
    c->I += c->V[sliced_opcode.x];
    break;

  case 0x000A: {
    bool erfolg = false;
    const int AMOUNTOFKEYS = 16;
    for (int i = 0; i < AMOUNTOFKEYS; i++) {
      if (getKeys()[i]) {
        c->V[sliced_opcode.x] = i;
        erfolg = true;
      }
    }

    if (!erfolg) {
      c->pc -= 2;
    }
    break;
  }

  case 0x0029:
    c->I = FONT_START + (c->V[sliced_opcode.x] & 0xF) * 5;

    break;
  case 0x0033: {
    uint8_t x = c->V[sliced_opcode.x];

    c->memory[c->I] = x / 100;
    c->memory[c->I + 1] = x / 10 % 10;
    c->memory[c->I + 2] = x % 10;

    break;
  }

  case 0x0055:
    for (int i = 0; i <= sliced_opcode.x; i++) {
      c->memory[c->I + i] = c->V[i];
    }

    break;

  case 0x0065:
    for (int i = 0; i <= sliced_opcode.x; i++) {
      c->V[i] = c->memory[c->I + i];
    }

    break;

  default:
    printf("Opencode not found (F):%i\n", opcode);
  }
}
