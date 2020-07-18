#pragma once

#include <cstdint>
#include <array>

namespace qnes {
    class ram {
    private:
        std::array<uint8_t, 0xFFFF> memory;

    public:
        ram();
        ~ram();

        void write(uint16_t addr, uint8_t data);
        void write_range(uint16_t start, uint16_t end, uint8_t data);
        uint8_t read(uint16_t addr);
        void read_range(uint16_t start, uint16_t end, uint8_t buf[]);
    };
}