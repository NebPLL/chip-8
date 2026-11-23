#include "headers/instructions.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void op_00E0_cls(Chip8 *c) {
  for (int w = 0; w < SCREEN_W; w++) {
    for (int h = 0; h < SCREEN_H; h++) {
      c->display[h][w] = 0;
    }
  }
}

void op_00EE_ret(Chip8 *c) {
  if (c->sp == 0) {
    fprintf(stderr, "Stack underflow at 0x%03X\n", c->pc - 2);
    return;
  }
  c->sp--;
  c->pc = c->stack[c->sp];
}

void op_1NNN_jump(Chip8 *c, sliced_opcode sliced_opcode) {
  c->pc = sliced_opcode.nnn;
}

void op_2NNN_call(Chip8 *c, sliced_opcode sliced_opcode) {
  if (c->sp >= STACK_SIZE) {
    fprintf(stderr, "Stack overflow at 0x%03X\n", c->pc - 2);
    return;
  }
  c->stack[c->sp] = c->pc;
  c->sp++;
  c->pc = sliced_opcode.nnn;
}

void op_3XNN_skip_eq(Chip8 *c, sliced_opcode sliced_opcode) {
  uint8_t vx = c->V[sliced_opcode.x];

  if (vx == sliced_opcode.nn) {
    c->pc += 2;
  }
}

void op_4XNN_skip_neq(Chip8 *c, sliced_opcode sliced_opcode) {
  uint8_t vx = c->V[sliced_opcode.x];

  if (vx != sliced_opcode.nn) {
    c->pc += 2;
  }
}

void op_5XY0_skip_eq_reg(Chip8 *c, sliced_opcode sliced_opcode) {
  uint8_t vx = c->V[sliced_opcode.x];
  uint8_t vy = c->V[sliced_opcode.y];

  if (vx == vy) {
    c->pc += 2;
  }
}

void op_6XNN_set(Chip8 *c, sliced_opcode sliced_opcode) {
  c->V[sliced_opcode.x] = sliced_opcode.nn;
}

void op_7XNN_add(Chip8 *c, sliced_opcode sliced_opcode) {
  c->V[sliced_opcode.x] += sliced_opcode.nn;
}

void op_8XY0_copy(Chip8 *c, sliced_opcode sliced_opcode) {
  c->V[sliced_opcode.x] = c->V[sliced_opcode.y];
}

void op_8XY1_or(Chip8 *c, sliced_opcode sliced_opcode) {
  c->V[sliced_opcode.x] |= c->V[sliced_opcode.y];
}

void op_8XY2_and(Chip8 *c, sliced_opcode sliced_opcode) {
  c->V[sliced_opcode.x] &= c->V[sliced_opcode.y];
}

void op_8XY3_xor(Chip8 *c, sliced_opcode sliced_opcode) {
  c->V[sliced_opcode.x] ^= c->V[sliced_opcode.y];
}

void op_8XY4_add(Chip8 *c, sliced_opcode sliced_opcode) {
  bool carry = c->V[sliced_opcode.x] + c->V[sliced_opcode.y] > 255;

  c->V[sliced_opcode.x] += c->V[sliced_opcode.y];

  c->V[0xF] = carry;
}

void op_8XY5_sub(Chip8 *c, sliced_opcode sliced_opcode) {
  bool no_borrow = c->V[sliced_opcode.x] >= c->V[sliced_opcode.y];

  c->V[sliced_opcode.x] = c->V[sliced_opcode.x] - c->V[sliced_opcode.y];

  c->V[0xF] = no_borrow;
}

void op_8XY6_shr(Chip8 *c, sliced_opcode sliced_opcode) {
  uint8_t src = c->V[sliced_opcode.x];
  uint8_t flag = src & 0x01;
  c->V[sliced_opcode.x] = src >> 1;
  c->V[0xF] = flag;
}

void op_8XY7_subn(Chip8 *c, sliced_opcode sliced_opcode) {
  bool no_borrow = c->V[sliced_opcode.y] >= c->V[sliced_opcode.x];

  c->V[sliced_opcode.x] = c->V[sliced_opcode.y] - c->V[sliced_opcode.x];

  c->V[0xF] = no_borrow;
}

