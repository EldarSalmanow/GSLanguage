#ifndef GSLANGUAGE_GS_CONTEXT_H
#define GSLANGUAGE_GS_CONTEXT_H

#include <AST/AST.h>

#include <Driver/GS_Arguments.h>

#include <Driver/GS_GlobalContext.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for containing and manipulating constantly information about compiling process
     */
    class GS_Context {
    public:

        /**
         * Creating context
         * @param stdIOStreamsManager Standard IO streams manager
         * @param sourceManager Source manager
         * @param messageRenderer Message renderer
         */
        GS_Context(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                   IO::GSSourceManagerPtr sourceManager,
                   IO::GSMessageRendererPtr messageRenderer);

    public:

        /**
         * Creating context
         * @param stdIOStreamsManager Standard IO streams manager
         * @param sourceManager Source manager
         * @param messageRenderer Message renderer
         * @return Context ptr
         */
        static std::unique_ptr<GS_Context> Create(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                                                  IO::GSSourceManagerPtr sourceManager,
                                                  IO::GSMessageRendererPtr messageRenderer);

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

    public:

        /**
         * Creating context from arguments
         * @param arguments Arguments
         * @return Context ptr
         */
        static std::unique_ptr<GS_Context> Create(GS_Arguments arguments);

    public:

        /**
         * Getting standard input stream from standard IO streams manager for reading data from stream
         * @return Standard input stream
         */
        LRef<std::istream> In();

        /**
         * Getting standard output stream from standard IO streams manager for writing data to stream
         * @return Standard output stream
         */
        LRef<std::ostream> Out();

        /**
         * Getting standard error stream from standard IO streams manager for writing data to stream
         * @return Standard error stream
         */
        LRef<std::ostream> Err();

        /**
         * Getting standard logging stream from standard IO streams manager for writing data to stream
         * @return Standard logging stream
         */
        LRef<std::ostream> Log();

    public:

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
         * Getter for sources from source manager
         * @return Sources
         */
        ConstLRef<IO::GSSourcePtrArray> GetSources() const;

    public:

        /**
         * Render message to message handler
         * @param message Message
         * @return
         */
        Void Render(IO::GS_Message message);

    public:

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
         * Getter for message renderer
         * @return Message renderer
         */
        LRef<IO::GS_MessageRenderer> GetMessageRenderer();

        LRef<IO::GS_MessageBuilder> CreateError();

    private:

        /**
         * Standard IO streams manager
         */
        IO::GSStdIOStreamsManagerPtr _stdIOStreamsManager;

        /**
         * Source manager
         */
        IO::GSSourceManagerPtr _sourceManager;

        /**
         * Message renderer
         */
        IO::GSMessageRendererPtr _messageRenderer;
    };

    /**
     * Context ptr type
     */
    using GSContextPtr = std::unique_ptr<GS_Context>;

}

#endif //GSLANGUAGE_GS_CONTEXT_H
