#include "mmu.h"

MMU::MMU(PPU* ppu) {
    this->ppu = ppu;
}

void MMU::setCartridge(Cartridge* cartridge) {
    this->cartridge = cartridge;
}

void MMU::write8(u16 address, u8 data) {

}

u8 MMU::read8(u16 address) {
    return cartridge->read8(address);
}

void MMU::write16(u16 address, u16 data) {

}

u16 MMU::read16(u16 address) {
    return cartridge->read16(address);
}