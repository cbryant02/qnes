#include "components/cpu.hh"
#include "components/ram.hh"

using qnes::cpu;

/**
 * @brief Construct a new cpu object
 * @param ram Pointer to a ram instance
 */
cpu::cpu(qnes::ram* ram) {
    this->ram = ram;
    a = 0x00;
    x = 0x00;
    y = 0x00;
    
    sp = 0xFD;
    status = 0x34;
}

/**
 * @brief Destroy the cpu object
 */
cpu::~cpu() {
}

/**
 * @brief Perform a clock cycle.
 */
void cpu::cycle() {
}

/**
 * @brief Reset the CPU.
 * The CPU will reset to a known state and
 * begin executing instructions again after
 * 6 clock cycles.
 */
void cpu::reset() {

}

/**
 * @brief Request an interrupt.
 */
void cpu::irq() {

}

/**
 * @brief Force an interrupt.
 */
void cpu::nmi() {

}