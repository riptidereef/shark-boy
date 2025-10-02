#include "cartridge.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <unordered_map>

Cartridge::Cartridge(string romPath) {
    loadRom(romPath);
}

bool Cartridge::loadRom(string romPath) {
    ifstream file(romPath, ios::binary | ios::ate);

    if (!file) {
        file.open("../" + romPath, ios::binary | ios::ate);
        if (!file) {
            cerr << "Failed to open ROM: " << romPath << endl;
            return false;
        }
    }

    this->romPath = romPath;

    romSize = file.tellg();
    file.seekg(0, ios::beg);

    romData = make_unique<u8[]>(romSize);

    file.read(reinterpret_cast<char*>(romData.get()), romSize);

    const u16 headerAddr = 0x0100;

    memcpy(romHeader.entry, romData.get() + headerAddr, 4);
    memcpy(romHeader.logo, romData.get() + headerAddr + 0x04, 48);
    memcpy(romHeader.title, romData.get() + headerAddr + 0x34, 16);
    memcpy(romHeader.manufacturer, romData.get() + headerAddr + 0x3F, 4);
    
    romHeader.cgbFlag = *(romData.get() + headerAddr + 0x43);

    memcpy(romHeader.newLicenseeCode, romData.get() + headerAddr + 0x44, 2);

    romHeader.sgbFlag = *(romData.get() + headerAddr + 0x46);
    romHeader.cartridgeType = *(romData.get() + headerAddr + 0x47);
    romHeader.romSize = *(romData.get() + headerAddr + 0x48);
    romHeader.ramSize = *(romData.get() + headerAddr + 0x49);
    romHeader.destinationCode = *(romData.get() + headerAddr + 0x4A);
    romHeader.oldLicenseeCode = *(romData.get() + headerAddr + 0x4B);
    romHeader.maskRomVersion = *(romData.get() + headerAddr + 0x4C);
    romHeader.headerChecksum = *(romData.get() + headerAddr + 0x4D);

    romHeader.globalChecksum = *(u16*)(romData.get() + headerAddr + 0x4E);

    return true;
}

u8 Cartridge::read8(u16 address) {
    if (address < romSize) {
        u8 val = romData[address];
        return romData[address];
    }
    else return 0xFF;
}

u16 Cartridge::read16(u16 address) {
    if (address < romSize - 1) {
        return ((romData[address + 1] << 8) | romData[address]);
    }
    else return 0xFFFF;
}

void Cartridge::write8(u16 address, u8 data) {

}

void Cartridge::write16(u16 address, u16 data) {
    
}

inline std::string getCartridgeType(u8 cartType) {
    switch (cartType) {
        case 0x00: return "ROM ONLY";
        case 0x01: return "MBC1";
        case 0x02: return "MBC1+RAM";
        case 0x03: return "MBC1+RAM+BATTERY";
        case 0x04: return "0x04 ???";
        case 0x05: return "MBC2";
        case 0x06: return "MBC2+BATTERY";
        case 0x07: return "0x07 ???";
        case 0x08: return "ROM+RAM";
        case 0x09: return "ROM+RAM+BATTERY";
        case 0x0A: return "0x0A ???";
        case 0x0B: return "MMM01";
        case 0x0C: return "MMM01+RAM";
        case 0x0D: return "MMM01+RAM+BATTERY";
        case 0x0E: return "0x0E ???";
        case 0x0F: return "MBC3+TIMER+BATTERY";
        case 0x10: return "MBC3+TIMER+RAM+BATTERY";
        case 0x11: return "MBC3";
        case 0x12: return "MBC3+RAM";
        case 0x13: return "MBC3+RAM+BATTERY";
        case 0x14: return "0x14 ???";
        case 0x15: return "0x15 ???";
        case 0x16: return "0x16 ???";
        case 0x17: return "0x17 ???";
        case 0x18: return "0x18 ???";
        case 0x19: return "MBC5";
        case 0x1A: return "MBC5+RAM";
        case 0x1B: return "MBC5+RAM+BATTERY";
        case 0x1C: return "MBC5+RUMBLE";
        case 0x1D: return "MBC5+RUMBLE+RAM";
        case 0x1E: return "MBC5+RUMBLE+RAM+BATTERY";
        case 0x1F: return "0x1F ???";
        case 0x20: return "MBC6";
        case 0x21: return "0x21 ???";
        case 0x22: return "MBC7+SENSOR+RUMBLE+RAM+BATTERY";
        case 0xFC: return "POCKET CAMERA";
        case 0xFD: return "BANDAI TAMA5";
        case 0xFE: return "HuC3";
        case 0xFF: return "HuC1+RAM+BATTERY";
        default:   return "Unknown Cartridge Type";
    }
}

