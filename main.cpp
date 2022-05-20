#include <Driver/Driver.h>

using namespace GSLanguageCompiler;

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C8>> argv) {
    return Driver::GS_Compiler::Start(argc, argv);
}

#include <AST/AST.h>

/**
 * Simple example of creating translation unit with AST builder
 * @return Translation unit declaration ptr
 */
AST::GSTranslationUnitDeclarationPtr CreateUnit() {
    // TODO create 'examples' dir and add this example

    /**
     *
     * main.gs
     *
     * func main() {
     *
     * }
     *
     */

    // create AST builder
    auto Builder = AST::GS_ASTBuilder::Create();

    // create 'main' translation unit declaration
    auto Unit = Builder->CreateTranslationUnitDeclaration("main");

    // create 'main' function signature
    auto FunctionSignature = Builder->CreateFunctionSignature(Builder->CreateI32Type());

    // create 'main' function
    auto Function = Builder->CreateFunctionDeclaration("main", FunctionSignature);

    // adding 'main' function to translation unit declaration
    Unit->AddNode(Function);

    // return translation unit declaration
    return Unit;
}

#include <Windows.h>

namespace unicode {

    inline constexpr std::uint32_t InvalidCodePoint = 0x10FFFF + 1;

    inline std::vector<std::uint8_t> InvalidBytes = {};

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

    inline std::vector<std::uint8_t> to_utf8(const std::uint32_t &codePoint) {
        auto bytes = InvalidBytes;

        auto size = utf8_size(codePoint);

        if (size == 1) {
            bytes.emplace_back(static_cast<std::uint8_t>(codePoint));
        } else if (size == 2) {
            bytes.emplace_back(0xC0 + (codePoint  >> 6));
            bytes.emplace_back(0x80 + (codePoint         & 0x3F));
        } else if (size == 3) {
            bytes.emplace_back(0xE0 + (codePoint  >> 12));
            bytes.emplace_back(0x80 + ((codePoint >> 6)  & 0x3F));
            bytes.emplace_back(0x80 + (codePoint         & 0x3F));
        } else if (size == 4) {
            bytes.emplace_back(0xF0 + (codePoint  >> 18));
            bytes.emplace_back(0x80 + ((codePoint >> 12) & 0x3F));
            bytes.emplace_back(0x80 + ((codePoint >> 6)  & 0x3F));
            bytes.emplace_back(0x80 + (codePoint         & 0x3F));
        }

        return bytes;
    }

    inline std::uint32_t from_utf8(const std::vector<std::uint8_t> &bytes) {
        auto codePoint = InvalidCodePoint;

        auto size = utf8_size(bytes[0]);

        if (size == 1) {
            codePoint = bytes[0];
        } else if (size == 2) {
            codePoint = ((bytes[0] & 0x1F) << 6)
                        +  (bytes[1] & 0x3F);
        } else if (size == 3) {
            codePoint = ((bytes[0] & 0x0F) << 12)
                        + ((bytes[1] & 0x3F) << 6)
                        +  (bytes[2] & 0x3F);
        } else if (size == 4) {
            codePoint = ((bytes[0] & 0x07) << 18)
                        + ((bytes[1] & 0x3F) << 12)
                        + ((bytes[2] & 0x3F) << 6)
                        +  (bytes[3] & 0x3F);
        }

        return codePoint;
    }

    // TODO add supporting UTF-16

