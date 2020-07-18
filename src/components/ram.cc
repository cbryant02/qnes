#include "components/ram.hh"
#include <algorithm>

using qnes::ram;

ram::ram() {
}

ram::~ram() {
}

// effectively does nothing for now
inline bool check_bounds(uint16_t addr) {
    return addr >= 0x0000 && addr <= 0xFFFF;
}

/**
 * @brief Write a value to a single address.
 * 
 * @param addr Address to write to
 * @param data Value to write
 */
void ram::write(uint16_t addr, uint8_t data) {
    if (check_bounds(addr)) {
        memory[addr] = data;
    }
}

/**
 * @brief Write a value to all cells within an address range.
 * 
 * @param start Start of address range to write to
 * @param end End of address range to write to
 * @param data Value to write
 */
void ram::write_range(uint16_t start, uint16_t end, uint8_t data) {
    if (check_bounds(start) && check_bounds(end)) {
        std::fill(memory.begin() + start, memory.begin() + end, data);
    }
}

/**
 * @brief Read a single value.
 * 
 * @param addr Address to read from
 * @return uint8_t The value at the address
 */
uint8_t ram::read(uint16_t addr) {
    if (check_bounds(addr)) {
        return memory[addr];
    }
    return 0x00;
}

/**
 * @brief Read all values within an address range.
 * 
 * @param start Start of address range to read from
 * @param end End of address range to read from
 * @param buf Buffer to write data into
 */
void ram::read_range(uint16_t start, uint16_t end, uint8_t buf[]) {
    if (check_bounds(start) && check_bounds(end)) {
        std::copy(memory.begin() + start, memory.begin() + end, buf);
    }
}