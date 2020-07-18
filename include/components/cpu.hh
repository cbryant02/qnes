/**
 * @class qnes::cpu
 * @author Cole Bryant (cole.z.bryant02@gmail.com)
 * @brief The core emulation class for the 2A03 CPU.
 */

#pragma once

#include <cstdint>
#include <bitset>

namespace qnes {
    // forward decs
    class ram;

    class cpu {
    private:
        qnes::ram* ram;

    public:
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

        // Constructor and destructor
        cpu(qnes::ram* ram);
        ~cpu();

        // 6502 registers
        uint8_t a;      // Accumulator
        uint8_t x;      // X register
        uint8_t y;      // Y register
        uint16_t pc;    // Program counter
        uint8_t sp;     // Stack pointer
        flags status;   // Status register

        // Emulator stuff
        uint8_t cycles_remaining;   // Clock cycles remaining in the current instruction
        uint64_t clock_count;       // Total # of clock cycles since reset

        // Signals
        void cycle();
        void reset();
        void irq();
        void nmi();

        // Addressing modes
        uint8_t am_ABS(); uint8_t am_ABS_X(); uint8_t am_ABS_Y();   // absolute, absolute x/y indexed
        uint8_t am_IND(); uint8_t am_IND_X(); uint8_t am_IND_Y();   // indirect, indirect x/y indexed
        uint8_t am_ZPG(); uint8_t am_ZPG_X(); uint8_t am_ZPG_Y();   // zeropage, zeropage x/y indexed
        uint8_t am_ACC();                                           // accumulator
        uint8_t am_IMM();                                           // immediate
        uint8_t am_IMP();                                           // implied
        uint8_t am_REL();                                           // relative

        // Official instruction set
        uint8_t op_ADC(); uint8_t op_AND(); uint8_t op_ASL(); uint8_t op_BCC();
        uint8_t op_BCS(); uint8_t op_BEQ(); uint8_t op_BIT(); uint8_t op_BMI();
        uint8_t op_BNE(); uint8_t op_BPL(); uint8_t op_BRK(); uint8_t op_BVC();
        uint8_t op_BVS(); uint8_t op_CLC(); uint8_t op_CLD(); uint8_t op_CLI();
        uint8_t op_CLV(); uint8_t op_CMP(); uint8_t op_CPX(); uint8_t op_CPY();
        uint8_t op_DEC(); uint8_t op_DEX(); uint8_t op_DEY(); uint8_t op_EOR();
        uint8_t op_INC(); uint8_t op_INX(); uint8_t op_INY(); uint8_t op_JMP();
        uint8_t op_JSR(); uint8_t op_LDA(); uint8_t op_LDX(); uint8_t op_LDY();
        uint8_t op_LSR(); uint8_t op_NOP(); uint8_t op_ORA(); uint8_t op_PHA();
        uint8_t op_PHP(); uint8_t op_PLA(); uint8_t op_PLP(); uint8_t op_ROL();
        uint8_t op_ROR(); uint8_t op_RTI(); uint8_t op_RTS(); uint8_t op_SBC();
        uint8_t op_SEC(); uint8_t op_SED(); uint8_t op_SEI(); uint8_t op_STA();
        uint8_t op_STX(); uint8_t op_STY(); uint8_t op_TAX(); uint8_t op_TAY();
        uint8_t op_TSX(); uint8_t op_TXA(); uint8_t op_TXS(); uint8_t op_TYA();

        // NOP capture for operations that haven't been implemented yet.
        // For now this consists of all the unofficial instructions.
        uint8_t op_null();
    };
}