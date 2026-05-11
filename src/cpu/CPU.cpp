#include "CPU.hpp"
#include "../bus/Bus.hpp"

CPU::CPU(Bus& bus) : bus(bus) {
    reset();
}

CPU::~CPU() {}

void CPU::reset() {
    regs.AF = 0x01B0;
    regs.BC = 0x0013;
    regs.DE = 0x00D8;
    regs.HL = 0x014D;
    regs.SP = 0xFFFE;
    regs.PC = 0x0100;
}

int CPU::step() {
    uint8_t opcode = fetch8();
    return execute(opcode);
}

bool CPU::getFlag(char flag) const {
    uint8_t f = regs.AF & 0xFF;
    switch (flag) {
        case 'Z': return (f >> 7) & 1;
        case 'N': return (f >> 6) & 1;
        case 'H': return (f >> 5) & 1;
        case 'C': return (f >> 4) & 1;
    }
    return false;
}

void CPU::setFlag(char flag, bool val) {
    uint8_t& f = reinterpret_cast<uint8_t*>(&regs.AF)[0];
    switch (flag) {
        case 'Z': val ? (f |= 0x80) : (f &= ~0x80); break;
        case 'N': val ? (f |= 0x40) : (f &= ~0x40); break;
        case 'H': val ? (f |= 0x20) : (f &= ~0x20); break;
        case 'C': val ? (f |= 0x10) : (f &= ~0x10); break;
    }
}

uint8_t CPU::fetch8() {
    return bus.read8(regs.PC++);
}

uint16_t CPU::fetch16() {
    uint16_t lo = fetch8();
    uint16_t hi = fetch8();
    return (hi << 8) | lo;
}

int CPU::execute(uint8_t opcode) {
    if (opcode == 0xCB)
        return executeExtended(fetch8());
    // TODO: implement SM83 instruction set
    (void)opcode;
    return 4;
}

int CPU::executeExtended(uint8_t opcode) {
    // TODO: implement CB-prefixed instructions
    (void)opcode;
    return 8;
}
