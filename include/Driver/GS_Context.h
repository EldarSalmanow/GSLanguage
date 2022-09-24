#ifndef GSLANGUAGE_GS_CONTEXT_H
#define GSLANGUAGE_GS_CONTEXT_H

#include <IO/GS_Stream.h>

#include <IO/GS_Source.h>

#include <AST/AST.h>

#include <Driver/GS_Arguments.h>

namespace GSLanguageCompiler::Driver {

    // optimize class

    /**
     *
     */
    class GS_Context {
    public:

        /**
         *
         * @param stdIOStreamsManager
         * @param sourceManager
         * @param outputStream
         * @param astContext
         */
        GS_Context(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                   IO::GSSourceManagerPtr       sourceManager,
                   IO::GSOutStreamPtr           outputStream,
                   AST::GSASTContextPtr         astContext);

    public:

        /**
         *
         * @param stdIOStreamsManager
         * @param sourceManager
         * @param outputStream
         * @param astContext
         * @return
         */
        static std::shared_ptr<GS_Context> Create(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                                                  IO::GSSourceManagerPtr       sourceManager,
                                                  IO::GSOutStreamPtr           outputStream,
                                                  AST::GSASTContextPtr         astContext);

        /**
         *
         * @param stdIOStreamsManager
         * @param sourceManager
         * @param outputStream
         * @return
         */
        static std::shared_ptr<GS_Context> Create(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                                                  IO::GSSourceManagerPtr       sourceManager,
                                                  IO::GSOutStreamPtr           outputStream);

        /**
         *
         * @param sourceManager
         * @param outputStream
         * @param astContext
         * @return
         */
        static std::shared_ptr<GS_Context> Create(IO::GSSourceManagerPtr sourceManager,
                                                  IO::GSOutStreamPtr     outputStream,
                                                  AST::GSASTContextPtr   astContext);

        /**
         *
         * @param sourceManager
         * @param outputStream
         * @return
         */
        static std::shared_ptr<GS_Context> Create(IO::GSSourceManagerPtr sourceManager,
                                                  IO::GSOutStreamPtr     outputStream);

        /**
         *
         * @return
         */
        static std::shared_ptr<GS_Context> Create();

    public:

        /**
         *
         * @param arguments
         * @return
         */
        static std::shared_ptr<GS_Context> Create(GS_Arguments arguments);

    public:

        /**
         * Read string from standard input stream from standard IO streams manager
         * @param string String for reading
         * @return
         */
        Void In(LRef<UString> string);

        /**
         * Write string to standard output stream from standard IO streams manager
         * @param string String for writing
         * @return
         */
        Void Out(ConstLRef<UString> string);

        /**
         * Write string to standard error stream from standard IO streams manager
         * @param string String for writing
         * @return
         */
        Void Err(ConstLRef<UString> string);

        /**
         * Write string to standard logging stream from standard IO streams manager
         * @param string String for writing
         * @return
         */
        Void Log(ConstLRef<UString> string);

        /**
         * Getter for standard input stream from standard IO streams manager
         * @return Standard input stream
         */
        IO::GSInStreamPtr GetStdInStream() const;

        /**
         * Getter for standard output stream from standard IO streams manager
         * @return Standard output stream
         */
        IO::GSOutStreamPtr GetStdOutStream() const;

        /**
         * Getter for standard error stream from standard IO streams manager
         * @return Standard error stream
         */
        IO::GSOutStreamPtr GetStdErrStream() const;

        /**
         * Getter for standard logging stream from standard IO streams manager
         * @return Standard logging stream
         */
        IO::GSOutStreamPtr GetStdLogStream() const;

    public:

        /**
         * Add source to source manager
         * @param source Source
         * @return Source hash
         */
        U64 AddSource(IO::GSSourcePtr source);

        /**
         * Get source from source manager by source hash
         * @param sourceHash Source hash
         * @return Source or nullptr
         */
        IO::GSSourcePtr GetSource(U64 sourceHash) const;

        /**
         * Get source from source manager by source name
         * @param sourceName Source name
         * @return Source or nullptr
         */
        IO::GSSourcePtr GetSource(IO::GS_SourceName sourceName) const;

        /**
         * Getter for sources from source manager
         * @return Sources
         */
        IO::GSSourcePtrArray GetSources() const;

    public:

        // for writing code to output stream

    public:

        /**
         * Getter for default Void type from AST context
         * @return Void type
         */
        std::shared_ptr<Semantic::GS_VoidType> GetVoidType() const;

        /**
         * Getter for default I32 type from AST context
         * @return I32 type
         */
        std::shared_ptr<Semantic::GS_I32Type> GetI32Type() const;

        /**
         * Getter for default String type from AST context
         * @return String type
         */
        std::shared_ptr<Semantic::GS_StringType> GetStringType() const;

        /**
         * Getter for type context from AST context
         * @return Type context
         */
        Semantic::GSTypeContextPtr GetTypeContext() const;

    public:

        /**
         *
         * @return
         */
        IO::GSStdIOStreamsManagerPtr GetStdIOStreamsManager() const;

        /**
         *
         * @return
         */
        IO::GSSourceManagerPtr GetSourceManager() const;

        /**
         *
         * @return
         */
        IO::GSOutStreamPtr GetOutputStream() const;

        /**
         *
         * @return
         */
        AST::GSASTContextPtr GetASTContext() const;

    private:

        /**
         *
         */
        IO::GSStdIOStreamsManagerPtr _stdIOStreamsManager;

        /**
         *
         */
        IO::GSSourceManagerPtr _sourceManager;

        /**
         *
         */
        IO::GSOutStreamPtr   _outputStream;

        /**
         *
         */
        AST::GSASTContextPtr _astContext;
    };

    using GSContextPtr = std::shared_ptr<GS_Context>;

}

#endif //GSLANGUAGE_GS_CONTEXT_H
