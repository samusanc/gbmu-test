# GBMU — GameBoy / GameBoy Color Emulator

A GameBoy™ and GameBoy™ Color emulator written in C++17 with SDL2.

## Requirements

- C++17 compiler (g++ / clang++)
- SDL2

```sh
sudo apt install libsdl2-dev
```

## Build

```sh
make
```

## Run

```sh
./gbmu path/to/rom.gb
```

## Controls

| Key | GameBoy Button |
|-----|----------------|
| Arrow keys | D-Pad |
| Z | A |
| X | B |
| Enter | Start |
| Right Shift | Select |

## Project Structure

```
src/
├── bus/          Memory bus — routes reads/writes to the correct component
├── cartridge/    ROM loading and MBC (Memory Bank Controllers)
├── cpu/          SM83 CPU emulation (registers, flags, instructions)
├── display/      SDL2 window, renderer, and texture
├── joypad/       Input handling (SDL2 key events → GB P1 register)
├── ppu/          Pixel Processing Unit — scanline rendering (160×144)
├── timer/        Hardware timer (DIV/TIMA/TMA/TAC)
└── GameBoy.{hpp,cpp}  Top-level orchestrator
main.cpp
```

## Progress

### Mandatory

- [ ] CPU — SM83 instruction set
- [ ] PPU / LCD — scanline renderer
- [ ] Timer — DIV, TIMA, TMA, TAC
- [ ] Joypad — D-Pad and buttons
- [ ] MBC1 / MBC2 / MBC3 / MBC5 bank switching
- [ ] GameBoy Color (CGB) support

### Bonus

- [ ] Sound
- [ ] BIOS / boot ROM
- [ ] Force DMG/CGB mode
- [ ] Save states
- [ ] Drag & drop ROMs

## References

- [Pan Docs](https://gbdev.io/pandocs/) — authoritative GB technical reference
- [gbdev.io](https://gbdev.io/) — community resources and homebrew ROMs
- [Game Boy CPU Manual](http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf)
