#pragma once
#include <cstdint>

class Bus;

class Timer {
public:
    Timer(Bus& bus);
    ~Timer();

    void        reset();
    void        step(int cycles);

    uint8_t     read8(uint16_t addr) const;
    void        write8(uint16_t addr, uint8_t val);

private:
    Bus&        bus;

    uint16_t    internalDiv;
    uint8_t     TIMA;
    uint8_t     TMA;
    uint8_t     TAC;

    int         timerCycles;

    int         getTimerFreq() const;
};
