#include "Bus.hpp"
#include "../cpu/CPU.hpp"
#include "../ppu/PPU.hpp"
#include "../cartridge/Cartridge.hpp"
#include "../timer/Timer.hpp"
#include "../joypad/Joypad.hpp"

Bus::Bus() : IF(0), IE(0),
             cpu(nullptr), ppu(nullptr),
             cartridge(nullptr), timer(nullptr), joypad(nullptr) {
    reset();
}

Bus::~Bus() {}

void Bus::reset() {
    memset(wram, 0, sizeof(wram));
    memset(hram, 0, sizeof(hram));
    IF = 0xE1;
    IE = 0x00;
}

void Bus::connectCPU(CPU* c)             { cpu = c; }
void Bus::connectPPU(PPU* p)             { ppu = p; }
void Bus::connectCartridge(Cartridge* c) { cartridge = c; }
void Bus::connectTimer(Timer* t)         { timer = t; }
void Bus::connectJoypad(Joypad* j)       { joypad = j; }

uint8_t Bus::read8(uint16_t addr) const {
    // ROM bank 0 / bank N
    if (addr <= 0x7FFF) {
        if (cartridge) return cartridge->read8(addr);
        return 0xFF;
    }
    // VRAM / OAM handled by PPU
    if ((addr >= 0x8000 && addr <= 0x9FFF) ||
        (addr >= 0xFE00 && addr <= 0xFE9F)) {
        if (ppu) return ppu->read8(addr);
        return 0xFF;
    }
    // External RAM
    if (addr >= 0xA000 && addr <= 0xBFFF) {
        if (cartridge) return cartridge->read8(addr);
        return 0xFF;
    }
    // Work RAM
    if (addr >= 0xC000 && addr <= 0xDFFF)
        return wram[addr - 0xC000];
    // Echo RAM
    if (addr >= 0xE000 && addr <= 0xFDFF)
        return wram[addr - 0xE000];
    // IO registers
    if (addr >= 0xFF00 && addr <= 0xFF7F) {
        if (addr == 0xFF0F) return IF;
        // TODO: route to timer, joypad, ppu
        return 0xFF;
    }
    // HRAM
    if (addr >= 0xFF80 && addr <= 0xFFFE)
        return hram[addr - 0xFF80];
    if (addr == 0xFFFF)
        return IE;
    return 0xFF;
}

void Bus::write8(uint16_t addr, uint8_t val) {
    if (addr <= 0x7FFF) {
        if (cartridge) cartridge->write8(addr, val);
        return;
    }
    if ((addr >= 0x8000 && addr <= 0x9FFF) ||
        (addr >= 0xFE00 && addr <= 0xFE9F)) {
        if (ppu) ppu->write8(addr, val);
        return;
    }
    if (addr >= 0xA000 && addr <= 0xBFFF) {
        if (cartridge) cartridge->write8(addr, val);
        return;
    }
    if (addr >= 0xC000 && addr <= 0xDFFF)
        { wram[addr - 0xC000] = val; return; }
    if (addr >= 0xE000 && addr <= 0xFDFF)
        { wram[addr - 0xE000] = val; return; }
    if (addr >= 0xFF00 && addr <= 0xFF7F) {
        if (addr == 0xFF0F) { IF = val; return; }
        // TODO: route to timer, joypad, ppu
        return;
    }
    if (addr >= 0xFF80 && addr <= 0xFFFE)
        { hram[addr - 0xFF80] = val; return; }
    if (addr == 0xFFFF)
        { IE = val; return; }
}

uint16_t Bus::read16(uint16_t addr) const {
    return (uint16_t)(read8(addr) | (read8(addr + 1) << 8));
}

void Bus::write16(uint16_t addr, uint16_t val) {
    write8(addr,     (uint8_t)(val & 0xFF));
    write8(addr + 1, (uint8_t)(val >> 8));
}
