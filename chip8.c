#include "headers/chip8.h"
#include "headers/instructions.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static const uint8_t fontset[80] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, 0x20, 0x60, 0x20, 0x20, 0x70, 0xF0, 0x10,
    0xF0, 0x80, 0xF0, 0xF0, 0x10, 0xF0, 0x10, 0xF0, 0x90, 0x90, 0xF0, 0x10,
    0x10, 0xF0, 0x80, 0xF0, 0x10, 0xF0, 0xF0, 0x80, 0xF0, 0x90, 0xF0, 0xF0,
    0x10, 0x20, 0x40, 0x40, 0xF0, 0x90, 0xF0, 0x90, 0xF0, 0xF0, 0x90, 0xF0,
    0x10, 0xF0, 0xF0, 0x90, 0xF0, 0x90, 0x90, 0xE0, 0x90, 0xE0, 0x90, 0xE0,
    0xF0, 0x80, 0x80, 0x80, 0xF0, 0xE0, 0x90, 0x90, 0x90, 0xE0, 0xF0, 0x80,
    0xF0, 0x80, 0xF0, 0xF0, 0x80, 0xF0, 0x80, 0x80};

void init_chip8(Chip8 *c) {
  memset(c, 0, sizeof(*c));
  c->pc = PROGRAM_START;
  memcpy(&c->memory[FONT_START], fontset, sizeof(fontset));
}

void load_rom(Chip8 *c, uint8_t rom[], size_t rom_size) {
  memcpy(&c->memory[PROGRAM_START], rom, rom_size);
}

void exec_command(Chip8 *c) {
  uint16_t opcode =
      (c->memory[c->pc & 0xFFF] << 8) | c->memory[(c->pc + 1) & 0xFFF];
  c->pc += 2;

  uint8_t x = (opcode & 0x0F00) >> 8;
  uint8_t y = (opcode & 0x00F0) >> 4;
  uint8_t n = opcode & 0x000F;
  uint8_t nn = opcode & 0x00FF;
  uint16_t nnn = opcode & 0x0FFF;

  sliced_opcode sliced_opcode = {.x = x, .y = y, .n = n, .nn = nn, .nnn = nnn};

  switch ((opcode & 0xF000) >> 12) {

  case 0x0: {

    switch (opcode) {
    case 0x00E0:
      op_00E0_cls(c);

      break;

    case 0x00EE:
      op_00EE_ret(c);

      break;

    default:
      printf("Opcode not found (1):%04X\n", opcode);
    }
    break;
  }

  case 0x1:

    op_1NNN_jump(c, sliced_opcode);

    break;

  case 0x2:

    op_2NNN_call(c, sliced_opcode);

    break;

  case 0x3:

    op_3XNN_skip_eq(c, sliced_opcode);

    break;

  case 0x4:
    op_4XNN_skip_neq(c, sliced_opcode);

    break;

  case 0x5:
    op_5XY0_skip_eq_reg(c, sliced_opcode);

    break;

  case 0x6:
    op_6XNN_set(c, sliced_opcode);

    break;

  case 0x7:
    op_7XNN_add(c, sliced_opcode);

    break;

  case 0x8: {
    switch (opcode & 0x000F) {
    case 0:
      op_8XY0_copy(c, sliced_opcode);
      break;

    case 1:
      op_8XY1_or(c, sliced_opcode);
      break;

    case 2:
      op_8XY2_and(c, sliced_opcode);
      break;
    case 3:
      op_8XY3_xor(c, sliced_opcode);
      break;

    case 4:
      op_8XY4_add(c, sliced_opcode);
      break;

    case 5:
      op_8XY5_sub(c, sliced_opcode);
      break;

    case 0x6:
      op_8XY6_shr(c, sliced_opcode);
      break;
    case 7:
      op_8XY7_subn(c, sliced_opcode);
      break;

    case 0xE: {
      op_8XYE_shl(c, sliced_opcode);
      break;
    }

    default:
      printf("Opcode not found (8):%04X\n", opcode);
    }
    break;
  }

  case 0x9:
    op_9XY0_skip_neq_reg(c, sliced_opcode);

    break;

  case 0xA:
    op_ANNN_set_i(c, sliced_opcode);

    break;

  case 0xB:
    op_BXNN_jump_vx(c, sliced_opcode);

    break;

  case 0xC:
    op_CXNN_rand(c, sliced_opcode);

    break;

  case 0xD:
    op_DXYN_draw(c, sliced_opcode);

    break;

  case 0xE: {

    switch (opcode & 0x00FF) {
    case 0x9E:
      op_EX9E_skip_key(c, sliced_opcode);

      break;

    case 0xA1:
      op_EXA1_skip_nkey(c, sliced_opcode);

      break;

    default:
      printf("Opcode not found (E):%04X\n", opcode);
    }
    break;
  }

  case 0xF: {
    switch (opcode & 0x00FF) {
    case 0x0007:
      op_FX07_get_delay(c, sliced_opcode);
      break;

    case 0x0015:
      op_FX15_set_delay(c, sliced_opcode);
      break;

    case 0x0018:
      op_FX18_set_sound(c, sliced_opcode);
      break;

    case 0x001E:
      op_FX1E_add_i(c, sliced_opcode);
      break;

    case 0x000A:
      op_FX0A_wait_key(c, sliced_opcode);
      break;

    case 0x0029:
      op_FX29_font(c, sliced_opcode);
      break;

    case 0x0033:
      op_FX33_bcd(c, sliced_opcode);
      break;

    case 0x0055:
      op_FX55_store(c, sliced_opcode);

      break;

    case 0x0065:
      op_FX65_load(c, sliced_opcode);

      break;

    default:
      printf("Opcode not found (F):%04X\n", opcode);
    }
    break;
  }
  }
}
