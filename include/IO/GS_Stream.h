#ifndef GSLANGUAGE_GS_STREAM_H
#define GSLANGUAGE_GS_STREAM_H

#include <fstream>

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::IO {

    /**
     * Class for containing information about I/O stream
     */
    class GS_StreamInfo {
    public:

        /**
         * Constructor for stream info
         * @param fileName File name
         */
        explicit GS_StreamInfo(UString fileName);

    public:

        /**
         * Creating stream info
         * @param fileName File name
         * @return Stream info ptr
         */
        static std::shared_ptr<GS_StreamInfo> Create(UString fileName);

        /**
         * Creating file stream info
         * @param fileName File name
         * @return Stream info ptr
         */
        static std::shared_ptr<GS_StreamInfo> CreateFileInfo(UString fileName);

        /**
         * Creating console stream info
         * @return Stream info ptr
         */
        static std::shared_ptr<GS_StreamInfo> CreateConsoleInfo();

    public:

        /**
         * Is file stream info
         * @return Is file stream info
         */
        Bool IsFile() const;

        /**
         * Is console stream info
         * @return Is console stream info
         */
        Bool IsConsole() const;

    public:

        /**
         * Getter for file name
         * @return File name
         */
        UString GetFileName() const;

    private:

        /**
         * File name
         */
        UString _fileName;
    };

    /**
     * Stream info ptr type
     */
    using GSStreamInfoPtr = std::shared_ptr<GS_StreamInfo>;

    /**
     * Base class for I/O streams
     */
    class GS_Stream {
    public:

        /**
         * Constructor for stream
         * @param streamInfo Stream info
         */
        explicit GS_Stream(GSStreamInfoPtr streamInfo);

    public:

        /**
         * Getter for stream info
         * @return Stream info
         */
        GSStreamInfoPtr GetStreamInfo() const;

    private:

        /**
         * Stream info
         */
        GSStreamInfoPtr _streamInfo;
    };

    /**
     * Input stream
     */
    class GS_InStream : public GS_Stream {
    public:

        /**
         * Constructor for input stream
         * @param streamInfo Stream info
         */
        explicit GS_InStream(GSStreamInfoPtr streamInfo);

    public:

        /**
         * Getter for standard input stream
         * @return Standard input stream
         */
        virtual LRef<std::istream> GetInStream() = 0;
    };

    /**
     * Input stream ptr type
     */
    using GSInStreamPtr = std::unique_ptr<GS_InStream>;

    /**
     * Input file stream
     */
    class GS_InFileStream : public GS_InStream {
    public:

        /**
         * Constructor for input file stream
         * @param stream Standard input file stream
         * @param streamInfo Stream info
         */
        explicit GS_InFileStream(std::ifstream stream, GSStreamInfoPtr streamInfo);

    public:

        /**
         * Creating input file stream
         * @param stream Standard input file stream
         * @param streamInfo Stream info
         * @return Input file stream ptr
         */
        static std::unique_ptr<GS_InFileStream> Create(std::ifstream stream, GSStreamInfoPtr streamInfo);

        /**
         * Creating input file stream
         * @param name File name
         * @return Input file stream ptr
         */
        static std::unique_ptr<GS_InFileStream> CreateInFile(UString name);

    public:

        /**
         * Getter for standard input stream
         * @return Standard input stream
         */
        LRef<std::istream> GetInStream() override;

    private:

        /**
         * Standard input file stream
         */
        std::ifstream _stream;
    };

    /**
     * Input console stream
     */
    class GS_InConsoleStream : public GS_InStream {
    public:

        /**
         * Constructor for input console stream
         * @param stream Standard input console stream
         * @param streamInfo Stream info
         */
        explicit GS_InConsoleStream(LRef<std::istream> stream, GSStreamInfoPtr streamInfo);

    public:

        /**
         * Creating input console stream
         * @param stream Standard input console stream
         * @param streamInfo Stream info
         * @return Input console stream ptr
         */
        static std::unique_ptr<GS_InConsoleStream> Create(LRef<std::istream> stream, GSStreamInfoPtr streamInfo);

        /**
         * Creating input console stream (std::cin standard stream)
         * @return Input console stream ptr
         */
        static std::unique_ptr<GS_InConsoleStream> CreateCIn();

    public:

        /**
         * Getter for standard input stream
         * @return Standard input stream
         */
        LRef<std::istream> GetInStream() override;

    private:

        /**
         * Standard input console stream
         */
        LRef<std::istream> _stream;
    };

    /**
     * Output stream
     */
    class GS_OutStream : public GS_Stream {
    public:

        /**
         * Constructor for output stream
         * @param streamInfo Stream info
         */
        explicit GS_OutStream(GSStreamInfoPtr streamInfo);

    public:

        /**
         * Getter for standard output stream
         * @return Standard output stream
         */
        virtual LRef<std::ostream> GetOutStream() = 0;
    };

    /**
     * Output stream ptr type
     */
    using GSOutStreamPtr = std::unique_ptr<GS_OutStream>;

    /**
     * Output file stream
     */
    class GS_OutFileStream : public GS_OutStream {
    public:

        /**
         * Constructor for output file stream
         * @param stream Standard output file stream
         * @param streamInfo Stream info
         */
        explicit GS_OutFileStream(std::ofstream stream, GSStreamInfoPtr streamInfo);

    public:

        /**
         * Creating output file stream
         * @param stream Standard output file stream
         * @param streamInfo Stream info
         * @return Output file stream ptr
         */
        static std::unique_ptr<GS_OutFileStream> Create(std::ofstream stream, GSStreamInfoPtr streamInfo);

        /**
         * Creating output file stream
         * @param name File name
         * @return Output file stream ptr
         */
        static std::unique_ptr<GS_OutFileStream> CreateOutFile(UString name);

    public:

        /**
         * Getter for standard output stream
         * @return Standard output stream
         */
        LRef<std::ostream> GetOutStream() override;

    private:

        /**
         * Standard output file stream
         */
        std::ofstream _stream;
    };

    /**
     * Output console stream
     */
    class GS_OutConsoleStream : public GS_OutStream {
    public:

        /**
         * Constructor for output console stream
         * @param stream Standard output console stream
         * @param streamInfo Stream info
         */
        explicit GS_OutConsoleStream(LRef<std::ostream> stream, GSStreamInfoPtr streamInfo);

    public:

        /**
         * Creating output console stream
         * @param stream Standard output console stream
         * @param streamInfo Stream info
         * @return Output console stream
         */
        static std::unique_ptr<GS_OutConsoleStream> Create(LRef<std::ostream> stream, GSStreamInfoPtr streamInfo);

        /**
         * Creating output console stream (std::cout standard stream)
         * @return Output console stream ptr
         */
        static std::unique_ptr<GS_OutConsoleStream> CreateCOut();

        /**
         * Creating output console stream (std::cerr standard stream)
         * @return Output console stream ptr
         */
        static std::unique_ptr<GS_OutConsoleStream> CreateCErr();

        /**
         * Creating output console stream (std::clog standard stream)
         * @return Output console stream ptr
         */
        static std::unique_ptr<GS_OutConsoleStream> CreateCLog();

    public:

        /**
         * Getter for standard output stream
         * @return Standard output stream
         */
        LRef<std::ostream> GetOutStream() override;

    private:

        /**
         * Standard output console stream
         */
        LRef<std::ostream> _stream;
    };

}

#endif //GSLANGUAGE_GS_STREAM_H