    inline std::vector<std::uint8_t> to_utf16(const std::uint32_t &codePoint) {
        auto bytes = InvalidBytes;

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

    inline std::uint32_t from_utf16(const std::vector<std::uint8_t> &bytes) {
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

    inline std::vector<std::uint8_t> to_utf32(const std::uint32_t &codePoint) {
        auto bytes = InvalidBytes;

        bytes.emplace_back(codePoint  >> 24);
        bytes.emplace_back((codePoint >> 16) & 0xFF);
        bytes.emplace_back((codePoint >> 8)  & 0xFF);
        bytes.emplace_back(codePoint         & 0xFF);

        return bytes;
    }

    inline std::uint32_t from_utf32(const std::vector<std::uint8_t> &bytes) {
        auto codePoint = InvalidCodePoint;

        codePoint = (bytes[0] << 24)
                    + (bytes[1] << 16)
                    + (bytes[2] << 8)
                    + bytes[3];

        return codePoint;
    }

    class usymbol {
    public:

        usymbol()
                : _codePoint(InvalidCodePoint) {}

        usymbol(const std::uint32_t &codePoint)
                : _codePoint(codePoint) {}

    public:

        usymbol(const usymbol &symbol)
                : _codePoint(symbol._codePoint) {}

        usymbol(usymbol &&symbol) noexcept
                : _codePoint(symbol._codePoint) {}

    public:

        std::vector<std::uint8_t> as_utf8() const {
            auto bytes = to_utf8(_codePoint);

            return bytes;
        }

        std::vector<std::uint8_t> as_utf16() const {
            auto bytes = to_utf16(_codePoint);

            return bytes;
        }

        std::vector<std::uint8_t> as_utf32() const {
            auto bytes = to_utf32(_codePoint);

            return bytes;
        }

    public:

        std::uint32_t code_point() const {
            return _codePoint;
        }

    public:

        usymbol &operator=(const usymbol &symbol) {
            if (this == &symbol) {
                return *this;
            }

            _codePoint = symbol._codePoint;

            return *this;
        }

        usymbol &operator=(usymbol &&symbol) noexcept {
            if (this == &symbol) {
                return *this;
            }

            _codePoint = symbol._codePoint;

            return *this;
        }

    private:

        std::uint32_t _codePoint;
    };

    class ustring {
    public:

        ustring() = default;

        ustring(std::vector<usymbol> symbols)
                : _symbols(std::move(symbols)) {}

        ustring(const char *string) {
            for (std::uint64_t index = 0; string[index] != 0; ++index) {
                auto byte = static_cast<std::uint8_t>(string[index]);

                auto symbolSize = utf8_size(byte);

                std::vector<std::uint8_t> bytes;

                bytes.emplace_back(byte);

                for (std::uint64_t i = 1; i < symbolSize; ++i) {
                    ++index;

                    byte = static_cast<std::uint8_t>(string[index]);

                    bytes.emplace_back(byte);
                }

                auto codePoint = from_utf8(bytes);

                _symbols.emplace_back(usymbol(codePoint));
            }
        }

#if defined(__cpp_lib_char8_t)

        ustring(const char8_t *string)
                : ustring(reinterpret_cast<const char *>(string)) {}

#endif

        // TODO add supporting UTF-16 strings
        ustring(const char16_t *string);

        ustring(const char32_t *string) {
            for (std::uint64_t index = 0; string[index] != 0; ++index) {
                _symbols.emplace_back(usymbol(static_cast<std::uint32_t>(string[index])));
            }
        }

        ustring(const std::string &string)
                : ustring(string.c_str()) {}

#if defined(__cpp_lib_char8_t)

        ustring(const std::u8string &string)
                : ustring(string.c_str()) {}

#endif

        ustring(const std::u16string &string)
                : ustring(string.c_str()) {}

        ustring(const std::u32string &string)
                : ustring(string.c_str()) {}

    public:

        ustring(const ustring &string)
                : _symbols(string._symbols) {}

        ustring(ustring &&string) noexcept
                : _symbols(std::move(string._symbols)) {}

    public:

        ustring &append(const usymbol &symbol) {
            _symbols.emplace_back(symbol);

            return *this;
        }

    public:

        std::vector<usymbol> symbols() const {
            return _symbols;
        }

    public:

        std::vector<usymbol>::iterator begin() {
            return _symbols.begin();
        }

        std::vector<usymbol>::iterator end() {
            return _symbols.end();
        }

        std::vector<usymbol>::const_iterator begin() const {
            return _symbols.cbegin();
        }

        std::vector<usymbol>::const_iterator end() const {
            return _symbols.cend();
        }

    public:

        ustring &operator=(const ustring &string) {
            if (this == &string) {
                return *this;
            }

            _symbols = string._symbols;

            return *this;
        }

        ustring &operator=(ustring &&string) noexcept {
            if (this == &string) {
                return *this;
            }

            _symbols = std::move(string._symbols);

            return *this;
        }

    private:

        std::vector<usymbol> _symbols;
    };

    inline std::istream &operator>>(std::istream &stream, ustring &string) {
        while (true) {
            auto byte = static_cast<std::uint8_t>(stream.get());

            if (byte == '\n' || stream.eof()) {
                break;
            }

            auto symbolSize = utf8_size(byte);

            std::vector<std::uint8_t> bytes;

            bytes.emplace_back(byte);

            for (std::uint64_t i = 1; i < symbolSize; ++i) {
                byte = static_cast<std::uint8_t>(stream.get());

                bytes.emplace_back(byte);
            }

            auto codePoint = from_utf8(bytes);

            string.append(usymbol(codePoint));
        }

        return stream;
    }

    inline std::ostream &operator<<(std::ostream &stream, const ustring &string) {
        for (auto &symbol : string) {
            auto bytes = symbol.as_utf8();

            for (auto &byte : bytes) {
                stream << byte;
            }
        }

        return stream;
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

            std::vector<std::uint8_t> bytes;

            bytes.emplace_back(byte);

            for (std::uint64_t i = 1; i < symbolSize; ++i) {
                ++index;

                byte = static_cast<std::uint8_t>(string[index]);

                bytes.emplace_back(byte);
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

    inline unicode::ustring read_string(std::istream &stream) {
        unicode::ustring string;

        stream >> string;

        return string;
    }

    inline void write_string(std::ostream &stream, const unicode::ustring &string) {
        stream << string;
    }

    namespace details {

        bool enable_unicode_console_windows() {
#if defined(WIN32)

            if (SetConsoleCP(CP_UTF8) == TRUE && SetConsoleOutputCP(CP_UTF8) == TRUE) {
                return true;
            }
#endif

            return false;
        }

    }

    bool enable_unicode_console() {
#if defined(WIN32)

        return details::enable_unicode_console_windows();

#endif

        return false;
    }

    static bool is_enabled_unicode_console = enable_unicode_console();

}
