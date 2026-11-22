#include "headers/disasm.h"
#include <stdio.h>

void disassemble_opcode(uint16_t opcode, char *buf, size_t size) {
  uint8_t x = (opcode & 0x0F00) >> 8;
  uint8_t y = (opcode & 0x00F0) >> 4;
  uint8_t n = opcode & 0x000F;
  uint8_t nn = opcode & 0x00FF;
  uint16_t nnn = opcode & 0x0FFF;

  snprintf(buf, size, "???");

  switch ((opcode & 0xF000) >> 12) {
  case 0x0:
    switch (opcode) {
    case 0x00E0:
      snprintf(buf, size, "CLS");
      break;
    case 0x00EE:
      snprintf(buf, size, "RET");
      break;
    default:
      snprintf(buf, size, "SYS 0x%03X", nnn);
      break;
    }
    break;

  case 0x1:
    snprintf(buf, size, "JP 0x%03X", nnn);
    break;

  case 0x2:
    snprintf(buf, size, "CALL 0x%03X", nnn);
    break;

  case 0x3:
    snprintf(buf, size, "SE V%X, 0x%02X", x, nn);
    break;

  case 0x4:
    snprintf(buf, size, "SNE V%X, 0x%02X", x, nn);
    break;

  case 0x5:
    if (n == 0)
      snprintf(buf, size, "SE V%X, V%X", x, y);
    break;

  case 0x6:
    snprintf(buf, size, "LD V%X, 0x%02X", x, nn);
    break;

  case 0x7:
    snprintf(buf, size, "ADD V%X, 0x%02X", x, nn);
    break;

  case 0x8:
    switch (n) {
    case 0x0:
      snprintf(buf, size, "LD V%X, V%X", x, y);
      break;
    case 0x1:
      snprintf(buf, size, "OR V%X, V%X", x, y);
      break;
    case 0x2:
      snprintf(buf, size, "AND V%X, V%X", x, y);
      break;
    case 0x3:
      snprintf(buf, size, "XOR V%X, V%X", x, y);
      break;
    case 0x4:
      snprintf(buf, size, "ADD V%X, V%X", x, y);
      break;
    case 0x5:
      snprintf(buf, size, "SUB V%X, V%X", x, y);
      break;
    case 0x6:
      snprintf(buf, size, "SHR V%X, V%X", x, y);
      break;
    case 0x7:
      snprintf(buf, size, "SUBN V%X, V%X", x, y);
      break;
    case 0xE:
      snprintf(buf, size, "SHL V%X, V%X", x, y);
      break;
    }
    break;

  case 0x9:
    if (n == 0)
      snprintf(buf, size, "SNE V%X, V%X", x, y);
    break;

  case 0xA:
    snprintf(buf, size, "LD I, 0x%03X", nnn);
    break;

  case 0xB:
    snprintf(buf, size, "JP V0, 0x%03X", nnn);
    break;

  case 0xC:
    snprintf(buf, size, "RND V%X, 0x%02X", x, nn);
    break;

  case 0xD:
    snprintf(buf, size, "DRW V%X, V%X, %X", x, y, n);
    break;

  case 0xE:
    switch (nn) {
    case 0x9E:
      snprintf(buf, size, "SKP V%X", x);
      break;
    case 0xA1:
      snprintf(buf, size, "SKNP V%X", x);
      break;
    }
    break;

  case 0xF:
    switch (nn) {
    case 0x07:
      snprintf(buf, size, "LD V%X, DT", x);
      break;
    case 0x0A:
      snprintf(buf, size, "LD V%X, K", x);
      break;
    case 0x15:
      snprintf(buf, size, "LD DT, V%X", x);
      break;
    case 0x18:
      snprintf(buf, size, "LD ST, V%X", x);
      break;
    case 0x1E:
      snprintf(buf, size, "ADD I, V%X", x);
      break;
    case 0x29:
      snprintf(buf, size, "LD F, V%X", x);
      break;
    case 0x33:
      snprintf(buf, size, "LD B, V%X", x);
      break;
    case 0x55:
      snprintf(buf, size, "LD [I], V%X", x);
      break;
    case 0x65:
      snprintf(buf, size, "LD V%X, [I]", x);
      break;
    }
    break;
  }
}
