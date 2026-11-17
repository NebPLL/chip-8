// name = f (first), n (nibble), 0. Es heisst das erste nibble 0 ist.
#include "../headers/fn_0.h"
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>

void decode_fn0(Chip8 *c, uint16_t opcode) {
  switch (opcode) {
  case 0x00E0:
    for (int w = 0; w < SCREEN_W; w++) {
      for (int h = 0; h < SCREEN_H; h++) {
        c->display[h][w] = 0;
      }
    }

    break;

  case 0x00EE:
    c->sp--;
    c->pc = c->stack[c->sp];
    break;

  default:
    printf("Opencode not found (1):%i\n", opcode);
  }
}
