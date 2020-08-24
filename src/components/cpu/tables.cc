#include "components/cpu.hh"

using qnes::cpu;

/**
 * @brief Populates the instruction decoding tables.
 * 
 * Hand-filling three 256 element arrays with 6502 instruction
 * data is a fantastic use of your time. Unfortunately, this
 * function does it for you.
 */
void cpu::populate_tables() {
    addr_table = {
        /* **    00            01            02            03            04            05            06            07            08            09            0A            0B            0C            0D            0E            0F               ** */
        /* 00 */ &cpu::am_IMP, &cpu::am_INX, &cpu::am_IMP, &cpu::am_INX, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_IMP, &cpu::am_IMM, &cpu::am_ACC, &cpu::am_IMM, &cpu::am_ABS, &cpu::am_ABS, &cpu::am_ABS, &cpu::am_ABS, /* 00 */
        /* 10 */ &cpu::am_REL, &cpu::am_INY, &cpu::am_IMP, &cpu::am_INY, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_IMP, &cpu::am_ABY, &cpu::am_IMP, &cpu::am_ZPY, &cpu::am_ABX, &cpu::am_ABX, &cpu::am_ABX, &cpu::am_ABX, /* 10 */
        /* 20 */ &cpu::am_ABS, &cpu::am_IND, &cpu::am_IMP, &cpu::am_INX, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_IMP, &cpu::am_IMM, &cpu::am_ACC, &cpu::am_IMM, &cpu::am_ABS, &cpu::am_ABS, &cpu::am_ABS, &cpu::am_ABS, /* 20 */
        /* 30 */ &cpu::am_REL, &cpu::am_INY, &cpu::am_IMP, &cpu::am_INY, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_IMP, &cpu::am_ABY, &cpu::am_IMP, &cpu::am_ABY, &cpu::am_ABX, &cpu::am_ABX, &cpu::am_ABX, &cpu::am_ABX, /* 30 */
        /* 40 */ &cpu::am_IMP, &cpu::am_INX, &cpu::am_IMP, &cpu::am_INX, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_IMP, &cpu::am_IMM, &cpu::am_ACC, &cpu::am_IMM, &cpu::am_ABS, &cpu::am_ABS, &cpu::am_ABS, &cpu::am_ABS, /* 40 */
        /* 50 */ &cpu::am_REL, &cpu::am_INY, &cpu::am_IMP, &cpu::am_INY, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_IMP, &cpu::am_ABY, &cpu::am_IMP, &cpu::am_ABY, &cpu::am_ABX, &cpu::am_ABX, &cpu::am_ABX, &cpu::am_ABX, /* 50 */
        /* 60 */ &cpu::am_IMP, &cpu::am_INX, &cpu::am_IMP, &cpu::am_INX, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_IMP, &cpu::am_IMM, &cpu::am_ACC, &cpu::am_IMM, &cpu::am_IND, &cpu::am_ABS, &cpu::am_ABS, &cpu::am_ABS, /* 60 */
        /* 70 */ &cpu::am_REL, &cpu::am_INY, &cpu::am_IMP, &cpu::am_INY, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_IMP, &cpu::am_ABY, &cpu::am_IMP, &cpu::am_ABY, &cpu::am_ABX, &cpu::am_ABX, &cpu::am_ABX, &cpu::am_ABX, /* 70 */
        /* 80 */ &cpu::am_IMM, &cpu::am_INX, &cpu::am_IMM, &cpu::am_INX, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_IMP, &cpu::am_IMM, &cpu::am_IMP, &cpu::am_IMM, &cpu::am_ABS, &cpu::am_ABS, &cpu::am_ABS, &cpu::am_ABS, /* 80 */
        /* 90 */ &cpu::am_REL, &cpu::am_INY, &cpu::am_IMP, &cpu::am_INY, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_ZPY, &cpu::am_ZPY, &cpu::am_IMP, &cpu::am_ABY, &cpu::am_IMP, &cpu::am_ABY, &cpu::am_ABX, &cpu::am_ABX, &cpu::am_ABY, &cpu::am_ABY, /* 90 */
        /* A0 */ &cpu::am_IMM, &cpu::am_INX, &cpu::am_IMM, &cpu::am_INX, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_IMP, &cpu::am_IMM, &cpu::am_IMP, &cpu::am_IMM, &cpu::am_ABS, &cpu::am_ABS, &cpu::am_ABS, &cpu::am_ABS, /* A0 */
        /* B0 */ &cpu::am_REL, &cpu::am_INY, &cpu::am_IMP, &cpu::am_INY, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_ZPY, &cpu::am_ZPY, &cpu::am_IMP, &cpu::am_ABY, &cpu::am_IMP, &cpu::am_ABY, &cpu::am_ABX, &cpu::am_ABX, &cpu::am_ABY, &cpu::am_ABY, /* B0 */
        /* C0 */ &cpu::am_IMM, &cpu::am_INX, &cpu::am_IMM, &cpu::am_INX, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_IMP, &cpu::am_IMM, &cpu::am_IMP, &cpu::am_IMM, &cpu::am_ABS, &cpu::am_ABS, &cpu::am_ABS, &cpu::am_ABS, /* C0 */
        /* D0 */ &cpu::am_REL, &cpu::am_INY, &cpu::am_IMP, &cpu::am_INY, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_IMP, &cpu::am_ABY, &cpu::am_IMP, &cpu::am_ABY, &cpu::am_ABX, &cpu::am_ABX, &cpu::am_ABX, &cpu::am_ABX, /* D0 */
        /* E0 */ &cpu::am_IMM, &cpu::am_INX, &cpu::am_IMM, &cpu::am_INX, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_ZPG, &cpu::am_IMP, &cpu::am_IMM, &cpu::am_IMP, &cpu::am_IMM, &cpu::am_ABS, &cpu::am_ABS, &cpu::am_ABS, &cpu::am_ABS, /* E0 */
        /* F0 */ &cpu::am_REL, &cpu::am_INY, &cpu::am_IMP, &cpu::am_INY, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_ZPX, &cpu::am_IMP, &cpu::am_ABY, &cpu::am_IMP, &cpu::am_ABY, &cpu::am_ABX, &cpu::am_ABX, &cpu::am_ABX, &cpu::am_ABX  /* F0 */
        /* **    00            01            02            03            04            05            06            07            08            09            0A            0B            0C            0D            0E            0F               ** */
    };

    op_table = {
        /* **    00            01            02            03            04            05            06            07            08            09            0A            0B            0C            0D            0E            0F               ** */
        /* 00 */ &cpu::op_BRK, &cpu::op_ORA, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_ORA, &cpu::op_ASL, &cpu::op_XXX, &cpu::op_PHP, &cpu::op_ORA, &cpu::op_ASL, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_ORA, &cpu::op_ASL, &cpu::op_XXX, /* 00 */
        /* 10 */ &cpu::op_BPL, &cpu::op_ORA, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_ORA, &cpu::op_ASL, &cpu::op_XXX, &cpu::op_CLC, &cpu::op_ORA, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_AND, &cpu::op_ASL, &cpu::op_XXX, /* 10 */
        /* 20 */ &cpu::op_JSR, &cpu::op_AND, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_BIT, &cpu::op_AND, &cpu::op_ROL, &cpu::op_XXX, &cpu::op_PLP, &cpu::op_AND, &cpu::op_ROL, &cpu::op_XXX, &cpu::op_BIT, &cpu::op_AND, &cpu::op_ROL, &cpu::op_XXX, /* 20 */
        /* 30 */ &cpu::op_BMI, &cpu::op_AND, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_AND, &cpu::op_ROL, &cpu::op_XXX, &cpu::op_SEC, &cpu::op_AND, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_AND, &cpu::op_ROL, &cpu::op_XXX, /* 30 */
        /* 40 */ &cpu::op_RTI, &cpu::op_EOR, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_EOR, &cpu::op_LSR, &cpu::op_XXX, &cpu::op_PHA, &cpu::op_EOR, &cpu::op_LSR, &cpu::op_XXX, &cpu::op_JMP, &cpu::op_EOR, &cpu::op_LSR, &cpu::op_XXX, /* 40 */
        /* 50 */ &cpu::op_BVC, &cpu::op_EOR, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_EOR, &cpu::op_LSR, &cpu::op_XXX, &cpu::op_CLI, &cpu::op_EOR, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_EOR, &cpu::op_LSR, &cpu::op_XXX, /* 50 */
        /* 60 */ &cpu::op_RTS, &cpu::op_ADC, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_ADC, &cpu::op_ROR, &cpu::op_XXX, &cpu::op_PLA, &cpu::op_ADC, &cpu::op_ROR, &cpu::op_XXX, &cpu::op_JMP, &cpu::op_ADC, &cpu::op_ROR, &cpu::op_XXX, /* 60 */
        /* 70 */ &cpu::op_BVS, &cpu::op_ADC, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_ADC, &cpu::op_ROR, &cpu::op_XXX, &cpu::op_SEI, &cpu::op_ADC, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_ADC, &cpu::op_ROR, &cpu::op_XXX, /* 70 */
        /* 80 */ &cpu::op_XXX, &cpu::op_STA, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_STY, &cpu::op_STA, &cpu::op_STX, &cpu::op_XXX, &cpu::op_DEY, &cpu::op_XXX, &cpu::op_TXA, &cpu::op_XXX, &cpu::op_STY, &cpu::op_STA, &cpu::op_STX, &cpu::op_XXX, /* 80 */
        /* 90 */ &cpu::op_BCC, &cpu::op_STA, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_STY, &cpu::op_STA, &cpu::op_STX, &cpu::op_XXX, &cpu::op_TYA, &cpu::op_STA, &cpu::op_TXS, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_STA, &cpu::op_XXX, &cpu::op_XXX, /* 90 */
        /* A0 */ &cpu::op_LDY, &cpu::op_LDA, &cpu::op_LDX, &cpu::op_XXX, &cpu::op_LDY, &cpu::op_LDA, &cpu::op_LDX, &cpu::op_XXX, &cpu::op_TAY, &cpu::op_LDA, &cpu::op_TAX, &cpu::op_XXX, &cpu::op_LDY, &cpu::op_LDA, &cpu::op_LDX, &cpu::op_XXX, /* A0 */
        /* B0 */ &cpu::op_BCS, &cpu::op_LDA, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_LDY, &cpu::op_LDA, &cpu::op_LDX, &cpu::op_XXX, &cpu::op_CLV, &cpu::op_LDA, &cpu::op_TSX, &cpu::op_XXX, &cpu::op_LDY, &cpu::op_LDA, &cpu::op_LDX, &cpu::op_XXX, /* B0 */
        /* C0 */ &cpu::op_CPY, &cpu::op_CMP, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_CPY, &cpu::op_CMP, &cpu::op_DEC, &cpu::op_XXX, &cpu::op_INY, &cpu::op_CMP, &cpu::op_DEX, &cpu::op_XXX, &cpu::op_CPY, &cpu::op_CMP, &cpu::op_DEC, &cpu::op_XXX, /* C0 */
        /* D0 */ &cpu::op_BNE, &cpu::op_CMP, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_CMP, &cpu::op_DEC, &cpu::op_XXX, &cpu::op_CLD, &cpu::op_CMP, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_CMP, &cpu::op_DEC, &cpu::op_XXX, /* D0 */
        /* E0 */ &cpu::op_CPX, &cpu::op_SBC, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_CPX, &cpu::op_SBC, &cpu::op_INC, &cpu::op_XXX, &cpu::op_INX, &cpu::op_SBC, &cpu::op_NOP, &cpu::op_XXX, &cpu::op_CPX, &cpu::op_SBC, &cpu::op_INC, &cpu::op_XXX, /* E0 */
        /* F0 */ &cpu::op_BEQ, &cpu::op_SBC, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_SBC, &cpu::op_INC, &cpu::op_XXX, &cpu::op_SED, &cpu::op_SBC, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_XXX, &cpu::op_SBC, &cpu::op_INC, &cpu::op_XXX  /* F0 */
        /* **    00            01            02            03            04            05            06            07            08            09            0A            0B            0C            0D            0E            0F               ** */
    };

    tick_table = {
        /* **    00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F    ** */
        /* 00 */ 7, 6, 2, 8, 3, 3, 5, 5, 3, 2, 2, 2, 4, 4, 6, 6, /* 00 */
        /* 10 */ 2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7, /* 10 */
        /* 20 */ 6, 6, 2, 8, 3, 3, 5, 5, 4, 2, 2, 2, 4, 4, 6, 6, /* 20 */
        /* 30 */ 2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7, /* 30 */
        /* 40 */ 6, 6, 2, 8, 3, 3, 5, 5, 3, 2, 2, 2, 3, 4, 6, 6, /* 40 */
        /* 50 */ 2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7, /* 50 */
        /* 60 */ 6, 6, 2, 8, 3, 3, 5, 5, 4, 2, 2, 2, 5, 4, 6, 6, /* 60 */
        /* 70 */ 2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7, /* 70 */
        /* 80 */ 2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4, /* 80 */
        /* 90 */ 2, 6, 2, 6, 4, 4, 4, 4, 2, 5, 2, 5, 5, 5, 5, 5, /* 90 */
        /* A0 */ 2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4, /* A0 */
        /* B0 */ 2, 5, 2, 5, 4, 4, 4, 4, 2, 4, 2, 4, 4, 4, 4, 4, /* B0 */
        /* C0 */ 2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6, /* C0 */
        /* D0 */ 2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7, /* D0 */
        /* E0 */ 2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6, /* E0 */
        /* F0 */ 2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7  /* F0 */
        /* **    00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F    ** */
    };
}