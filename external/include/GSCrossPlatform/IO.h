#ifndef GSCROSSPLATFORM_IO_H
#define GSCROSSPLATFORM_IO_H

#if defined(WIN32)

    #include <Windows.h>

#endif

#include <iostream>

#include <GSCrossPlatform/UString.h>

inline std::istream &operator>>(std::istream &stream, UString &string) {
    while (true) {
        auto byte = static_cast<U8>(stream.get());

        if (byte == '\n' || stream.eof()) {
            break;
        }

        auto symbolSize = UTF8Size(byte);

        Vector<U8> bytes;

        bytes.Append(byte);

        for (U64 i = 1; i < symbolSize; ++i) {
            byte = static_cast<U8>(stream.get());

            bytes.Append(byte);
        }

        auto codePoint = FromUTF8(bytes);

        string.Append(USymbol(codePoint));
    }

    return stream;
}

inline std::ostream &operator<<(std::ostream &stream, const UString &string) {
    for (auto &symbol: string) {
        auto bytes = symbol.AsUTF8();

        for (auto &byte: bytes) {
            stream << byte;
        }
    }

    return stream;
}

inline Bool EnableUnicodeConsole() {
#if defined(WIN32)

    if (SetConsoleCP(CP_UTF8) == TRUE && SetConsoleOutputCP(CP_UTF8) == TRUE) {
        return true;
    }

#endif

    return false;
}

static Bool IsEnabledUnicodeConsole = EnableUnicodeConsole();

#endif //GSCROSSPLATFORM_IO_H
