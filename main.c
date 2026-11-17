#include "headers/chip8.h"

#include <raylib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int keymap[] = {KEY_X,    KEY_ONE, KEY_TWO, KEY_THREE, KEY_Q, KEY_W,
                      KEY_E,    KEY_A,   KEY_S,   KEY_D,     KEY_Z, KEY_C,
                      KEY_FOUR, KEY_R,   KEY_F,   KEY_V};

size_t read_rom(const char *path, uint8_t *buffer, size_t max_size);

int main(int argc, char *argv[]) {

  if (argc != 2) {
    fprintf(stderr, "Not enought arguments.");
    return EXIT_FAILURE;
  }

  srand(time(NULL));

  Chip8 c;
  init_chip8(&c);

  const int MAX_ROM_SIZE = MEM_SIZE - PROGRAM_START;

  uint8_t ibm_rom[MAX_ROM_SIZE];

  size_t ibm_rom_size = read_rom(argv[1], ibm_rom, MAX_ROM_SIZE);

  if (ibm_rom_size == 0) {
    return EXIT_FAILURE;
  }

  load_rom(&c, ibm_rom, ibm_rom_size);

  int cycles_per_frame = 11;

  SetTraceLogLevel(LOG_WARNING);
  InitWindow(SCREEN_W * 10, SCREEN_H * 10, "Chip-8");

  InitAudioDevice();

  Sound beep_sound = LoadSound("resources/beep.wav");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    if (c.sound_timer > 0 && !IsSoundPlaying(beep_sound)) {
      PlaySound(beep_sound);
    } else if (c.sound_timer == 0 && IsSoundPlaying(beep_sound)) {
      StopSound(beep_sound);
    }

    for (int i = 0; i < 16; i++) {
      c.keys[i] = IsKeyDown(keymap[i]);
    }

    for (int i = 0; i < cycles_per_frame; i++) {
      exec_command(&c);
    }

    BeginDrawing();

    DrawFPS(10, 10);

    for (int y = 0; y < SCREEN_H; y++) {
      for (int x = 0; x < SCREEN_W; x++) {
        DrawRectangle(x * 10, y * 10, 10, 10,
                      (&c)->display[y][x] == 0 ? RAYWHITE : BLACK);
      }
    }

    EndDrawing();

    if (c.delay_timer > 0) {
      c.delay_timer--;
    }

    if (c.sound_timer > 0) {
      c.sound_timer--;
    }
  }

  UnloadSound(beep_sound);
  CloseAudioDevice();
  CloseWindow();

  return 0;
}

size_t read_rom(const char *path, uint8_t *buffer, size_t max_size) {
  FILE *rom = fopen(path, "rb");
  if (rom == NULL) {
    perror(path);

    return EXIT_FAILURE;
  }

  size_t rom_size = fread(buffer, 1, max_size, rom);

  if (ferror(rom)) {
    fprintf(stderr, "%s: read error\n", path);
    rom_size = 0;
  } else if (rom_size == 0) {
    fprintf(stderr, "%s: file is empty\n", path);
  } else if (rom_size == max_size && fgetc(rom) != EOF) {
    fprintf(stderr, "%s: ROM is too large (max %zu bytes)\n", path, max_size);
    rom_size = 0;
  }

  fclose(rom);

  return rom_size;
}
