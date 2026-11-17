#ifndef CHIP8_H
#define CHIP8_H

#include <stddef.h>
#include <stdint.h>

#define MEM_SIZE 4096
#define NUM_REGS 16
#define STACK_SIZE 16
#define SCREEN_W 64
#define SCREEN_H 32
#define NUM_KEYS 16
#define PROGRAM_START 0x200
#define FONT_START 0x050

typedef struct {
  uint8_t memory[MEM_SIZE];
  uint8_t V[NUM_REGS];
  uint16_t I;
  uint16_t pc;

  uint16_t stack[STACK_SIZE];
  uint8_t sp;

  uint8_t delay_timer;
  uint8_t sound_timer;

  uint8_t display[SCREEN_H][SCREEN_W];
  uint8_t keys[NUM_KEYS];

} Chip8;

typedef struct {
  uint8_t x;
  uint8_t y;
  uint8_t n;
  uint8_t nn;
  uint16_t nnn;
} sliced_opcode;

void init_chip8(Chip8 *c);
void load_rom(Chip8 *c, uint8_t rom[], size_t rom_size);

void exec_command(Chip8 *c);

#endif
