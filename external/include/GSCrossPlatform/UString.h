#ifndef GSCROSSPLATFORM_USTRING_H
#define GSCROSSPLATFORM_USTRING_H

#include <GSCrossPlatform/Encoding.h>

class USymbol {
public:

    constexpr USymbol()
            : _codePoint(InvalidCodePoint) {}

    constexpr USymbol(const std::uint32_t &codePoint)
            : _codePoint(codePoint) {}

public:

    constexpr USymbol(const USymbol &symbol)
            : _codePoint(symbol._codePoint) {}

    constexpr USymbol(USymbol &&symbol) noexcept
            : _codePoint(symbol._codePoint) {}

public:

    inline constexpr Vector<std::uint8_t> as_utf8() const {
        auto bytes = to_utf8(_codePoint);

        return bytes;
    }

    inline constexpr Vector<std::uint8_t> as_utf16() const {
        auto bytes = to_utf16(_codePoint);

        return bytes;
    }

    inline constexpr Vector<std::uint8_t> as_utf32() const {
        auto bytes = to_utf32(_codePoint);

        return bytes;
    }

public:

    inline constexpr std::uint32_t code_point() const {
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

    inline constexpr bool operator==(const USymbol &symbol) const {
        return _codePoint == symbol._codePoint;
    }

    inline constexpr bool operator!=(const USymbol &symbol) const {
        return !(*this == symbol);
    }

private:

    std::uint32_t _codePoint;
};

class UString {
public:

    constexpr UString() = default;

    constexpr UString(Vector<USymbol> symbols)
            : _symbols(std::move(symbols)) {}

    constexpr UString(const char *string) {
        for (std::uint64_t index = 0; string[index] != 0; ++index) {
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
        for (std::uint64_t index = 0; string[index] != 0; ++index) {
            _symbols.Append(USymbol(static_cast<std::uint32_t>(string[index])));
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

    inline constexpr UString &append(const USymbol &symbol) {
        _symbols.Append(symbol);

        return *this;
    }

public:

    inline constexpr std::uint64_t size() const {
        return _symbols.Size();
    }

    inline constexpr bool empty() const {
        return _symbols.Empty();
    }

public:

    inline std::string as_utf8() const {
        std::string string;

        for (auto &symbol: _symbols) {
            for (auto &byte : to_utf8(symbol.code_point())) {
                string += static_cast<char>(byte);
            }
        }

        return string;
    }

    inline std::u16string as_utf16() const {
        std::u16string u16string;

        // ...

        return u16string;
    }

    inline std::u32string as_utf32() const {
        std::u32string u32string;

        for (auto &symbol: _symbols) {
            u32string += static_cast<char32_t>(symbol.code_point());
        }

        return u32string;
    }

public:

    inline constexpr Vector<USymbol> symbols() const {
        return _symbols;
    }

public:

    inline constexpr Vector<USymbol>::Iterator begin() {
        return _symbols.begin();
    }

    inline constexpr Vector<USymbol>::Iterator end() {
        return _symbols.end();
    }

    inline constexpr Vector<USymbol>::ConstIterator begin() const {
        return _symbols.begin();
    }

    inline constexpr Vector<USymbol>::ConstIterator end() const {
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

    inline constexpr bool operator==(const UString &string) const {
        if (size() != string.size()) {
            return false;
        }

        for (std::uint64_t index = 0; index < size(); ++index) {
            if ((*this)[index] != string[index]) {
                return false;
            }
        }

        return true;
    }

    inline constexpr bool operator!=(const UString &string) const {
        return !(*this == string);
    }

    inline constexpr auto operator<=>(const UString &string) const {
        return size() <=> string.size();
    }

    inline constexpr USymbol &operator[](const std::uint64_t &index) {
        return _symbols[index];
    }

    inline constexpr const USymbol &operator[](const std::uint64_t &index) const {
        return _symbols[index];
    }

private:

    Vector<USymbol> _symbols;
};

inline constexpr UString operator""_us(const char *string, std::uint64_t size) {
    return UString(string);
}

#if defined(__cpp_lib_char8_t)

inline constexpr UString operator""_us(const char8_t *string, std::uint64_t size) {
    return UString(string);
}

#endif

inline constexpr UString operator""_us(const char16_t *string, std::uint64_t size) {
    return UString(string);
}

inline constexpr UString operator""_us(const char32_t *string, std::uint64_t size) {
    return UString(string);
}

#endif //GSCROSSPLATFORM_USTRING_H