void op_8XYE_shl(Chip8 *c, sliced_opcode sliced_opcode) {

  uint8_t src = c->V[sliced_opcode.x];
  uint8_t flag = (src >> 7) & 0x01;
  c->V[sliced_opcode.x] = src << 1;
  c->V[0xF] = flag;
}

void op_9XY0_skip_neq_reg(Chip8 *c, sliced_opcode sliced_opcode) {
  uint8_t vx = c->V[sliced_opcode.x];
  uint8_t vy = c->V[sliced_opcode.y];

  if (vx != vy) {
    c->pc += 2;
  }
}

void op_ANNN_set_i(Chip8 *c, sliced_opcode sliced_opcode) {
  c->I = sliced_opcode.nnn;
}

void op_BXNN_jump_vx(Chip8 *c, sliced_opcode sliced_opcode) {
  c->pc = sliced_opcode.nnn + c->V[sliced_opcode.x];
}

void op_CXNN_rand(Chip8 *c, sliced_opcode sliced_opcode) {
  uint8_t r = rand() % (UINT8_MAX + 1);
  c->V[sliced_opcode.x] = r & sliced_opcode.nn;
}

void op_DXYN_draw(Chip8 *c, sliced_opcode sliced_opcode) {
  uint8_t n = sliced_opcode.n;

  uint8_t x = c->V[sliced_opcode.x] & 63;
  uint8_t y = c->V[sliced_opcode.y] & 31;

  c->V[0xF] = 0;

  for (int row = 0; row < n; row++) {
    if (y + row >= SCREEN_H)
      break;
    uint8_t sprite = c->memory[(c->I + row) & 0xFFF];

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

void op_EX9E_skip_key(Chip8 *c, sliced_opcode sliced_opcode) {
  if (c->keys[c->V[sliced_opcode.x] & 0x0F]) {
    c->pc += 2;
  }
}

void op_EXA1_skip_nkey(Chip8 *c, sliced_opcode sliced_opcode) {
  if (!c->keys[c->V[sliced_opcode.x] & 0x0F]) {
    c->pc += 2;
  }
}

void op_FX07_get_delay(Chip8 *c, sliced_opcode sliced_opcode) {
  c->V[sliced_opcode.x] = c->delay_timer;
}

void op_FX15_set_delay(Chip8 *c, sliced_opcode sliced_opcode) {
  c->delay_timer = c->V[sliced_opcode.x];
}

void op_FX18_set_sound(Chip8 *c, sliced_opcode sliced_opcode) {
  c->sound_timer = c->V[sliced_opcode.x];
}

void op_FX1E_add_i(Chip8 *c, sliced_opcode sliced_opcode) {
  c->I += c->V[sliced_opcode.x];
}

void op_FX0A_wait_key(Chip8 *c, sliced_opcode sliced_opcode) {
  bool success = false;
  const int AMOUNTOFKEYS = 16;
  for (int i = 0; i < AMOUNTOFKEYS; i++) {
    if (c->keys[i]) {
      c->V[sliced_opcode.x] = i;
      success = true;
    }
  }

  if (!success) {
    c->pc -= 2;
  }
}

void op_FX29_font(Chip8 *c, sliced_opcode sliced_opcode) {
  c->I = FONT_START + (c->V[sliced_opcode.x] & 0xF) * 5;
}

void op_FX33_bcd(Chip8 *c, sliced_opcode sliced_opcode) {
  uint8_t x = c->V[sliced_opcode.x];

  c->memory[c->I & 0xFFF] = x / 100;
  c->memory[(c->I + 1) & 0xFFF] = x / 10 % 10;
  c->memory[(c->I + 2) & 0xFFF] = x % 10;
}

void op_FX55_store(Chip8 *c, sliced_opcode sliced_opcode) {

  for (int i = 0; i <= sliced_opcode.x; i++) {
    c->memory[(c->I + i) & 0xFFF] = c->V[i];
  }
}

void op_FX65_load(Chip8 *c, sliced_opcode sliced_opcode) {

  for (int i = 0; i <= sliced_opcode.x; i++) {
    c->V[i] = c->memory[(c->I + i) & 0xFFF];
  }
}
