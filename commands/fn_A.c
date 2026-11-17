// name = f (first), n (nibble), 1. Es heisst das erste nibble A ist.
#include "../headers/fn_A.h"

void decode_fnA(Chip8 *c, uint16_t opcode, sliced_opcode sliced_opcode) {
  c->I = sliced_opcode.nnn;
}
