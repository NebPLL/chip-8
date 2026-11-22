#include "headers/debug.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int debug_lines = 0;

static const uint8_t keypad_layout[4][4] = {
    {0x1, 0x2, 0x3, 0xC},
    {0x4, 0x5, 0x6, 0xD},
    {0x7, 0x8, 0x9, 0xE},
    {0xA, 0x0, 0xB, 0xF},
};

#define DBG_MESSAGE(fmt, ...)                                                  \
  printf(fmt "\033[K\n", ##__VA_ARGS__);                                       \
  debug_lines++

void start_debug() { printf("\033[?25l"); }

void show_debug(Chip8 *c) {
  debug_lines = 0;

  DBG_MESSAGE("PC: 0x%03X               I:  0x%03X", c->pc, c->I);
  uint16_t opcode = (c->memory[c->pc] << 8) | c->memory[c->pc + 1];
  DBG_MESSAGE("opcode: 0x%04X", opcode);

  DBG_MESSAGE("Delay Timer: %03i        Sound Timer:  %03i", c->delay_timer,
              c->sound_timer);

  DBG_MESSAGE("");

  DBG_MESSAGE("register              stack");

  DBG_MESSAGE("-------------------------------");

  for (size_t i = 0; i < sizeof(c->V); i++) {

    if (i == c->sp) {

      DBG_MESSAGE("V%zX: 0x%02X              S%zX: 0x%03X <- sp", i, c->V[i], i,
                  c->stack[i]);
      continue;
    }

    DBG_MESSAGE("V%zX: 0x%02X              S%zX: 0x%03X", i, c->V[i], i,
                c->stack[i]);
  }
  DBG_MESSAGE("");

  DBG_MESSAGE("keys");

  DBG_MESSAGE("-------------------------------");

  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      uint8_t key = keypad_layout[y][x];
      DBG_MESSAGE("K%X: %s", key, c->keys[key] ? "True" : "False");
    }
  }

  printf("\033[%dA", debug_lines);

  fflush(stdout);
}

void cleanup_debug() {
  printf("\033[%dB", debug_lines);
  printf("\033[?25h");
}
