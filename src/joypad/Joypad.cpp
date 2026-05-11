#include "Joypad.hpp"
#include "../bus/Bus.hpp"

Joypad::Joypad(Bus& bus) : bus(bus), buttons(0xFF), select(0) {}

Joypad::~Joypad() {}

void Joypad::reset() {
    buttons = 0xFF;
    select = 0;
}

void Joypad::handleEvent(const SDL_Event& event) {
    if (event.type != SDL_KEYDOWN && event.type != SDL_KEYUP)
        return;
    bool pressed = (event.type == SDL_KEYDOWN);
    // TODO: make key mapping configurable
    switch (event.key.keysym.sym) {
        case SDLK_RIGHT:  pressed ? (buttons &= ~(1 << RIGHT))  : (buttons |= (1 << RIGHT));  break;
        case SDLK_LEFT:   pressed ? (buttons &= ~(1 << LEFT))   : (buttons |= (1 << LEFT));   break;
        case SDLK_UP:     pressed ? (buttons &= ~(1 << UP))     : (buttons |= (1 << UP));     break;
        case SDLK_DOWN:   pressed ? (buttons &= ~(1 << DOWN))   : (buttons |= (1 << DOWN));   break;
        case SDLK_z:      pressed ? (buttons &= ~(1 << A))      : (buttons |= (1 << A));      break;
        case SDLK_x:      pressed ? (buttons &= ~(1 << B))      : (buttons |= (1 << B));      break;
        case SDLK_RETURN: pressed ? (buttons &= ~(1 << START))  : (buttons |= (1 << START));  break;
        case SDLK_RSHIFT: pressed ? (buttons &= ~(1 << SELECT)) : (buttons |= (1 << SELECT)); break;
        default: break;
    }
    if (pressed)
        bus.IF |= 0x10;  // request joypad interrupt
}

uint8_t Joypad::read8() const {
    uint8_t val = select | 0xCF;
    if (!(select & 0x10))       // D-pad
        val |= (buttons & 0x0F);
    else if (!(select & 0x20))  // buttons
        val |= ((buttons >> 4) & 0x0F);
    return val;
}

void Joypad::write8(uint8_t val) {
    select = val & 0x30;
}
