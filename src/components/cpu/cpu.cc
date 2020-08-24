#include "components/cpu.hh"
#include "components/ram.hh"

#include <vector>

using qnes::cpu;

cpu::cpu(qnes::ram* memory) {
    this->ram = memory;
    a = 0x00;
    x = 0x00;
    y = 0x00;
    
    sp = 0xFD;
    status = 0x34;
    populate_tables();
}

cpu::~cpu() {
}

void cpu::cycle() {
}

void cpu::reset() {
    a = 0x00;
    x = 0x00;
    y = 0x00;
    sp = 0xFD;
    status = 0x34;
}

void cpu::irq() {

}

void cpu::nmi() {

}

void cpu::write(uint16_t addr, uint8_t data) {
    ram->write(addr, data);
}

uint8_t cpu::read(uint16_t addr) {
    return ram->read(addr);
}