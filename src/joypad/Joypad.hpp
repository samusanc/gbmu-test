#pragma once
#include <cstdint>
#include <SDL2/SDL.h>

class Bus;

class Joypad {
public:
    Joypad(Bus& bus);
    ~Joypad();

    void        reset();
    void        handleEvent(const SDL_Event& event);

    uint8_t     read8() const;
    void        write8(uint8_t val);

    enum Button { RIGHT = 0, LEFT, UP, DOWN, A, B, SELECT, START };

private:
    Bus&        bus;

    uint8_t     buttons;
    uint8_t     select;
};
