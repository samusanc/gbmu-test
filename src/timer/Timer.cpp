#include "Timer.hpp"
#include "../bus/Bus.hpp"

Timer::Timer(Bus& bus) : bus(bus) {
    reset();
}

Timer::~Timer() {}

void Timer::reset() {
    internalDiv = 0;
    TIMA = 0; TMA = 0; TAC = 0;
    timerCycles = 0;
}

void Timer::step(int cycles) {
    internalDiv += cycles;
    if (!(TAC & 0x04))
        return;
    timerCycles += cycles;
    int freq = getTimerFreq();
    while (timerCycles >= freq) {
        timerCycles -= freq;
        if (++TIMA == 0) {
            TIMA = TMA;
            bus.IF |= 0x04;  // request timer interrupt
        }
    }
}

uint8_t Timer::read8(uint16_t addr) const {
    switch (addr) {
        case 0xFF04: return (uint8_t)(internalDiv >> 8);
        case 0xFF05: return TIMA;
        case 0xFF06: return TMA;
        case 0xFF07: return TAC | 0xF8;
        default:     return 0xFF;
    }
}

void Timer::write8(uint16_t addr, uint8_t val) {
    switch (addr) {
        case 0xFF04: internalDiv = 0;       break;
        case 0xFF05: TIMA = val;            break;
        case 0xFF06: TMA  = val;            break;
        case 0xFF07: TAC  = val & 0x07;     break;
    }
}

int Timer::getTimerFreq() const {
    switch (TAC & 0x03) {
        case 0: return 1024;
        case 1: return 16;
        case 2: return 64;
        case 3: return 256;
        default: return 1024;
    }
}
