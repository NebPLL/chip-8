#include "headers/chip8.h"
#include "headers/fn_0.h"
#include "headers/fn_1.h"
#include "headers/fn_2.h"
#include "headers/fn_3.h"
#include "headers/fn_4.h"
#include "headers/fn_5.h"
#include "headers/fn_6.h"
#include "headers/fn_7.h"
#include "headers/fn_8.h"
#include "headers/fn_9.h"
#include "headers/fn_A.h"
#include "headers/fn_B.h"
#include "headers/fn_C.h"
#include "headers/fn_D.h"
#include "headers/fn_E.h"
#include "headers/fn_F.h"

#include <raylib.h>
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

const int keymap[] = {KEY_X,    KEY_ONE, KEY_TWO, KEY_THREE, KEY_Q, KEY_W,
                      KEY_E,    KEY_A,   KEY_S,   KEY_D,     KEY_Z, KEY_C,
                      KEY_FOUR, KEY_R,   KEY_F,   KEY_V};

bool keys[16];

bool *getKeys() { return keys; }

void update_keys() {
  for (int i = 0; i < 16; i++) {
    keys[i] = IsKeyDown(keymap[i]);
  }
}

void init_chip8(Chip8 *c) {
  memset(c, 0, sizeof(*c));
  c->pc = PROGRAM_START;
  memcpy(&c->memory[FONT_START], fontset, sizeof(fontset));
}

void load_rom(Chip8 *c, uint8_t rom[], size_t rom_size) {
  memcpy(&c->memory[PROGRAM_START], rom, rom_size);
}

void exec_command(Chip8 *c) {
  uint16_t opcode = (c->memory[c->pc] << 8) | c->memory[c->pc + 1];
  c->pc += 2;

  uint8_t x = (opcode & 0x0F00) >> 8; // zweites Nibble
  uint8_t y = (opcode & 0x00F0) >> 4; // drittes Nibble
  uint8_t n = opcode & 0x000F;        // letztes Nibble
  uint8_t nn = opcode & 0x00FF;       // letztes Byte
  uint16_t nnn = opcode & 0x0FFF;     // Adresse

  sliced_opcode sliced_opcode = {.x = x, .y = y, .n = n, .nn = nn, .nnn = nnn};

  switch ((opcode & 0xF000) >> 12) {

  case 0x0:
    decode_fn0(c, opcode);

    break;

  case 0x1:

    decode_fn1(c, opcode, sliced_opcode);

    break;

  case 0x2:

    decode_fn2(c, opcode, sliced_opcode);

    break;

  case 0x3:
    decode_fn3(c, opcode, sliced_opcode);

    break;

  case 0x4:
    decode_fn4(c, opcode, sliced_opcode);

    break;

  case 0x5:
    decode_fn5(c, opcode, sliced_opcode);

    break;

  case 0x6:
    decode_fn6(c, opcode, sliced_opcode);

    break;

  case 0x7:
    decode_fn7(c, opcode, sliced_opcode);

    break;

  case 0x8:
    decode_fn8(c, opcode, sliced_opcode);

    break;

  case 0x9:
    decode_fn9(c, opcode, sliced_opcode);

    break;

  case 0xA:
    decode_fnA(c, opcode, sliced_opcode);

    break;

  case 0xB:
    decode_fnB(c, opcode, sliced_opcode);

    break;

  case 0xC:
    decode_fnC(c, opcode, sliced_opcode);

    break;

  case 0xD:
    decode_fnD(c, opcode, sliced_opcode);

    break;

  case 0xE:
    decode_fnE(c, opcode, sliced_opcode);

    break;

  case 0xF:
    decode_fnF(c, opcode, sliced_opcode);

    break;

  default:
    printf("Opencode not found (0):%i\n", opcode);
  }
}