inline std::string getRomSizeName(u8 code) {
    switch (code) {
        case 0x00: return "32KB (no banking)";
        case 0x01: return "64KB (4 banks)";
        case 0x02: return "128KB (8 banks)";
        case 0x03: return "256KB (16 banks)";
        case 0x04: return "512KB (32 banks)";
        case 0x05: return "1MB (64 banks)";
        case 0x06: return "2MB (128 banks)";
        case 0x07: return "4MB (256 banks)";
        case 0x08: return "8MB (512 banks)";
        case 0x52: return "1.1MB (72 banks)";
        case 0x53: return "1.2MB (80 banks)";
        case 0x54: return "1.5MB (96 banks)";
        default:   return "Unknown ROM Size";
    }
}

inline std::string getRamSizeName(u8 code) {
    switch (code) {
        case 0x00: return "None";
        case 0x01: return "2KB";
        case 0x02: return "8KB (1 bank)";
        case 0x03: return "32KB (4 banks of 8KB)";
        case 0x04: return "128KB (16 banks of 8KB)";
        case 0x05: return "64KB (8 banks of 8KB)";
        default:   return "Unknown RAM Size";
    }
}

inline std::string getNewLicenseeName(const std::string &code) {
    static const std::unordered_map<std::string, std::string> licenseeMap = {
        {"00", "None"},
        {"01", "Nintendo R&D1"},
        {"08", "Capcom"},
        {"13", "EA (Electronic Arts)"},
        {"18", "Hudson Soft"},
        {"19", "B-AI"},
        {"20", "KSS"},
        {"22", "Planning Office WADA"},
        {"24", "PCM Complete"},
        {"25", "San-X"},
        {"28", "Kemco Japan"},
        {"29", "SETA Corporation"},
        {"30", "Viacom"},
        {"31", "Nintendo"},
        {"32", "Bandai"},
        {"33", "Ocean/Acclaim"},
        {"34", "Konami"},
        {"35", "HectorSoft"},
        {"37", "Taito"},
        {"38", "Hudson Soft"},
        {"39", "Banpresto"},
        {"41", "Ubi Soft"},
        {"42", "Atlus"},
        {"44", "Malibu Interactive"},
        {"46", "Angel"},
        {"47", "Bullet-Proof Software"},
        {"49", "Irem"},
        {"50", "Absolute"},
        {"51", "Acclaim Entertainment"},
        {"52", "Activision"},
        {"53", "Sammy USA Corporation"},
        {"54", "Konami"},
        {"55", "Hi Tech Expressions"},
        {"56", "LJN"},
        {"57", "Matchbox"},
        {"58", "Mattel"},
        {"59", "Milton Bradley"},
        {"60", "Titus Interactive"},
        {"61", "Virgin Games Ltd."},
        {"64", "Lucasfilm Games"},
        {"67", "Ocean Software"},
        {"69", "EA (Electronic Arts)"},
        {"70", "Infogrames"},
        {"71", "Interplay Entertainment"},
        {"72", "Broderbund"},
        {"73", "Sculptured Software"},
        {"75", "The Sales Curve Limited"},
        {"78", "THQ"},
        {"79", "Accolade"},
        {"80", "Misawa Entertainment"},
        {"83", "lozc"},
        {"86", "Tokuma Shoten Intermedia"},
        {"87", "Tsukuda Original"},
        {"91", "Chunsoft"},
        {"92", "Video System"},
        {"93", "Ocean/Acclaim"},
        {"95", "Varie"},
        {"96", "Yonezawa/s’pal"},
        {"97", "Kaneko"},
        {"99", "Pack-In-Video"},
        {"A4", "Konami (Yu-Gi-Oh!)"}
    };

    auto it = licenseeMap.find(code);
    if (it != licenseeMap.end())
        return it->second;
    return "Unknown Licensee";
}

