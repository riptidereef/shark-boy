#pragma once
#include <array>
#include "common.h"
#include "cartridge.h"
#include "ppu.h"
using namespace std;

class MMU {
public:
    MMU(PPU* ppu);

    void write8(u16 address, u8 data);
    u8 read8(u16 address);
    void write16(u16 address, u16 data);
    u16 read16(u16 address);

    void setCartridge(Cartridge* cartridge);

private:
    Cartridge* cartridge;
    PPU* ppu;

    array<u8, 0x2000> wram {};
    array<u8, 0xA0> oam {};
    array<u8, 0x80> io {};
    array<u8, 0x7F> hram {};
    u8 interruptEnable = 0;
};