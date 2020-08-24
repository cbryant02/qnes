#include "components/cpu.hh"

using qnes::cpu;

uint8_t cpu::fetch_operand() {
    if(addr_table[cur_opcode] == &cpu::am_ACC) cur_operand = a;
    else cur_operand = read(addr_abs);
    return cur_operand;
}

void cpu::put_accum(uint16_t result) {
    a = result & 0xFF;
}

void cpu::put(uint16_t result) {
    if(addr_table[cur_opcode] == &cpu::am_ACC) put_accum(result);
    else write(addr_abs, (result & 0xFF));
}

inline bool calc_carry(uint16_t result) {
    return result > 255;
}

inline bool calc_zero(uint16_t result) {
    return (result & 0xFF) == 0;
}

inline bool calc_overflow(uint16_t result, uint8_t acc, uint8_t operand) {
    return ((~(acc ^ operand) & (acc ^ result)) & 0x80);
}

inline bool calc_negative(uint16_t result) {
    return result & 0x80;
}

bool cpu::op_ADC() {
    result = a + fetch_operand() + status.c;
    status.n = calc_negative(result);
    status.z = calc_zero(result);
    status.c = calc_carry(result);
    status.v = calc_overflow(result, a, cur_operand);
    put_accum(result);
    return true;
}

bool cpu::op_AND() {
    result = a & fetch_operand();
    status.n = calc_negative(result);
    status.z = calc_zero(result);
    put_accum(result);
    return true;
}

bool cpu::op_ASL() {
    result = cur_operand << 1;
    status.n = calc_negative(result);
    status.z = calc_zero(result);
    status.c = calc_carry(result);
    put(result);
    return false;
}

bool cpu::op_BCC() {
    if(!status.c) {
        uint16_t prev_pc = pc;
        pc += addr_rel;
        if((prev_pc & 0xFF00) != (pc & 0xFF00)) return true;
    }
    return false;
}

bool cpu::op_BCS() {
    if(status.c) {
        uint16_t prev_pc = pc;
        pc += addr_rel;
        if((prev_pc & 0xFF00) != (pc & 0xFF00)) return true;
    }
    return false;
}

bool cpu::op_BEQ() {
    if(status.z) {
        uint16_t prev_pc = pc;
        pc += addr_rel;
        if((prev_pc & 0xFF00) != (pc & 0xFF00)) return true;
    }
    return false;
}

bool cpu::op_BIT() {
    
    return false;
}

bool cpu::op_BMI() {
    return false;
}

bool cpu::op_BNE() {
    return false;
}

bool cpu::op_BPL() {
    return false;
}

bool cpu::op_BRK() {
    return false;
}

bool cpu::op_BVC() {
    return false;
}

bool cpu::op_BVS() {
    return false;
}

bool cpu::op_CLC() {
    return false;
}

bool cpu::op_CLD() {
    return false;
}

bool cpu::op_CLI() {
    return false;
}

bool cpu::op_CLV() {
    return false;
}

bool cpu::op_CMP() {
    return false;
}

bool cpu::op_CPX() {
    return false;
}

bool cpu::op_CPY() {
    return false;
}

bool cpu::op_DEC() {
    return false;
}

bool cpu::op_DEX() {
    return false;
}

bool cpu::op_DEY() {
    return false;
}

bool cpu::op_EOR() {
    return false;
}

bool cpu::op_INC() {
    return false;
}

bool cpu::op_INX() {
    return false;
}

bool cpu::op_INY() {
    return false;
}

bool cpu::op_JMP() {
    return false;
}

bool cpu::op_JSR() {
    return false;
}

bool cpu::op_LDA() {
    return false;
}

bool cpu::op_LDX() {
    return false;
}

bool cpu::op_LDY() {
    return false;
}

bool cpu::op_LSR() {
    return false;
}

bool cpu::op_NOP() {
    return false;
}

bool cpu::op_ORA() {
    return false;
}

bool cpu::op_PHA() {
    return false;
}

bool cpu::op_PHP() {
    return false;
}

bool cpu::op_PLA() {
    return false;
}

bool cpu::op_PLP() {
    return false;
}

bool cpu::op_ROL() {
    return false;
}

bool cpu::op_ROR() {
    return false;
}

bool cpu::op_RTI() {
    return false;
}

bool cpu::op_RTS() {
    return false;
}

bool cpu::op_SBC() {
    return false;
}

bool cpu::op_SEC() {
    return false;
}

bool cpu::op_SED() {
    return false;
}

bool cpu::op_SEI() {
    return false;
}

bool cpu::op_STA() {
    return false;
}

bool cpu::op_STX() {
    return false;
}

bool cpu::op_STY() {
    return false;
}

bool cpu::op_TAX() {
    return false;
}

bool cpu::op_TAY() {
    return false;
}

bool cpu::op_TSX() {
    return false;
}

bool cpu::op_TXA() {
    return false;
}

bool cpu::op_TXS() {
    return false;
}

bool cpu::op_TYA() {
    return false;
}

bool cpu::op_XXX() {
    return op_NOP();
}