inline std::string getPublisherName(u8 oldCode, std::string newCode) {
    switch (oldCode) {
        case 0x00: return "None";
        case 0x01: return "Nintendo";
        case 0x08: return "Capcom";
        case 0x09: return "HOT-B";
        case 0x0A: return "Jaleco";
        case 0x0B: return "Coconuts Japan";
        case 0x0C: return "Elite Systems";
        case 0x13: return "EA (Electronic Arts)";
        case 0x18: return "Hudson Soft";
        case 0x19: return "ITC Entertainment";
        case 0x1A: return "Yanoman";
        case 0x1D: return "Japan Clary";
        case 0x1F: return "Virgin Games Ltd.";
        case 0x24: return "PCM Complete";
        case 0x25: return "San-X";
        case 0x28: return "Kemco";
        case 0x29: return "SETA Corporation";
        case 0x30: return "Infogrames";
        case 0x31: return "Nintendo";
        case 0x32: return "Bandai";
        case 0x33: return getNewLicenseeName(newCode);
        case 0x34: return "Konami";
        case 0x35: return "HectorSoft";
        case 0x38: return "Capcom";
        case 0x39: return "Banpresto";
        case 0x3C: return "Entertainment Interactive";
        case 0x3E: return "Gremlin";
        case 0x41: return "Ubi Soft";
        case 0x42: return "Atlus";
        case 0x44: return "Malibu Interactive";
        case 0x46: return "Angel";
        case 0x47: return "Spectrum HoloByte";
        case 0x49: return "Irem";
        case 0x4A: return "Virgin Games Ltd.";
        case 0x4D: return "Malibu Interactive";
        case 0x4F: return "U.S. Gold";
        case 0x50: return "Absolute";
        case 0x51: return "Acclaim Entertainment";
        case 0x52: return "Activision";
        case 0x53: return "Sammy USA Corporation";
        case 0x54: return "GameTek";
        case 0x55: return "Park Place";
        case 0x56: return "LJN";
        case 0x57: return "Matchbox";
        case 0x59: return "Milton Bradley";
        case 0x5A: return "Mindscape";
        case 0x5B: return "Romstar";
        case 0x5C: return "Naxat Soft";
        case 0x5D: return "Tradewest";
        case 0x60: return "Titus Interactive";
        case 0x61: return "Virgin Games Ltd.";
        case 0x67: return "Ocean Software";
        case 0x69: return "EA (Electronic Arts)";
        case 0x6E: return "Elite Systems";
        case 0x6F: return "Electro Brain";
        case 0x70: return "Infogrames";
        case 0x71: return "Interplay Entertainment";
        case 0x72: return "Broderbund";
        case 0x73: return "Sculptured Software";
        case 0x75: return "The Sales Curve Limited";
        case 0x78: return "THQ";
        case 0x79: return "Accolade";
        case 0x7A: return "Triffix Entertainment";
        case 0x7C: return "MicroProse";
        case 0x7F: return "Kemco";
        case 0x80: return "Misawa Entertainment";
        case 0x83: return "LOZC G.";
        case 0x86: return "Tokuma Shoten";
        case 0x8B: return "Bullet-Proof Software";
        case 0x8C: return "Vic Tokai";
        case 0x8E: return "Ape Inc.";
        case 0x8F: return "I’Max";
        case 0x91: return "Chunsoft Co.";
        case 0x92: return "Video System";
        case 0x93: return "Tsubaraya Productions";
        case 0x95: return "Varie";
        case 0x96: return "Yonezawa/S’Pal";
        case 0x97: return "Kemco";
        case 0x99: return "Arc";
        case 0x9A: return "Nihon Bussan";
        case 0x9B: return "Tecmo";
        case 0x9C: return "Imagineer";
        case 0x9D: return "Banpresto";
        case 0x9F: return "Nova";
        case 0xA1: return "Hori Electric";
        case 0xA2: return "Bandai";
        case 0xA4: return "Konami";
        case 0xA6: return "Kawada";
        case 0xA7: return "Takara";
        case 0xA9: return "Technos Japan";
        case 0xAA: return "Broderbund";
        case 0xAC: return "Toei Animation";
        case 0xAD: return "Toho";
        case 0xAF: return "Namco";
        case 0xB0: return "Acclaim Entertainment";
        case 0xB1: return "ASCII / Nexsoft";
        case 0xB2: return "Bandai";
        case 0xB4: return "Square Enix";
        case 0xB6: return "HAL Laboratory";
        case 0xB7: return "SNK";
        case 0xB9: return "Pony Canyon";
        case 0xBA: return "Culture Brain";
        case 0xBB: return "Sunsoft";
        case 0xBD: return "Sony Imagesoft";
        case 0xBF: return "Sammy Corporation";
        case 0xC0: return "Taito";
        case 0xC2: return "Kemco";
        case 0xC3: return "Square";
        case 0xC4: return "Tokuma Shoten";
        case 0xC5: return "Data East";
        case 0xC6: return "Tonkin House";
        case 0xC8: return "Koei";
        case 0xC9: return "UFL";
        case 0xCA: return "Ultra Games";
        case 0xCB: return "VAP, Inc.";
        case 0xCC: return "Use Corporation";
        case 0xCD: return "Meldac";
        case 0xCE: return "Pony Canyon";
        case 0xCF: return "Angel";
        case 0xD0: return "Taito";
        case 0xD1: return "SOFEL";
        case 0xD2: return "Quest";
        case 0xD3: return "Sigma Enterprises";
        case 0xD4: return "ASK Kodansha";
        case 0xD6: return "Naxat Soft";
        case 0xD7: return "Copya System";
        case 0xD9: return "Banpresto";
        case 0xDA: return "Tomy";
        case 0xDB: return "LJN";
        case 0xDD: return "Nippon Computer Systems";
        case 0xDE: return "Human Entertainment";
        case 0xDF: return "Altron";
        case 0xE0: return "Jaleco";
        case 0xE1: return "Towa Chiki";
        case 0xE2: return "Yutaka";
        case 0xE3: return "Varie";
        case 0xE5: return "Epoch";
        case 0xE7: return "Athena";
        case 0xE8: return "Asmik Ace Entertainment";
        case 0xE9: return "Natsume";
        case 0xEA: return "King Records";
        case 0xEB: return "Atlus";
        case 0xEC: return "Epic/Sony Records";
        case 0xEE: return "IGS";
        case 0xF0: return "A Wave";
        case 0xF3: return "Extreme Entertainment";
        case 0xFF: return "LJN";
        default:   return "Unknown Licensee";
    }
}

