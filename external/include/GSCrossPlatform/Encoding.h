#ifndef GSCROSSPLATFORM_ENCODING_H
#define GSCROSSPLATFORM_ENCODING_H

#include <GSCrossPlatform/Vector.h>

inline constexpr std::uint32_t InvalidCodePoint = 0x10FFFF + 1;

inline constexpr std::uint8_t utf8_size(const std::uint32_t &codePoint) {
    auto size = 0;

    if (codePoint <= 0x7F) {
        size = 1;
    } else if (codePoint <= 0x7FF) {
        size = 2;
    } else if (codePoint <= 0xFFFF) {
        size = 3;
    } else if (codePoint <= 0x10FFFF) {
        size = 4;
    }

    return size;
}

inline constexpr std::uint8_t utf8_size(const std::uint8_t &byte) {
    auto size = 0;

    if (byte <= 0x7F) {
        size = 1;
    } else if (byte <= 0xDF) {
        size = 2;
    } else if (byte <= 0xEF) {
        size = 3;
    } else if (byte <= 0xF4) {
        size = 4;
    }

    return size;
}

inline constexpr Vector<std::uint8_t> to_utf8(const std::uint32_t &codePoint) {
    Vector<std::uint8_t> bytes;

    auto size = utf8_size(codePoint);

    if (size == 1) {
        bytes.Append(static_cast<std::uint8_t>(codePoint));
    } else if (size == 2) {
        bytes.Append(0xC0 + (codePoint >> 6));
        bytes.Append(0x80 + (codePoint & 0x3F));
    } else if (size == 3) {
        bytes.Append(0xE0 + (codePoint >> 12));
        bytes.Append(0x80 + ((codePoint >> 6) & 0x3F));
        bytes.Append(0x80 + (codePoint & 0x3F));
    } else if (size == 4) {
        bytes.Append(0xF0 + (codePoint >> 18));
        bytes.Append(0x80 + ((codePoint >> 12) & 0x3F));
        bytes.Append(0x80 + ((codePoint >> 6) & 0x3F));
        bytes.Append(0x80 + (codePoint & 0x3F));
    }

    return bytes;
}

inline constexpr std::uint32_t from_utf8(const Vector<std::uint8_t> &bytes) {
    auto codePoint = InvalidCodePoint;

    auto size = utf8_size(bytes[0]);

    if (size == 1) {
        codePoint = bytes[0];
    } else if (size == 2) {
        codePoint = ((bytes[0] & 0x1F) << 6)
                    + (bytes[1] & 0x3F);
    } else if (size == 3) {
        codePoint = ((bytes[0] & 0x0F) << 12)
                    + ((bytes[1] & 0x3F) << 6)
                    + (bytes[2] & 0x3F);
    } else if (size == 4) {
        codePoint = ((bytes[0] & 0x07) << 18)
                    + ((bytes[1] & 0x3F) << 12)
                    + ((bytes[2] & 0x3F) << 6)
                    + (bytes[3] & 0x3F);
    }

    return codePoint;
}

// TODO add supporting UTF-16

inline constexpr Vector<std::uint8_t> to_utf16(const std::uint32_t &codePoint) {
    Vector<std::uint8_t> bytes;

//        if (codePoint <= 0xD7FF || (codePoint >= 0xE000 && codePoint <= 0xFFFF)) {
//            bytes.emplace_back(codePoint >> 8);
//            bytes.emplace_back(codePoint & 0xFF);
//        } else {
//            uint16_t high = ((codePoint - 0x10000) >> 10)  + 0xD800;
//            uint16_t low = ((codePoint - 0x10000) & 0x3FF) + 0xDC00;
//            bytes.emplace_back(high >> 8);
//            bytes.emplace_back(high & 0xFF);
//            bytes.emplace_back(low >> 8);
//            bytes.emplace_back(low & 0xFF);
//        }

    return bytes;
}

inline constexpr std::uint32_t from_utf16(const Vector<std::uint8_t> &bytes) {
    auto codePoint = InvalidCodePoint;

//        auto size = utf16_size();
//
//        if (size == 2) {
//            codePoint = (bytes[0] << 8)
//                       + bytes[1];
//        }
//        if (size == 4) {
//            codePoint = 0x10000 + ((((bytes[0] << 8) + bytes[1]) - 0xD800) << 10)
//                    + (((bytes[2] << 8) + bytes[3]) - 0xDC00);
//        }

    return codePoint;
}

inline constexpr Vector<std::uint8_t> to_utf32(const std::uint32_t &codePoint) {
    Vector<std::uint8_t> bytes;

    bytes.Append(codePoint >> 24);
    bytes.Append((codePoint >> 16) & 0xFF);
    bytes.Append((codePoint >> 8) & 0xFF);
    bytes.Append(codePoint & 0xFF);

    return bytes;
}

inline constexpr std::uint32_t from_utf32(const Vector<std::uint8_t> &bytes) {
    auto codePoint = InvalidCodePoint;

    codePoint = (bytes[0] << 24)
                + (bytes[1] << 16)
                + (bytes[2] << 8)
                + bytes[3];

    return codePoint;
}

inline std::u16string utf8_to_utf16(const std::string &string) {
    std::u16string u16string;

    return u16string;
}

inline std::u32string utf8_to_utf32(const std::string &string) {
    std::u32string u32string;

    for (std::uint64_t index = 0; index < string.size(); ++index) {
        auto byte = static_cast<std::uint8_t>(string[index]);

        auto symbolSize = utf8_size(byte);

        Vector<std::uint8_t> bytes;

        bytes.Append(byte);

        for (std::uint64_t i = 1; i < symbolSize; ++i) {
            ++index;

            byte = static_cast<std::uint8_t>(string[index]);

            bytes.Append(byte);
        }

        auto codePoint = from_utf8(bytes);

        u32string += static_cast<char32_t>(codePoint);
    }

    return u32string;
}

#if defined(__cpp_lib_char8_t)

inline std::u16string utf8_to_utf16(const std::u8string &string) {
    std::u16string u16string;

    return u16string;
}

inline std::u32string utf8_to_utf32(const std::u8string &string) {
    std::u32string u32string;

    return u32string;
}

#endif

inline std::string utf16_to_utf8(const std::u16string &u16string) {
    std::string string;

    return string;
}

inline std::u32string utf16_to_utf32(const std::u16string &u16string) {
    std::u32string u32string;

    return u32string;
}

inline std::string utf32_to_utf8(const std::u32string &u32string) {
    std::string string;

    return string;
}

inline std::u16string utf32_to_utf16(const std::u32string &u32string) {
    std::u16string u16string;

    return u16string;
}

#endif //GSCROSSPLATFORM_ENCODING_H
