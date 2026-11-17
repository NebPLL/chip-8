#include "headers/chip8.h"
#include "tests_roms/chip8_logo_rom.h"
#include "tests_roms/font_rom.h"
#include "tests_roms/ibm_rom.h"

#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

const int keymap[] = {KEY_X,    KEY_ONE, KEY_TWO, KEY_THREE, KEY_Q, KEY_W,
                      KEY_E,    KEY_A,   KEY_S,   KEY_D,     KEY_Z, KEY_C,
                      KEY_FOUR, KEY_R,   KEY_F,   KEY_V};

int main(void) {
  srand(time(NULL));

  Chip8 c;
  init_chip8(&c);
  uint8_t MAZE_ROM[] = {
      // --- Start ---
      0x00,
      0xE0, // 0x200: 00E0  Bildschirm löschen
      0x60,
      0x00, // 0x202: 6000  V0 = 0   x
      0x61,
      0x00, // 0x204: 6100  V1 = 0   y

      // --- Zufällige Kachel wählen ---
      0xA2,
      0x2C, // 0x206: A22C  I = Sprite "/"
      0xC2,
      0x01, // 0x208: C201  V2 = zufällig 0 oder 1
      0x32,
      0x00, // 0x20A: 3200  V2 == 0 -> nächste überspringen
      0xA2,
      0x30, // 0x20C: A230  I = Sprite "\"
      0xD0,
      0x14, // 0x20E: D014  Kachel zeichnen (4 Zeilen)

      // --- Kurz warten, damit man das Aufbauen sieht ---
      0x63,
      0x01, // 0x210: 6301  V3 = 1
      0xF3,
      0x15, // 0x212: F315  Delay-Timer = 1
      0xF3,
      0x07, // 0x214: F307  V3 = Delay-Timer
      0x33,
      0x00, // 0x216: 3300  V3 == 0 -> nächste überspringen
      0x12,
      0x14, // 0x218: 1214  zurück zu 0x214

      // --- Nächste Spalte ---
      0x70,
      0x04, // 0x21A: 7004  V0 += 4
      0x30,
      0x40, // 0x21C: 3040  V0 == 64 -> nächste überspringen
      0x12,
      0x06, // 0x21E: 1206  nächste Kachel

      // --- Nächste Zeile ---
      0x60,
      0x00, // 0x220: 6000  V0 = 0
      0x71,
      0x04, // 0x222: 7104  V1 += 4
      0x31,
      0x20, // 0x224: 3120  V1 == 32 -> nächste überspringen
      0x12,
      0x06, // 0x226: 1206  nächste Kachel

      // --- Fertig: auf Taste warten, dann neu ---
      0xF2,
      0x0A, // 0x228: F20A  auf Taste warten
      0x12,
      0x00, // 0x22A: 1200  neu starten

      // --- Sprites (je 4 Zeilen) ---
      0x10,
      0x20,
      0x40,
      0x80, // 0x22C: Sprite "/"

      0x80,
      0x40,
      0x20,
      0x10, // 0x230: Sprite "\"
  };

  load_rom(&c, MAZE_ROM, sizeof(MAZE_ROM));

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
