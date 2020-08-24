#include "components/cpu.hh"

using qnes::cpu;

/**
 * @brief Absolute
 * 
 * @return true if a subsequent instruction might require an additional cycle
 * @return false if no additional cycle is required
 */
bool cpu::am_ABS() {
    addr_abs = read(pc) | (read(pc+1) << 8);
    pc += 2;
    return false;
}

/**
 * @brief Absolute, X-indexed
 * 
 * @return true if a subsequent instruction might require an additional cycle
 * @return false if no additional cycle is required
 */
bool cpu::am_ABX() {
    addr_abs = read(pc) | (read(pc) << 8);
    uint16_t original_page = addr_abs & 0xFF00;
    addr_abs += x;

    pc += 2;

    // Potential one-cycle penalty for page wrapping on read opcodes
    if ((addr_abs & 0xFF00) != original_page) {
        return true;
    }

    return false;
}   

/**
 * @brief Absolute, Y-indexed
 * 
 * @return true if a subsequent instruction might require an additional cycle
 * @return false if no additional cycle is required
 */
bool cpu::am_ABY() {
    addr_abs = read(pc) | (read(pc) << 8);
    uint16_t original_page = addr_abs & 0xFF00;
    addr_abs += y;

    pc += 2;

    // Potential one-cycle penalty for page wrapping on read opcodes
    if ((addr_abs & 0xFF00) != original_page) {
        return true;
    }

    return false;
}

/**
 * @brief Accumulator
 * 
 * @return true if a subsequent instruction might require an additional cycle
 * @return false if no additional cycle is required
 */
bool cpu::am_ACC() {
    return false;
}

/**
 * @brief Immediate
 * 
 * @return true if a subsequent instruction might require an additional cycle
 * @return false if no additional cycle is required
 */
bool cpu::am_IMM() {
    addr_abs = pc++;
    return false;
}

/**
 * @brief Implied
 * 
 * @return true if a subsequent instruction might require an additional cycle
 * @return false if no additional cycle is required
 */
bool cpu::am_IMP() {
    return false;
}

/**
 * @brief Indirect
 * 
 * @return true if a subsequent instruction might require an additional cycle
 * @return false if no additional cycle is required
 */
bool cpu::am_IND() {
    uint16_t ptr = read(pc) | (read(pc) << 8);
    uint16_t bugged_ptr = (ptr & 0xFF00) | ((ptr+1) & 0x00FF); // Replicate page wrapping bug
    addr_abs = read(ptr) | (read(bugged_ptr) << 8);

    pc += 2;
    return false;
}

/**
 * @brief Indirect, X-indexed
 * 
 * @return true if a subsequent instruction might require an additional cycle
 * @return false if no additional cycle is required
 */
bool cpu::am_INX() {
    uint16_t ptr = read(pc);
    addr_abs = read((ptr + x) & 0x00FF) | (read((ptr + x + 1) & 0x00FF) << 8);

    pc += 2;
    return false;
}

/**
 * @brief Indirect, Y-indexed
 * 
 * @return true if a subsequent instruction might require an additional cycle
 * @return false if no additional cycle is required
 */
bool cpu::am_INY() {
    uint16_t ptr = read(pc);
    addr_abs = read((ptr + x) & 0x00FF) | (read((ptr + x + 1) & 0x00FF) << 8);

    pc += 2;
    return false;
}

/**
 * @brief Relative
 * 
 * @return true if a subsequent instruction might require an additional cycle
 * @return false if no additional cycle is required
 */
bool cpu::am_REL() {
    addr_rel = read(pc++);
    if (addr_rel & 0x80) addr_rel |= 0xFF00;
    return false;
}

/**
 * @brief Zeropage absolute
 * 
 * @return true if a subsequent instruction might require an additional cycle
 * @return false if no additional cycle is required
 */
bool cpu::am_ZPG() {
    addr_abs = read(pc++);
    return false;
}

/**
 * @brief Zeropage absolute, X-offset
 * 
 * @return true if a subsequent instruction might require an additional cycle
 * @return false if no additional cycle is required
 */
bool cpu::am_ZPX() {
    addr_abs = (read(pc++) + x) & 0xFF;
    return false;
}

/**
 * @brief Zeropage absolute, Y-offset
 * 
 * @return true if a subsequent instruction might require an additional cycle
 * @return false if no additional cycle is required
 */
bool cpu::am_ZPY() {
    addr_abs = (read(pc++) + y) & 0xFF;
    return false;
}