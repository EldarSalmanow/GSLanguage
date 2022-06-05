#ifndef GSLANGUAGE_GS_READER_H
#define GSLANGUAGE_GS_READER_H

#include <GSCrossPlatform/CrossPlatform.h>

#include <fstream>

namespace GSLanguageCompiler::IO {

    class GS_InStreamInfo {
    public:

        GS_InStreamInfo(UString fileName, Bool isConsole)
                : _fileName(std::move(fileName)), _isConsole(isConsole) {}

    public:

        static std::shared_ptr<GS_InStreamInfo> Create(UString fileName, Bool isConsole) {
            return std::make_shared<GS_InStreamInfo>(std::move(fileName), isConsole);
        }

        static std::shared_ptr<GS_InStreamInfo> CreateFileInfo(UString fileName) {
            return GS_InStreamInfo::Create(std::move(fileName), false);
        }

        static std::shared_ptr<GS_InStreamInfo> CreateConsoleInfo() {
            return GS_InStreamInfo::Create("<console>", true);
        }

        static std::shared_ptr<GS_InStreamInfo> Create() {
            return GS_InStreamInfo::Create(UString(), false);
        }

    public:

        UString GetFileName() const {
            return _fileName;
        }

        Bool GetIsConsole() const {
            return _isConsole;
        }

    private:

        UString _fileName;

        Bool _isConsole;
    };

    class GS_InStream {
    public:

        explicit GS_InStream(std::shared_ptr<GS_InStreamInfo> streamInfo)
                : _streamInfo(std::move(streamInfo)) {}

    public:

        std::shared_ptr<GS_InStreamInfo> GetStreamInfo() const {
            return _streamInfo;
        }

    public:

        virtual LRef<std::istream> GetStream() = 0;

    private:

        std::shared_ptr<GS_InStreamInfo> _streamInfo;
    };

    class GS_InFileStream : public GS_InStream {
    public:

        explicit GS_InFileStream(std::ifstream stream, std::shared_ptr<GS_InStreamInfo> streamInfo)
                : _stream(std::move(stream)), GS_InStream(std::move(streamInfo)) {}

    public:

        static std::shared_ptr<GS_InFileStream> Create(std::ifstream stream, std::shared_ptr<GS_InStreamInfo> streamInfo) {
            return std::make_shared<GS_InFileStream>(std::move(stream), std::move(streamInfo));
        }

        static std::shared_ptr<GS_InFileStream> CreateInFile(UString name) {
            return GS_InFileStream::Create(std::ifstream(name.AsUTF8()), GS_InStreamInfo::CreateFileInfo(name));
        }

    public:

        LRef<std::istream> GetStream() override {
            return _stream;
        }

    private:

        std::ifstream _stream;
    };

    class GS_InConsoleStream : public GS_InStream {
    public:

        explicit GS_InConsoleStream(LRef<std::istream> stream, std::shared_ptr<GS_InStreamInfo> streamInfo)
                : _stream(stream), GS_InStream(std::move(streamInfo)) {}

    public:

        static std::shared_ptr<GS_InConsoleStream> Create(LRef<std::istream> stream, std::shared_ptr<GS_InStreamInfo> streamInfo) {
            return std::make_shared<GS_InConsoleStream>(stream, std::move(streamInfo));
        }

        static std::shared_ptr<GS_InConsoleStream> CreateInConsole() {
            return GS_InConsoleStream::Create(std::cin, GS_InStreamInfo::CreateConsoleInfo());
        }

    public:

        LRef<std::istream> GetStream() override {
            return _stream;
        }

    private:

        LRef<std::istream> _stream;
    };

    /**
     * Declaring text stream
     */
    class GS_TextStream;

    /**
     * Reader for read files
     */
    class GS_Reader {
    public:

        /**
         * Constructor for reader
         * @param stream Input stream
         */
        explicit GS_Reader(LRef<std::istream> stream);

    public:

        /**
         * Creating reader
         * @param stream Stream
         * @return Reader
         */
        static GS_Reader Create(LRef<std::istream> stream);

    public:

        /**
         * Reading text from source
         * @return Text
         */
        UString ReadText();

    public:

        /**
         * Creating text stream for reading text
         * @return Text stream
         */
        GS_TextStream CreateStream();

    private:

        /**
         * Stream for reading text
         */
        LRef<std::istream> _stream;
    };

}

#endif //GSLANGUAGE_GS_READER_H
