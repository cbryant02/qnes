#pragma once

#include <cstdint>
#include <bitset>
#include <array>

namespace qnes {
// forward dec
class ram;

class cpu {
private:
    qnes::ram* ram;
    std::array<bool (cpu::*)(void), 256> addr_table;
    std::array<bool (cpu::*)(void), 256> op_table;
    std::array<uint8_t, 256> tick_table;

    void populate_tables();
    uint8_t fetch_operand();
    void put_accum(uint16_t result);
    void put(uint16_t result);

public:
    // Addressing modes
    bool am_ABS(); bool am_ABX(); bool am_ABY();   // absolute, absolute x/y indexed
    bool am_IND(); bool am_INX(); bool am_INY();   // indirect, indirect x/y indexed
    bool am_ZPG(); bool am_ZPX(); bool am_ZPY();   // zeropage, zeropage x/y indexed
    bool am_ACC();                                 // accumulator
    bool am_IMM();                                 // immediate
    bool am_IMP();                                 // implied
    bool am_REL();                                 // relative

    // Instructions
    bool op_ADC(); bool op_AND(); bool op_ASL(); bool op_BCC();
    bool op_BCS(); bool op_BEQ(); bool op_BIT(); bool op_BMI();
    bool op_BNE(); bool op_BPL(); bool op_BRK(); bool op_BVC();
    bool op_BVS(); bool op_CLC(); bool op_CLD(); bool op_CLI();
    bool op_CLV(); bool op_CMP(); bool op_CPX(); bool op_CPY();
    bool op_DEC(); bool op_DEX(); bool op_DEY(); bool op_EOR();
    bool op_INC(); bool op_INX(); bool op_INY(); bool op_JMP();
    bool op_JSR(); bool op_LDA(); bool op_LDX(); bool op_LDY();
    bool op_LSR(); bool op_NOP(); bool op_ORA(); bool op_PHA();
    bool op_PHP(); bool op_PLA(); bool op_PLP(); bool op_ROL();
    bool op_ROR(); bool op_RTI(); bool op_RTS(); bool op_SBC();
    bool op_SEC(); bool op_SED(); bool op_SEI(); bool op_STA();
    bool op_STX(); bool op_STY(); bool op_TAX(); bool op_TAY();
    bool op_TSX(); bool op_TXA(); bool op_TXS(); bool op_TYA();
    bool op_XXX();  // placeholder for unimplemented instructions

    // Status flags wrapper
    struct flags {
        bool c = false; // 0 Carry
        bool z = false; // 1 Zero
        bool i = false; // 2 Interrupt disable
        bool d = false; // 3 BCD mode (no effect)
        // Bits 4 and 5 are a government secret
        bool v = false; // 6 Overflow
        bool n = false; // 7 Negative

        flags() {
        }

        flags(uint8_t raw) {
            update(raw);
        }

        uint8_t uint() {
            return c | z << 1 | i << 2 | d << 3 | v << 6 | n << 7;
        }

        auto& operator=(uint8_t raw) {
            update(raw);
            return *this;
        }

    private:
        void update(uint8_t raw) {
            std::bitset<8> bits(raw);
            c = bits[0];
            z = bits[1];
            i = bits[2];
            d = bits[3];
            v = bits[6];
            n = bits[7];
        }
    };

public:
    // Constructor and destructor

    /**
     * @brief Construct a new cpu object
     * @param ram Pointer to a ram instance
     */
    cpu(qnes::ram* memory);

    /**
     * @brief Destroy the cpu object
     */
    ~cpu();

    // 6502 registers
    uint8_t  a;         // Accumulator
    uint8_t  x;         // X register
    uint8_t  y;         // Y register
    uint16_t pc;        // Program counter
    uint8_t  sp;        // Stack pointer
    flags    status;    // Status register

    // Emulation stuff
    uint8_t  cur_opcode;        // Opcode of current instruction
    uint16_t cur_operand;       // Operand of current instruction
    uint16_t result;            // Used to temporarily store op results
    uint16_t addr_abs;          // Absolute address used for most addressing modes
    uint16_t addr_rel;          // Relative address for branch instructions
    uint8_t  cycles_remaining;  // Clock cycles remaining in the current instruction
    uint64_t clock_count;       // Total # of clock cycles since reset

    /**
     * @brief Perform a single clock cycle.
     */
    void cycle();

    /**
     * @brief Reset the CPU.
     * The CPU will be forced into a known state and
     * begin executing from the beginning of the
     * ROM after 6 clock cycles.
     */
    void reset();

    /**
     * @brief Request an interrupt.
     */
    void irq();

    /**
     * @brief Force an interrupt.
     */
    void nmi();

    /**
     * @brief Write a byte to somewhere in the memory space.
     * For now, we only handle writing to RAM.
     * 
     * @param addr 
     * @param data 
     */
    void write(uint16_t addr, uint8_t data);

    /**
     * @brief Read a byte from somewhere in the memory space.
     * For now, we only handle reading from RAM.
     * 
     * @param addr 
     * @return uint8_t 
     */
    uint8_t read(uint16_t addr);
};
}