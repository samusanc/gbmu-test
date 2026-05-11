#pragma once
#include <cstdint>
#include <cstring>

#define GB_SCREEN_WIDTH  160
#define GB_SCREEN_HEIGHT 144

class Bus;

class PPU {
public:
    PPU(Bus& bus);
    ~PPU();

    void            reset();
    void            step(int cycles);

    uint8_t         read8(uint16_t addr) const;
    void            write8(uint16_t addr, uint8_t val);

    const uint32_t* getFramebuffer() const { return framebuffer; }
    bool            isFrameReady()   const { return frameReady; }
    void            clearFrameReady()      { frameReady = false; }

    enum Mode { HBLANK = 0, VBLANK = 1, OAM_SEARCH = 2, PIXEL_TRANSFER = 3 };

private:
    Bus&        bus;

    uint8_t     vram[0x2000];
    uint8_t     oam[0xA0];

    uint8_t     LCDC, STAT, SCY, SCX, LY, LYC;
    uint8_t     WY, WX, BGP, OBP0, OBP1;

    int         cycles;
    Mode        mode;
    bool        frameReady;

    uint32_t    framebuffer[GB_SCREEN_WIDTH * GB_SCREEN_HEIGHT];

    void        renderScanline();
};
