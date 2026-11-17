// name = f (first), n (nibble), 1. Es heisst das erste nibble D ist.
#include "../headers/fn_D.h"
#include <stdint.h>

void decode_fnD(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode) {
  uint8_t n = sliced_opcode.n;

  uint8_t x = c->V[sliced_opcode.x] & 63;
  uint8_t y = c->V[sliced_opcode.y] & 31;

  c->V[0xF] = 0;

  for (int row = 0; row < n; row++) {
    if (y + row >= SCREEN_H)
      break;
    uint8_t sprite = c->memory[c->I + row];

    for (int col = 0; col < 8; col++) {
      if (x + col >= SCREEN_W)
        break;
      if (sprite & (0x80 >> col)) {
        uint8_t *px = &c->display[y + row][x + col];
        if (*px)
          c->V[0xF] = 1;
        *px ^= 1;
      }
    }
  }
}
