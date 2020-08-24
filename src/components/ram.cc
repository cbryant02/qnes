#include "components/ram.hh"
#include <algorithm>

using qnes::ram;

void ram::write(uint16_t addr, uint8_t data) {
    memory[addr] = data;
}

uint8_t ram::read(uint16_t addr) {
    return memory[addr];
}

void ram::write_range(uint16_t start, uint16_t end, uint8_t data) {
    std::fill(memory.begin() + start, memory.begin() + end, data);
}

void ram::read_range(uint16_t start, uint16_t end, uint8_t buf[]) {
    std::copy(memory.begin() + start, memory.begin() + end, buf);
}