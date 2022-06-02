#ifndef GSCROSSPLATFORM_ENCODING_H
#define GSCROSSPLATFORM_ENCODING_H

#include <GSCrossPlatform/Vector.h>

inline constexpr U32 InvalidCodePoint = 0x10FFFF + 1;

inline constexpr U8 UTF8Size(const U32 &codePoint) {
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

inline constexpr U8 UTF8Size(const U8 &byte) {
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

inline constexpr Vector<U8> ToUTF8(const U32 &codePoint) {
    Vector<U8> bytes;

    auto size = UTF8Size(codePoint);

    if (size == 1) {
        bytes.Append(static_cast<U8>(codePoint));
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

inline constexpr U32 FromUTF8(const Vector<U8> &bytes) {
    auto codePoint = InvalidCodePoint;

    auto size = UTF8Size(bytes[0]);

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

inline constexpr Vector<U8> ToUTF16(const U32 &codePoint) {
    Vector<U8> bytes;

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

inline constexpr U32 FromUTF16(const Vector<U8> &bytes) {
    auto codePoint = InvalidCodePoint;

//        auto Size = utf16_size();
//
//        if (Size == 2) {
//            codePoint = (bytes[0] << 8)
//                       + bytes[1];
//        }
//        if (Size == 4) {
//            codePoint = 0x10000 + ((((bytes[0] << 8) + bytes[1]) - 0xD800) << 10)
//                    + (((bytes[2] << 8) + bytes[3]) - 0xDC00);
//        }

    return codePoint;
}

inline constexpr Vector<U8> ToUTF32(const U32 &codePoint) {
    Vector<U8> bytes;

    bytes.Append(codePoint >> 24);
    bytes.Append((codePoint >> 16) & 0xFF);
    bytes.Append((codePoint >> 8) & 0xFF);
    bytes.Append(codePoint & 0xFF);

    return bytes;
}

inline constexpr U32 FromUTF32(const Vector<U8> &bytes) {
    auto codePoint = InvalidCodePoint;

    codePoint = (bytes[0] << 24)
                + (bytes[1] << 16)
                + (bytes[2] << 8)
                + bytes[3];

    return codePoint;
}

inline std::u16string UTF8ToUTF16(const std::string &string) {
    std::u16string u16string;

    return u16string;
}

inline std::u32string UTF8ToUTF32(const std::string &string) {
    std::u32string u32string;

    for (U64 index = 0; index < string.size(); ++index) {
        auto byte = static_cast<U8>(string[index]);

        auto symbolSize = UTF8Size(byte);

        Vector<U8> bytes;

        bytes.Append(byte);

        for (U64 i = 1; i < symbolSize; ++i) {
            ++index;

            byte = static_cast<U8>(string[index]);

            bytes.Append(byte);
        }

        auto codePoint = FromUTF8(bytes);

        u32string += static_cast<char32_t>(codePoint);
    }

    return u32string;
}

#if defined(__cpp_lib_char8_t)

inline std::u16string UTF8ToUTF16(const std::u8string &string) {
    std::u16string u16string;

    return u16string;
}

inline std::u32string UTF8ToUTF32(const std::u8string &string) {
    std::u32string u32string;

    return u32string;
}

#endif

inline std::string UTF16ToUTF8(const std::u16string &u16string) {
    std::string string;

    return string;
}

inline std::u32string UTF16ToUTF32(const std::u16string &u16string) {
    std::u32string u32string;

    return u32string;
}

inline std::string UTF32ToUTF8(const std::u32string &u32string) {
    std::string string;

    return string;
}

inline std::u16string UTF32ToUTF16(const std::u32string &u32string) {
    std::u16string u16string;

    return u16string;
}

#endif //GSCROSSPLATFORM_ENCODING_H
