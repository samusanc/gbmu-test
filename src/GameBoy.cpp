#include "GameBoy.hpp"
#include <iostream>

// GB runs at 4.194304 MHz; one frame is 70224 cycles at ~59.7 fps
static const int CYCLES_PER_FRAME = 70224;

GameBoy::GameBoy()
    : cpu(bus), ppu(bus), timer(bus), joypad(bus),
      running(false), paused(false) {
    bus.connectCPU(&cpu);
    bus.connectPPU(&ppu);
    bus.connectCartridge(&cartridge);
    bus.connectTimer(&timer);
    bus.connectJoypad(&joypad);
}

GameBoy::~GameBoy() {}

bool GameBoy::load(const std::string& romPath) {
    if (!cartridge.load(romPath)) {
        std::cerr << "Failed to load ROM: " << romPath << std::endl;
        return false;
    }
    reset();
    return true;
}

void GameBoy::reset() {
    bus.reset();
    cpu.reset();
    ppu.reset();
    timer.reset();
    joypad.reset();
}

void GameBoy::run() {
    std::string title = "GBMU - " + cartridge.title();
    if (!display.init(title)) {
        std::cerr << "Failed to initialize display" << std::endl;
        return;
    }
    running = true;
    while (running) {
        handleEvents();
        if (!paused)
            stepFrame();
    }
    display.destroy();
}

void GameBoy::stop()   { running = false; }
void GameBoy::pause()  { paused = true;   }
void GameBoy::resume() { paused = false;  }

void GameBoy::handleEvents() {
    SDL_Event event;
    while (display.pollEvents(event)) {
        if (event.type == SDL_QUIT)
            stop();
        joypad.handleEvent(event);
    }
}

void GameBoy::stepFrame() {
    int cycles = 0;
    while (cycles < CYCLES_PER_FRAME) {
        int c = cpu.step();
        ppu.step(c);
        timer.step(c);
        cycles += c;
    }
    if (ppu.isFrameReady()) {
        display.update(ppu.getFramebuffer());
        ppu.clearFrameReady();
    }
}
