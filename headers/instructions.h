#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "chip8.h"

void op_00E0_cls(Chip8 *c);
void op_00EE_ret(Chip8 *c);

void op_1NNN_jump(Chip8 *c, sliced_opcode sliced_opcode);

void op_2NNN_call(Chip8 *c, sliced_opcode sliced_opcode);

void op_3XNN_skip_eq(Chip8 *c, sliced_opcode sliced_opcode);

void op_4XNN_skip_neq(Chip8 *c, sliced_opcode sliced_opcode);

void op_5XY0_skip_eq_reg(Chip8 *c, sliced_opcode sliced_opcode);

void op_6XNN_set(Chip8 *c, sliced_opcode sliced_opcode);

void op_7XNN_add(Chip8 *c, sliced_opcode sliced_opcode);

void op_8XY0_copy(Chip8 *c, sliced_opcode sliced_opcode);
void op_8XY1_or(Chip8 *c, sliced_opcode sliced_opcode);
void op_8XY2_and(Chip8 *c, sliced_opcode sliced_opcode);
void op_8XY3_xor(Chip8 *c, sliced_opcode sliced_opcode);
void op_8XY4_add(Chip8 *c, sliced_opcode sliced_opcode);
void op_8XY5_sub(Chip8 *c, sliced_opcode sliced_opcode);
void op_8XY6_shr(Chip8 *c, sliced_opcode sliced_opcode);
void op_8XY7_subn(Chip8 *c, sliced_opcode sliced_opcode);
void op_8XYE_shl(Chip8 *c, sliced_opcode sliced_opcode);

void op_9XY0_skip_neq_reg(Chip8 *c, sliced_opcode sliced_opcode);

void op_ANNN_set_i(Chip8 *c, sliced_opcode sliced_opcode);

void op_BXNN_jump_vx(Chip8 *c, sliced_opcode sliced_opcode);

void op_CXNN_rand(Chip8 *c, sliced_opcode sliced_opcode);

void op_DXYN_draw(Chip8 *c, sliced_opcode sliced_opcode);

void op_EX9E_skip_key(Chip8 *c, sliced_opcode sliced_opcode);
void op_EXA1_skip_nkey(Chip8 *c, sliced_opcode sliced_opcode);

void op_FX07_get_delay(Chip8 *c, sliced_opcode sliced_opcode);

void op_FX15_set_delay(Chip8 *c, sliced_opcode sliced_opcode);
void op_FX18_set_sound(Chip8 *c, sliced_opcode sliced_opcode);
void op_FX1E_add_i(Chip8 *c, sliced_opcode sliced_opcode);
void op_FX0A_wait_key(Chip8 *c, sliced_opcode sliced_opcode);
void op_FX29_font(Chip8 *c, sliced_opcode sliced_opcode);
void op_FX33_bcd(Chip8 *c, sliced_opcode sliced_opcode);
void op_FX55_store(Chip8 *c, sliced_opcode sliced_opcode);
void op_FX65_load(Chip8 *c, sliced_opcode sliced_opcode);
#endif
