#ifndef GSLANGUAGE_GS_STREAMS_H
#define GSLANGUAGE_GS_STREAMS_H

#include <fstream>
#include <iostream>

namespace Streams {

    template<typename T>
    class GS_Stream {
    public:

        using SymbolT = T;

    public:

        virtual ~GS_Stream() = default;
    };

    template<typename T>
    class GS_IStream : public GS_Stream<T> {
    public:

        virtual typename GS_Stream<T>::SymbolT read() = 0;

    public:

        virtual GS_IStream<T> &operator>>(typename GS_Stream<T>::SymbolT &symbol) = 0;
    };

    template<typename T>
    class GS_OStream : public GS_Stream<T> {
    public:

        virtual void write(typename GS_Stream<T>::SymbolT symbol) = 0;

    public:

        virtual GS_OStream<T> &operator<<(typename GS_Stream<T>::SymbolT symbol) = 0;

        virtual GS_OStream<T> &operator<<(int number) {
            return *this;
        }

        virtual GS_OStream<T> &operator<<(GS_OStream<T> &(*modifier)(GS_OStream<T>&)) {
            return modifier(*this);
        }
    };

    enum class StreamState {
        OPENED,
        CLOSED
    };

    template<typename T>
    class GS_FileStream : public GS_Stream<T> {
    public:

        GS_FileStream()
        : _state(StreamState::CLOSED) {};

        explicit GS_FileStream(std::string_view filename)
        : _filename(filename), _state(StreamState::CLOSED) {}

    public:

        virtual void open() = 0;

        virtual void open(std::string_view filename) = 0;

        virtual void close() = 0;

        virtual bool isOpen() {
            return _state == StreamState::OPENED;
        }

        virtual bool isEof() = 0;

        virtual StreamState getState() {
            return _state;
        }

    protected:

        std::string_view _filename;

        StreamState _state;
    };

    template<typename T>
    class GS_IFileStream : public GS_FileStream<T>, public GS_IStream<T> {
    public:

        GS_IFileStream() = default;

        explicit GS_IFileStream(std::string_view filename)
        : GS_FileStream<T>(filename) {}

        explicit GS_IFileStream(std::basic_ifstream<T> *fileStream)
        : _fileStream(*fileStream) {}

        GS_IFileStream(std::string_view filename, std::basic_ifstream<T> *fileStream)
        : GS_FileStream<T>(filename), _fileStream(*fileStream) {}

    public:

        void open() override {
            if (GS_FileStream<T>::isOpen()) {
                return;
            }

            _fileStream.open(GS_FileStream<T>::_filename.data(), std::ios::binary);

            if (_fileStream.is_open()) {
                GS_FileStream<T>::_state = StreamState::OPENED;
            } else {
                GS_FileStream<T>::_state = StreamState::CLOSED;
            }
        }

        void open(std::string_view filename) override {
            _fileStream.open(filename.data(), std::ios::binary);

            if (_fileStream.is_open()) {
                GS_FileStream<T>::_state = StreamState::OPENED;

                return;
            }

            GS_FileStream<T>::_state = StreamState::CLOSED;
        }

        void close() override {
            if (GS_FileStream<T>::isOpen()) {
                _fileStream.close();

                GS_FileStream<T>::_state = StreamState::CLOSED;
            }
        }

        bool isEof() override {
            return _fileStream.eof();
        }

    public:

        typename GS_IStream<T>::SymbolT read() override {
            return static_cast<T>(_fileStream.get());
        }

    public:

        GS_IStream<T> &operator>>(typename GS_Stream<T>::SymbolT &symbol) override {
            symbol = read();

            return *this;
        }

    protected:

        std::basic_ifstream<T> _fileStream;
    };

    template<typename T>
    class GS_OFileStream : public GS_FileStream<T>, public GS_OStream<T> {
    public:

        GS_OFileStream() = default;

        explicit GS_OFileStream(std::string_view filename)
        : GS_FileStream<T>(filename) {}

        explicit GS_OFileStream(std::basic_ifstream<T> *fileStream)
        : _fileStream(*fileStream) {}

        GS_OFileStream(std::string_view filename, std::basic_ifstream<T> *fileStream)
        : GS_FileStream<T>(filename), _fileStream(*fileStream) {}

    public:

        void open() override {
            if (GS_FileStream<T>::isOpen()) {
                return;
            }

            _fileStream.open(GS_FileStream<T>::_filename.data(), std::ios::binary);

            if (_fileStream.is_open()) {
                GS_FileStream<T>::_state = StreamState::OPENED;
            } else {
                GS_FileStream<T>::_state = StreamState::CLOSED;
            }
        }