void Cartridge::printRomInfo() {
    cout << "=== ROM Information ===\n";
    cout << "ROM Path: " << this->romPath << "\n";

    cout << "Title: " << toStringFromArray(romHeader.title, sizeof(romHeader.title)) << "\n";
    cout << "Manufacturer: " << toStringFromArray(romHeader.manufacturer, sizeof(romHeader.manufacturer)) << "\n";

    string publisher = getPublisherName(romHeader.oldLicenseeCode, std::string(romHeader.newLicenseeCode, 2));
    cout << "Publisher: " << publisher << "\n";

    cout << "CGB Flag: 0x" << hex << setw(2) << setfill('0') << (int)romHeader.cgbFlag << dec << "\n";
    cout << "SGB Flag: 0x" << hex << setw(2) << setfill('0') << (int)romHeader.sgbFlag << dec << "\n";

    cout << "Cartridge Type: " << getCartridgeType(romHeader.cartridgeType) << "\n";
    cout << "ROM Size: " << getRomSizeName(romHeader.romSize) << "\n";
    cout << "RAM Size Code: " << getRamSizeName(romHeader.ramSize) << "\n";

    string dest;
    if (romHeader.destinationCode == 0x00) {
        dest = "Japan (and possibly overseas)";
    }
    else {
        dest = "Overseas Only";
    }
    cout << "Destination: " << dest << "\n";

    cout << "Mask ROM Version: 0x" << hex << setw(2) << setfill('0') << (int)romHeader.maskRomVersion << dec << "\n";
    //cout << "Header Checksum: 0x" << hex << setw(2) << setfill('0') << (int)romHeader.headerChecksum << dec << "\n";
    //cout << "Global Checksum: 0x" << hex << setw(4) << setfill('0') << romHeader.globalChecksum << dec << "\n";
    cout << "\n";
}