#include <Driver/Driver.h>

using namespace GSLanguageCompiler;

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C>> argv) {
    return Driver::GS_Compiler::Start(argc, argv);
}

#include <IO/IO.h>

namespace io {

    class stream {
    public:

        virtual ~stream() = default;

    public:

        virtual USymbol read() = 0;

        virtual void write(USymbol symbol) = 0;

    public:

        stream &operator>>(USymbol &symbol) {
            symbol = read();

            return *this;
        }

        stream &operator<<(const USymbol &symbol) {
            write(symbol);

            return *this;
        }
    };

    class handle {
    public:

        virtual ~handle() = default;

    public:

        virtual std::unique_ptr<stream> create_stream() = 0;
    };

    class file;

    class file_stream : public stream {
    public:

        explicit file_stream(file *file)
                : _file(file) {}

    public:

        USymbol read() override;

        void write(USymbol symbol) override;

    private:

        file *_file;
    };

    class file : public handle {
    public:

        friend class file_stream;

    public:

        explicit file(FILE *file)
                : _file(file) {}

    public:

        static std::unique_ptr<file> create(FILE *fileDescriptor) {
            return std::make_unique<file>(fileDescriptor);
        }

        static std::unique_ptr<file> create(UString name) {
            return file::create(std::fopen(name.AsUTF8().c_str(), "r"));
        }

    public:

        std::unique_ptr<stream> create_stream() override {
            return std::make_unique<file_stream>(this);
        }

    private:

        FILE *_file;
    };

    USymbol file_stream::read() {
        auto byte = StaticCast<U8>(std::fgetc(_file->_file));

        auto size = UTF8Size(byte);

        Vector<U8> bytes;

        bytes.Append(byte);

        for (U64 i = 0; i < size; ++i) {
            bytes.Append(StaticCast<U8>(std::fgetc(_file->_file)));
        }

        auto codePoint = FromUTF8(bytes);

        return USymbol(codePoint);
    }

    void file_stream::write(USymbol symbol) {
        for (auto &byte : ToUTF8(symbol.CodePoint())) {
            std::fputc(byte, _file->_file);
        }
    }

    inline std::unique_ptr<stream> &operator>>(std::unique_ptr<stream> &stream, USymbol &symbol) {
        *stream >> symbol;

        return stream;
    }

    inline std::unique_ptr<stream> &operator<<(std::unique_ptr<stream> &stream, const USymbol &symbol) {
        *stream << symbol;

        return stream;
    }

    inline std::unique_ptr<handle> cout = file::create(stdout);

}

void f(std::unique_ptr<io::handle> &handle) {
    USymbol s;

    *handle->create_stream() >> s;
}

void test() {
    f(io::cout);

    auto fileStream = io::file::create("main.gs")->create_stream();

    USymbol s;

    fileStream >> s;
}
