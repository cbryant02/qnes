#pragma once

#include <cstdint>
#include <array>

namespace qnes {
    class ram {
    private:
        std::array<uint8_t, 0xFFFF> memory;

    public:
        /**
         * @brief Write a value to a single address.
         * 
         * @param addr Address to write to
         * @param data Value to write
         */
        void write(uint16_t addr, uint8_t data);

        /**
         * @brief Read a single value.
         * 
         * @param addr Address to read from
         * @return uint8_t The value at the address
         */
        uint8_t read(uint16_t addr);

        /**
         * @brief Write a value to all cells within an address range.
         * 
         * @param start Start of address range to write to
         * @param end End of address range to write to
         * @param data Value to write
         */
        void write_range(uint16_t start, uint16_t end, uint8_t data);

        /**
         * @brief Read all values within an address range.
         * 
         * @param start Start of address range to read from
         * @param end End of address range to read from
         * @param buf Buffer to write data into
         */
        void read_range(uint16_t start, uint16_t end, uint8_t buf[]);
    };
}