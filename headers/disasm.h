#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <stddef.h>
#include <stdint.h>
void disassemble_opcode(uint16_t opcode, char *buf, size_t size);

#endif
