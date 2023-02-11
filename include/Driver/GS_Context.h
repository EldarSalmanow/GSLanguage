#ifndef GSLANGUAGE_GS_CONTEXT_H
#define GSLANGUAGE_GS_CONTEXT_H

#include <IO/IO.h>

#include <AST/AST.h>

#include <Driver/GS_Arguments.h>

#include <Driver/GS_GlobalContext.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for containing and manipulating constantly information about compiling process
     */
    class GS_Context {
    public:

        /*
         *
         * GS_Context PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Creating context
         * @param stdIOStreamsManager Standard IO streams manager
         * @param sourceManager Source manager
         * @param messageStreamsManager Message streams manager
         */
        GS_Context(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                   IO::GSSourceManagerPtr sourceManager,
                   IO::GSMessageStreamsManagerPtr messageStreamsManager);

    public:

        /*
         *
         * GS_Context PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating context
         * @param stdIOStreamsManager Standard IO streams manager
         * @param sourceManager Source manager
         * @param messageStreamsManager Message streams manager
         * @return Context ptr
         */
        static std::unique_ptr<GS_Context> Create(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                                                  IO::GSSourceManagerPtr sourceManager,
                                                  IO::GSMessageStreamsManagerPtr messageStreamsManager);

        /**
         * Creating context
         * @param sourceManager Source manager
         * @return Context ptr
         */
        static std::unique_ptr<GS_Context> Create(IO::GSSourceManagerPtr sourceManager);

        /**
         * Creating context
         * @return Context ptr
         */
        static std::unique_ptr<GS_Context> Create();

        /**
         * Creating context from arguments
         * @param arguments Arguments
         * @return Context ptr
         */
        static std::unique_ptr<GS_Context> Create(GS_Arguments arguments);

    public:

        /*
         *
         * GS_Context PUBLIC METHODS
         *
         */

        /**
         * Getting standard input stream from standard IO streams manager for reading data from stream
         * @return Standard input stream
         */
        LRef<std::istream> StdIn();

        /**
         * Getting standard output stream from standard IO streams manager for writing data to stream
         * @return Standard output stream
         */
        LRef<std::ostream> StdOut();

        /**
         * Getting standard error stream from standard IO streams manager for writing data to stream
         * @return Standard error stream
         */
        LRef<std::ostream> StdErr();

        /**
         * Getting standard logging stream from standard IO streams manager for writing data to stream
         * @return Standard logging stream
         */
        LRef<std::ostream> StdLog();

        /**
         * Add source to source manager
         * @param source Source
         * @return Source hash
         */
        ConstLRef<IO::GS_Source> AddSource(IO::GSSourcePtr source);

        /**
         * Adding file source to source manager
         * @param name File name
         * @return File source
         */
        ConstLRef<IO::GS_Source> AddFileSource(UString name);

        /**
         * Adding string source to source manager
         * @param source Source code
         * @return String source
         */
        ConstLRef<IO::GS_Source> AddStringSource(UString source);

        /**
         * Adding custom source to source manager
         * @param source Source code
         * @param name Source name
         * @return Custom source
         */
        ConstLRef<IO::GS_Source> AddCustomSource(UString source,
                                                 UString name);

        /**
         * Get source from source manager by source hash
         * @param sourceHash Source hash
         * @return Source or null
         */
        std::optional<IO::GS_Source> GetSource(U64 sourceHash) const;

        /**
         * Get source from source manager by source name
         * @param sourceName Source name
         * @return Source or null
         */
        std::optional<IO::GS_Source> GetSource(IO::GS_SourceName sourceName) const;

        /**
         * Get file source from source manager by file name
         * @param fileName File name
         * @return File source or null
         */
        std::optional<IO::GS_Source> GetFileSource(UString fileName) const;

        /**
         * Get custom source from source manager by source name
         * @return Custom source or null
         */
        std::optional<IO::GS_Source> GetCustomSource(UString sourceName) const;

        /**
         * Get sources from source manager
         * @return Sources
         */
        ConstLRef<IO::GSSourcePtrArray> GetSources() const;

        /**
         * Getting output message stream for writing message in stream from message streams manager
         * @return Output message stream
         */
        LRef<IO::GS_MessageStream> Out();

        /**
         * Getting error message stream for writing message in stream from message streams manager
         * @return
         */
        LRef<IO::GS_MessageStream> Err();

        /**
         * Getting logging message stream for writing message in stream from message streams manager
         * @return Loging message stream
         */
        LRef<IO::GS_MessageStream> Log();

    public:

        /*
         *
         * GS_Context PUBLIC GETTERS
         *
         */

        /**
         * Getter for standard IO streams manager
         * @return Standard IO streams manager
         */
        LRef<IO::GS_StdIOStreamsManager> GetStdIOStreamsManager();

        /**
         * Getter for source manager
         * @return Source manager
         */
        LRef<IO::GS_SourceManager> GetSourceManager();

        /**
         * Getter for message streams manager
         * @return Message streams manager
         */
        LRef<IO::GS_MessageStreamsManager> GetMessageStreamsManager();

    private:

        /*
         *
         * GS_Context PRIVATE FIELDS
         *
         */

        /**
         * Standard IO streams manager
         */
        IO::GSStdIOStreamsManagerPtr _stdIOStreamsManager;

        /**
         * Source manager
         */
        IO::GSSourceManagerPtr _sourceManager;

        /**
         * Message streams manager
         */
        IO::GSMessageStreamsManagerPtr _messageStreamsManager;
    };

    /**
     * Context ptr type
     */
    using GSContextPtr = std::unique_ptr<GS_Context>;

}

#endif //GSLANGUAGE_GS_CONTEXT_H
