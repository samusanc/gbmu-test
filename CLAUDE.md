# CLAUDE.md

## Project

GBMU is a GameBoy™ / GameBoy™ Color emulator written in C++17 with SDL2 for rendering and input.

## Build

```sh
make          # build → ./gbmu
make re       # clean rebuild
make fclean   # remove binary and build/
```

Requires: `libsdl2-dev` (`sudo apt install libsdl2-dev`)

## Run

```sh
./gbmu <rom.gb>
```

## Architecture

All components are connected via the `Bus`. The `GameBoy` class owns every component and wires them up.

| Component | Files | Responsibility |
|-----------|-------|----------------|
| `Bus` | `src/bus/` | Routes `read8`/`write8` across the full memory map; holds IF/IE |
| `CPU` | `src/cpu/` | SM83 processor — registers, flags, fetch/decode/execute |
| `PPU` | `src/ppu/` | VRAM, OAM, scanline renderer → 160×144 ARGB framebuffer |
| `Cartridge` | `src/cartridge/` | ROM loading, MBC1/2/3/5 bank switching, battery RAM |
| `Timer` | `src/timer/` | DIV/TIMA/TMA/TAC; fires interrupt bit 2 of IF on overflow |
| `Joypad` | `src/joypad/` | P1 register; translates SDL2 key events to button state |
| `Display` | `src/display/` | SDL2 window + renderer; scales 160×144 × DISPLAY_SCALE (3×) |
| `GameBoy` | `src/GameBoy` | Owns all components, runs `stepFrame()` loop at ~59.7 fps |

## Key Constants

- CPU clock: 4.194304 MHz (DMG)
- Cycles per frame: **70224** (`CYCLES_PER_FRAME` in `GameBoy.cpp`)
- Screen: 160 × 144 pixels (`GB_SCREEN_WIDTH` / `GB_SCREEN_HEIGHT` in `PPU.hpp`)
- Display scale: 3× (`DISPLAY_SCALE` in `Display.hpp`)

## Memory Map

| Range | Size | Owner |
|-------|------|-------|
| `0x0000–0x7FFF` | 32 KB | Cartridge (ROM) |
| `0x8000–0x9FFF` | 8 KB | PPU (VRAM) |
| `0xA000–0xBFFF` | 8 KB | Cartridge (external RAM) |
| `0xC000–0xDFFF` | 8 KB | Bus (WRAM) |
| `0xE000–0xFDFF` | — | Echo RAM (WRAM mirror) |
| `0xFE00–0xFE9F` | 160 B | PPU (OAM) |
| `0xFF00–0xFF7F` | 128 B | I/O registers (Timer, Joypad, PPU, etc.) |
| `0xFF80–0xFFFE` | 127 B | Bus (HRAM) |
| `0xFFFF` | 1 B | Bus (IE register) |

## Interrupts (IF at 0xFF0F / IE at 0xFFFF)

| Bit | Source |
|-----|--------|
| 0 | VBlank |
| 1 | LCD STAT |
| 2 | Timer |
| 3 | Serial |
| 4 | Joypad |

## Coding Conventions

- C++17, `-Wall -Wextra -Werror`
- No raw `new`/`delete` except where unavoidable; prefer stack allocation
- Each component owns its own register state; `Bus` only routes, never holds game logic
- Stubs marked with `// TODO:` — implement in order: CPU → PPU → Timer → Joypad → MBC
