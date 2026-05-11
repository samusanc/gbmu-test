#include "Cartridge.hpp"
#include <fstream>
#include <iostream>

Cartridge::Cartridge()
    : mbc(ROM_ONLY), battery(false),
      romBank(1), ramBank(0), ramEnabled(false), bankMode(false) {}

Cartridge::~Cartridge() {}

bool Cartridge::load(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open ROM: " << path << std::endl;
        return false;
    }
    rom = std::vector<uint8_t>(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    );
    if (rom.size() < 0x150) {
        std::cerr << "ROM too small to be valid" << std::endl;
        return false;
    }
    mbc     = detectMBC(rom[0x147]);
    battery = (rom[0x147] == 0x03 || rom[0x147] == 0x06 ||
               rom[0x147] == 0x0F || rom[0x147] == 0x10 ||
               rom[0x147] == 0x13 || rom[0x147] == 0x1B ||
               rom[0x147] == 0x1E);
    return true;
}

void Cartridge::unload() {
    rom.clear();
    ram.clear();
}

uint8_t Cartridge::read8(uint16_t addr) const {
    if (addr < (uint16_t)rom.size())
        return rom[addr];
    return 0xFF;
}

void Cartridge::write8(uint16_t addr, uint8_t val) {
    // TODO: implement MBC register writes
    (void)addr;
    (void)val;
}

std::string Cartridge::title() const {
    if (rom.size() < 0x144)
        return "";
    std::string t(rom.begin() + 0x134, rom.begin() + 0x144);
    t.erase(t.find_last_not_of('\0') + 1);
    return t;
}

uint8_t Cartridge::mbcType()    const { return (uint8_t)mbc; }
bool    Cartridge::hasBattery() const { return battery; }

Cartridge::MBCType Cartridge::detectMBC(uint8_t code) {
    switch (code) {
        case 0x00:                                           return ROM_ONLY;
        case 0x01: case 0x02: case 0x03:                    return MBC1;
        case 0x05: case 0x06:                               return MBC2;
        case 0x0F: case 0x10: case 0x11: case 0x12: case 0x13: return MBC3;
        case 0x19: case 0x1A: case 0x1B:
        case 0x1C: case 0x1D: case 0x1E:                   return MBC5;
        default:                                            return ROM_ONLY;
    }
}
