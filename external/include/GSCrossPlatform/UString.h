#ifndef GSCROSSPLATFORM_USTRING_H
#define GSCROSSPLATFORM_USTRING_H

#include <GSCrossPlatform/Encoding.h>

class USymbol {
public:

    constexpr USymbol()
            : _codePoint(InvalidCodePoint) {}

    constexpr USymbol(const U32 &codePoint)
            : _codePoint(codePoint) {}

public:

    constexpr USymbol(const USymbol &symbol)
            : _codePoint(symbol._codePoint) {}

    constexpr USymbol(USymbol &&symbol) noexcept
            : _codePoint(symbol._codePoint) {}

public:

    inline constexpr Vector<U8> AsUTF8() const {
        auto bytes = ToUTF8(_codePoint);

        return bytes;
    }

    inline constexpr Vector<U8> AsUTF16() const {
        auto bytes = ToUTF16(_codePoint);

        return bytes;
    }

    inline constexpr Vector<U8> AsUTF32() const {
        auto bytes = ToUTF32(_codePoint);

        return bytes;
    }

public:

    inline constexpr U32 CodePoint() const {
        return _codePoint;
    }

public:

    inline constexpr USymbol &operator=(const USymbol &symbol) {
        if (this == &symbol) {
            return *this;
        }

        _codePoint = symbol._codePoint;

        return *this;
    }

    inline constexpr USymbol &operator=(USymbol &&symbol) noexcept {
        if (this == &symbol) {
            return *this;
        }

        _codePoint = symbol._codePoint;

        return *this;
    }

    inline constexpr Bool operator==(const USymbol &symbol) const {
        return _codePoint == symbol._codePoint;
    }

    inline constexpr Bool operator!=(const USymbol &symbol) const {
        return !(*this == symbol);
    }

private:

    U32 _codePoint;
};

class UString {
public:

    using Iterator = Vector<USymbol>::Iterator;

    using ConstIterator = Vector<USymbol>::ConstIterator;

public:

    constexpr UString() = default;

    constexpr UString(Vector<USymbol> symbols)
            : _symbols(std::move(symbols)) {}

    constexpr UString(const char *string) {
        for (U64 index = 0; string[index] != 0; ++index) {
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

            _symbols.Append(USymbol(codePoint));
        }
    }

#if defined(__cpp_lib_char8_t)

    constexpr UString(const char8_t *string)
            : UString(reinterpret_cast<const char *>(string)) {}

#endif

    // TODO add supporting UTF-16 strings
    constexpr UString(const char16_t *string);

    constexpr UString(const char32_t *string) {
        for (U64 index = 0; string[index] != 0; ++index) {
            _symbols.Append(USymbol(static_cast<U32>(string[index])));
        }
    }

    constexpr UString(const std::string &string)
            : UString(string.c_str()) {}

#if defined(__cpp_lib_char8_t)

    constexpr UString(const std::u8string &string)
            : UString(string.c_str()) {}

#endif

    constexpr UString(const std::u16string &string)
            : UString(string.c_str()) {}

    constexpr UString(const std::u32string &string)
            : UString(string.c_str()) {}

public:

    constexpr UString(const UString &string)
            : _symbols(string._symbols) {}

    constexpr UString(UString &&string) noexcept
            : _symbols(std::move(string._symbols)) {}

public:

    inline constexpr UString &Append(const USymbol &symbol) {
        _symbols.Append(symbol);

        return *this;
    }

public:

    inline constexpr U64 Size() const {
        return _symbols.Size();
    }

    inline constexpr Bool Empty() const {
        return _symbols.Empty();
    }

public:

    inline std::string AsUTF8() const {
        std::string string;

        for (auto &symbol: _symbols) {
            for (auto &byte : ToUTF8(symbol.CodePoint())) {
                string += static_cast<char>(byte);
            }
        }

        return string;
    }

    inline std::u16string AsUTF16() const {
        std::u16string u16string;

        // ...

        return u16string;
    }

    inline std::u32string AsUTF32() const {
        std::u32string u32string;

        for (auto &symbol: _symbols) {
            u32string += static_cast<char32_t>(symbol.CodePoint());
        }

        return u32string;
    }

public:

    inline constexpr Iterator begin() {
        return _symbols.begin();
    }

    inline constexpr Iterator end() {
        return _symbols.end();
    }

    inline constexpr ConstIterator begin() const {
        return _symbols.begin();
    }

    inline constexpr ConstIterator end() const {
        return _symbols.end();
    }

public:

    inline constexpr UString &operator=(const UString &string) {
        if (this == &string) {
            return *this;
        }

        _symbols = string._symbols;

        return *this;
    }

    inline constexpr UString &operator=(UString &&string) noexcept {
        if (this == &string) {
            return *this;
        }

        _symbols = std::move(string._symbols);

        return *this;
    }

    inline constexpr UString &operator+=(const USymbol &symbol) {
        _symbols.Append(symbol);

        return *this;
    }

    inline constexpr UString &operator+=(const UString &string) {
        for (auto &symbol : string) {
            _symbols.Append(symbol);
        }

        return *this;
    }

    inline constexpr UString operator+(const USymbol &symbol) const {
        UString outputString;

        outputString += *this;

        outputString += symbol;

        return outputString;
    }

    inline constexpr UString operator+(const UString &string) const {
        UString outputString;

        outputString += *this;

        outputString += string;

        return outputString;
    }

    inline constexpr Bool operator==(const UString &string) const {
        if (Size() != string.Size()) {
            return false;
        }

        for (U64 index = 0; index < Size(); ++index) {
            if ((*this)[index] != string[index]) {
                return false;
            }
        }

        return true;
    }

    inline constexpr Bool operator!=(const UString &string) const {
        return !(*this == string);
    }

    inline constexpr auto operator<=>(const UString &string) const {
        return Size() <=> string.Size();
    }

    inline constexpr USymbol &operator[](const U64 &index) {
        return _symbols[index];
    }

    inline constexpr const USymbol &operator[](const U64 &index) const {
        return _symbols[index];
    }

private:

    Vector<USymbol> _symbols;
};

inline constexpr UString operator""_us(const char *string, U64 size) {
    return UString(string);
}

#if defined(__cpp_lib_char8_t)

inline constexpr UString operator""_us(const char8_t *string, U64 size) {
    return UString(string);
}

#endif

inline constexpr UString operator""_us(const char16_t *string, U64 size) {
    return UString(string);
}

inline constexpr UString operator""_us(const char32_t *string, U64 size) {
    return UString(string);
}

#endif //GSCROSSPLATFORM_USTRING_H
