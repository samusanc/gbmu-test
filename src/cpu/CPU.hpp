#pragma once
#include <cstdint>

class Bus;

class CPU {
public:
    CPU(Bus& bus);
    ~CPU();

    void        reset();
    int         step();     // execute one instruction, return cycles taken

    struct Registers {
        uint16_t AF, BC, DE, HL;
        uint16_t SP, PC;
    } regs;

    bool        getFlag(char flag) const;
    void        setFlag(char flag, bool val);

private:
    Bus&        bus;

    uint8_t     fetch8();
    uint16_t    fetch16();
    int         execute(uint8_t opcode);
    int         executeExtended(uint8_t opcode);
};
