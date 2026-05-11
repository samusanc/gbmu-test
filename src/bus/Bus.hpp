#pragma once
#include <cstdint>
#include <cstring>

class CPU;
class PPU;
class Cartridge;
class Timer;
class Joypad;

class Bus {
public:
    Bus();
    ~Bus();

    void        connectCPU(CPU* cpu);
    void        connectPPU(PPU* ppu);
    void        connectCartridge(Cartridge* cart);
    void        connectTimer(Timer* timer);
    void        connectJoypad(Joypad* joypad);

    uint8_t     read8(uint16_t addr) const;
    void        write8(uint16_t addr, uint8_t val);
    uint16_t    read16(uint16_t addr) const;
    void        write16(uint16_t addr, uint16_t val);

    void        reset();

    uint8_t     IF;
    uint8_t     IE;

private:
    uint8_t     wram[0x2000];
    uint8_t     hram[0x7F];

    CPU*        cpu;
    PPU*        ppu;
    Cartridge*  cartridge;
    Timer*      timer;
    Joypad*     joypad;
};
