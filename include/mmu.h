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

    u8& joyp;   // $FF00 - Joypad
    u8& sb;     // $FF01 - Serial data
    u8& sc;     // $FF02 - Serial control
    u8& div;    // $FF04 - Divider
    u8& tima;   // $FF05 - Timer counter
    u8& tma;    // $FF06 - Timer modulo
    u8& tac;    // $FF07 - Timer control
    u8& if_reg; // $FF0F - Interrupt flag

    u8& lcdc;   // $FF40 - LCD Control
    u8& stat;   // $FF41 - LCD Status
    u8& scy;    // $FF42 - Scroll Y
    u8& scx;    // $FF43 - Scroll X
    u8& ly;     // $FF44 - LCD Y-coordinate
    u8& lyc;    // $FF45 - LY Compare
    u8& dma;    // $FF46 - DMA source address
    u8& bgp;    // $FF47 - BG Palette
    u8& obp0;   // $FF48 - OBJ Palette 0
    u8& obp1;   // $FF49 - OBJ Palette 1
    u8& wy;     // $FF4A - Window Y
    u8& wx;     // $FF4B - Window X
    u8& ie;     // $FFFF - Interrupt enable

private:
    Cartridge* cartridge = nullptr;
    PPU* ppu = nullptr;

    array<u8, 0x2000> wram {};
    array<u8, 0xA0> oam {};
    array<u8, 0x80> io {};
    array<u8, 0x7F> hram {};
    u8 ie_backing = 0;
};