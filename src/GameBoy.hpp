#pragma once
#include <string>
#include "bus/Bus.hpp"
#include "cpu/CPU.hpp"
#include "ppu/PPU.hpp"
#include "cartridge/Cartridge.hpp"
#include "timer/Timer.hpp"
#include "joypad/Joypad.hpp"
#include "display/Display.hpp"

class GameBoy {
public:
    GameBoy();
    ~GameBoy();

    bool    load(const std::string& romPath);
    void    run();
    void    stop();
    void    pause();
    void    resume();
    void    reset();

    bool    isRunning() const { return running; }
    bool    isPaused()  const { return paused; }

    CPU&        getCPU()     { return cpu; }
    PPU&        getPPU()     { return ppu; }
    Bus&        getBus()     { return bus; }
    Display&    getDisplay() { return display; }

private:
    Bus         bus;
    CPU         cpu;
    PPU         ppu;
    Cartridge   cartridge;
    Timer       timer;
    Joypad      joypad;
    Display     display;

    bool        running;
    bool        paused;

    void        handleEvents();
    void        stepFrame();
};
