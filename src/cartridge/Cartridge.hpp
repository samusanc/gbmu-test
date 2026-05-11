#pragma once
#include <cstdint>
#include <string>
#include <vector>

class Cartridge {
public:
    Cartridge();
    ~Cartridge();

    bool        load(const std::string& path);
    void        unload();

    uint8_t     read8(uint16_t addr) const;
    void        write8(uint16_t addr, uint8_t val);

    std::string title()      const;
    uint8_t     mbcType()    const;
    bool        hasBattery() const;

    enum MBCType { ROM_ONLY = 0, MBC1, MBC2, MBC3, MBC5 };

private:
    std::vector<uint8_t>    rom;
    std::vector<uint8_t>    ram;
    MBCType                 mbc;
    bool                    battery;

    uint8_t     romBank;
    uint8_t     ramBank;
    bool        ramEnabled;
    bool        bankMode;

    MBCType     detectMBC(uint8_t headerByte);
};
