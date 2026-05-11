#include "PPU.hpp"
#include "../bus/Bus.hpp"

PPU::PPU(Bus& bus) : bus(bus) {
    reset();
}

PPU::~PPU() {}

void PPU::reset() {
    memset(vram, 0, sizeof(vram));
    memset(oam, 0, sizeof(oam));
    memset(framebuffer, 0xFF, sizeof(framebuffer));
    LCDC = 0x91; STAT = 0x00;
    SCY = 0;     SCX = 0;
    LY = 0;      LYC = 0;
    WY = 0;      WX = 0;
    BGP = 0xFC;  OBP0 = 0xFF; OBP1 = 0xFF;
    cycles = 0;  mode = OAM_SEARCH; frameReady = false;
}

void PPU::step(int c) {
    if (!(LCDC & 0x80))
        return;
    // TODO: implement PPU timing (OAM=80, Transfer=172, HBlank=204, VBlank=456*10)
    (void)c;
}

uint8_t PPU::read8(uint16_t addr) const {
    if (addr >= 0x8000 && addr <= 0x9FFF)
        return vram[addr - 0x8000];
    if (addr >= 0xFE00 && addr <= 0xFE9F)
        return oam[addr - 0xFE00];
    // TODO: IO register reads (0xFF40–0xFF4B)
    return 0xFF;
}

void PPU::write8(uint16_t addr, uint8_t val) {
    if (addr >= 0x8000 && addr <= 0x9FFF)
        { vram[addr - 0x8000] = val; return; }
    if (addr >= 0xFE00 && addr <= 0xFE9F)
        { oam[addr - 0xFE00] = val; return; }
    // TODO: IO register writes
    (void)val;
}

void PPU::renderScanline() {
    // TODO: render background, window, sprites for current LY
}
