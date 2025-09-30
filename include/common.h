#pragma once

#include <cstdint>
#include <string>
#include <algorithm>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

inline std::string toStringFromArray(const char* data, size_t size) {
    std::string s(data, data + size);
    s.erase(std::find(s.begin(), s.end(), '\0'), s.end());
    return s;
}