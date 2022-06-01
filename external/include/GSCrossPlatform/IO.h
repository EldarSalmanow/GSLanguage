#ifndef GSCROSSPLATFORM_IO_H
#define GSCROSSPLATFORM_IO_H

#if defined(WIN32)

    #include <Windows.h>

#endif

#include <iostream>

#include <GSCrossPlatform/UString.h>

inline std::istream &operator>>(std::istream &stream, UString &string) {
    while (true) {
        auto byte = static_cast<std::uint8_t>(stream.get());

        if (byte == '\n' || stream.eof()) {
            break;
        }

        auto symbolSize = utf8_size(byte);

        Vector<std::uint8_t> bytes;

        bytes.Append(byte);

        for (std::uint64_t i = 1; i < symbolSize; ++i) {
            byte = static_cast<std::uint8_t>(stream.get());

            bytes.Append(byte);
        }

        auto codePoint = from_utf8(bytes);

        string.append(USymbol(codePoint));
    }

    return stream;
}

inline std::ostream &operator<<(std::ostream &stream, const UString &string) {
    for (auto &symbol: string) {
        auto bytes = symbol.as_utf8();

        for (auto &byte: bytes) {
            stream << byte;
        }
    }

    return stream;
}

inline bool EnableUnicodeConsole() {
#if defined(WIN32)

    if (SetConsoleCP(CP_UTF8) == TRUE && SetConsoleOutputCP(CP_UTF8) == TRUE) {
        return true;
    }

#endif

    return false;
}

static bool IsEnabledUnicodeConsole = EnableUnicodeConsole();

#endif //GSCROSSPLATFORM_IO_H
