#include "headers/chip8.h"
#include "headers/debug.h"

#include <raylib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

size_t read_rom(const char *path, uint8_t *buffer, size_t max_size);

static bool parse_int(const char *str, long min, long max, int *out);

int main(int argc, char *argv[]) {

  if (argc != 3) {
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

  int ipf; // Instructions per Frame

  if (argc < 2 || !parse_int(argv[2], 1, 1000, &ipf)) {
    fprintf(stderr, "Benutzung: %s <instruktionen pro frame (1-1000)>\n",
            argv[0]);
    return 1;
  }

  SetTraceLogLevel(LOG_WARNING);
  InitWindow(SCREEN_W * 10, SCREEN_H * 10, "Chip-8");

  InitAudioDevice();

  Sound beep_sound = LoadSound("resources/beep.wav");

  SetTargetFPS(60);

  start_debug();

  while (!WindowShouldClose()) {

    show_debug(&c);

    if (c.sound_timer > 0 && !IsSoundPlaying(beep_sound)) {
      PlaySound(beep_sound);
    } else if (c.sound_timer == 0 && IsSoundPlaying(beep_sound)) {
      StopSound(beep_sound);
    }

    for (int i = 0; i < 16; i++) {
      c.keys[i] = IsKeyDown(keymap[i]);
    }

    for (int i = 0; i < ipf; i++) {
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

  cleanup_debug();

  UnloadSound(beep_sound);
  CloseAudioDevice();
  CloseWindow();

  return 0;
}

size_t read_rom(const char *path, uint8_t *buffer, size_t max_size) {
  FILE *rom = fopen(path, "rb");
  if (rom == NULL) {
    perror(path);

    return 0;
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

static bool parse_int(const char *str, long min, long max, int *out) {
  char *end;
  long value = strtol(str, &end, 0);

  if (end == str || *end != '\0' || value < min || value > max)
    return false;

  *out = (int)value;
  return true;
}
