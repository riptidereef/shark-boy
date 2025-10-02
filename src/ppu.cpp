#include "ppu.h"

u8 PPU::read8(u16 address) {
    if (address > 0x2000) return 0xFF;
    return vram[address];
}

void PPU::write8(u16 address, u8 data) {
    if (address >= 0x2000) return;
    vram[address] = data;
}

u16 PPU::read16(u16 address) {
    return 0xFFFF;
}

void PPU::write16(u16 address, u16 data) {

}