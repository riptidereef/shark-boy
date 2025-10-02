#include "mmu.h"

MMU::MMU(PPU* ppu) {
    this->ppu = ppu;
}

void MMU::setCartridge(Cartridge* cartridge) {
    this->cartridge = cartridge;
}

void MMU::write8(u16 address, u8 data) {
    if (address <= 0x7FFF) {
        // Cartridge ROM (writes handled by MBC)
        cartridge->write8(address, data);
    }
    else if (address <= 0x9FFF) {
        // VRAM
        ppu->write8(address, data);
    }
    else if (address <= 0xBFFF) {
        // Cartridge RAM
        cartridge->write8(address, data);
    }
    else if (address <= 0xDFFF) {
        // Work RAM
        wram[address - 0xC000] = data;
    }
    else if (address <= 0xFDFF) {
        // Echo RAM (mirror of C000–DDFF)
        wram[address - 0xE000] = data;
    }
    else if (address <= 0xFE9F) {
        // OAM
        oam[address - 0xFE00] = data;
    }
    else if (address <= 0xFEFF) {
        // Not usable
        // Do nothing
    }
    else if (address <= 0xFF7F) {
        // I/O Registers
        if (address == 0xFF0F) {
            if_reg = data;
        }

        io[address - 0xFF00] = data;
    }
    else if (address <= 0xFFFE) {
        // High RAM (HRAM)
        hram[address - 0xFF80] = data;
    }
    else if (address == 0xFFFF) {
        // Interrupt Enable (IE)
        ie = data;
    }
}

u8 MMU::read8(u16 address) {
    if (address <= 0x7FFF) {
        // Cartridge ROM
        return cartridge->read8(address);
    }
    else if (address <= 0x9FFF) {
        // VRAM
        return ppu->read8(address);
    }
    else if (address <= 0xBFFF) {
        // Cartridge RAM
        return cartridge->read8(address);
    }
    else if (address <= 0xDFFF) {
        // WRAM
        return wram[address - 0xC000];
    }
    else if (address <= 0xFDFF) {
        // Echo RAM
        return wram[address - 0xE000];
    }
    else if (address <= 0xFE9F) {
        // OAM
        return oam[address - 0xFE00];
    }
    else if (address <= 0xFEFF) {
        // Not usable
        return 0xFF;
    }
    else if (address <= 0xFF7F) {
        // I/O Registers

        if (address == 0xFF0F) {
            return if_reg;
        }

        return io[address - 0xFF00];
    }
    else if (address <= 0xFFFE) {
        // HRAM
        return hram[address - 0xFF80];
    }
    else if (address == 0xFFFF) {
        // Interrupt Enable (IE)
        return ie;
    }
    else {
        return 0xFF;
    }
}

void MMU::write16(u16 address, u16 data) {
    u8 lo = static_cast<u8>(data & 0xFF);
    u8 hi = static_cast<u8>((data & 0xFF00) >> 8);
    write8(address, lo);
    write8(address + 1, hi);
}

u16 MMU::read16(u16 address) {
    u8 lo = read8(address);
    u8 hi = read8(address + 1);
    return static_cast<u16>((hi << 8) | lo);
}