        void open(std::string_view filename) override {
            _fileStream.open(filename.data(), std::ios::binary);

            if (_fileStream.is_open()) {
                GS_FileStream<T>::_state = StreamState::OPENED;

                return;
            }

            GS_FileStream<T>::_state = StreamState::CLOSED;
        }

        void close() override {
            if (GS_FileStream<T>::isOpen()) {
                _fileStream.close();

                GS_FileStream<T>::_state = StreamState::CLOSED;
            }
        }

        bool isEof() override {
            return _fileStream.eof();
        }

    public:

        void write(typename GS_Stream<T>::SymbolT symbol) override {
            _fileStream.write(reinterpret_cast<char *>(&symbol), 1);
        }

    public:

        GS_OStream<T> &operator<<(typename GS_Stream<T>::SymbolT symbol) override {
            write(symbol);

            return *this;
        }

        GS_OStream<T> &operator<<(int number) override {
            for (auto &symbol : std::to_string(number)) {
                write(symbol);
            }

            return *this;
        }

    protected:

        std::basic_ofstream<T> _fileStream;
    };

    template<typename T>
    class GS_ConsoleStream : public GS_Stream<T> {
    public:

        GS_ConsoleStream() = default;
    };

    template<typename T>
    class GS_IConsoleStream : public GS_ConsoleStream<T>, public GS_IStream<T> {
    public:

        GS_IConsoleStream()
        : _consoleStream(&std::cin) {};

        explicit GS_IConsoleStream(std::basic_istream<T> *consoleStream)
        : _consoleStream(consoleStream) {}

    public:

        typename GS_Stream<T>::SymbolT read() override {
            return static_cast<T>(_consoleStream->get());
        }

    public:

        GS_IStream<T> &operator>>(typename GS_Stream<T>::SymbolT &symbol) override {
            symbol = read();

            return *this;
        }

    protected:

        std::basic_istream<T> *_consoleStream;
    };

    template<typename T>
    class GS_OConsoleStream : public GS_ConsoleStream<T>, public GS_OStream<T> {
    public:

        GS_OConsoleStream()
        : _consoleStream(&std::cout) {}

        explicit GS_OConsoleStream(std::basic_ostream<T> *consoleStream)
        : _consoleStream(consoleStream) {}

    public:

        void write(typename GS_Stream<T>::SymbolT symbol) override {
            _consoleStream->write(reinterpret_cast<char *>(&symbol), 1);
        }

    public:

        GS_OStream<T> &operator<<(typename GS_Stream<T>::SymbolT symbol) override {
            write(symbol);

            return *this;
        }

        GS_OStream<T> &operator<<(int number) override {
            for (auto &symbol : std::to_string(number)) {
                write(symbol);
            }

            return *this;
        }

    protected:

        std::basic_ostream<T> *_consoleStream;
    };

    template<typename T>
    class GS_StringStream : public GS_OStream<T> {
    public:

        GS_StringStream() = default;

    public:

        std::basic_string<T> toString() {
            return _stringBuffer;
        }

    public:

        void write(typename GS_Stream<T>::SymbolT symbol) override {
            _stringBuffer += symbol;
        }

    public:

        GS_OStream<T> &operator<<(typename GS_Stream<T>::SymbolT symbol) override {
            write(symbol);

            return *this;
        }

        GS_OStream<T> &operator<<(int number) override {
            for (auto &symbol : std::to_string(number)) {
                write(symbol);
            }

            return *this;
        }

    protected:

        std::basic_string<T> _stringBuffer;
    };

    inline GS_OConsoleStream<char> COut(&std::cout);

    inline GS_IConsoleStream<char> CIn(&std::cin);

    inline GS_OConsoleStream<char> CErr(&std::cerr);

    inline GS_OConsoleStream<char> CLog(&std::clog);

    using OStream = GS_OStream<char>;

    using IStream = GS_IStream<char>;

    using OCStream = GS_OConsoleStream<char>;

    using ICStream = GS_IConsoleStream<char>;

    using OFStream = GS_OFileStream<char>;

    using IFStream = GS_IFileStream<char>;

    using SStream = GS_StringStream<char>;

    inline OStream &operator<<(OStream &stream, std::string_view string) {
        for (auto &symbol : string) {
            stream.write(symbol);
        }

        return stream;
    }

    inline GS_IStream<char> &operator>>(IStream &stream, std::string &string) {
        auto symbol = stream.read();

        while (symbol != '\n') {
            string += symbol;

            symbol = stream.read();
        }

        return stream;
    }

    template<typename T>
    inline GS_OStream<T> &EndL(OStream &stream) {
        stream.write(static_cast<T>('\n'));

        return stream;
    }

}

#endif //GSLANGUAGE_GS_STREAMS_H
