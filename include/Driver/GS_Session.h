#ifndef GSLANGUAGE_GS_SESSION_H
#define GSLANGUAGE_GS_SESSION_H

#include <Driver/GS_Context.h>

namespace GSLanguageCompiler {

    namespace Semantic {

        class GS_TableOfSymbols;

        using GSTableOfSymbolsPtr = std::shared_ptr<GS_TableOfSymbols>;

    }

    namespace Driver {

        /**
         * Result of compiling
         */
        enum class CompilingResult : I32 {
            Success = 0,
            Failure = 1
        };

        /**
         * Class for representation compiler sessions
         */
        class GS_Session {
        public:

            /**
             * Constructor for compiler session
             * @param context Context
             */
            explicit GS_Session(GSContextPtr context);

        public:

            /**
             * Creating compiler session
             * @param context Context
             * @return Compiler session ptr
             */
            static std::unique_ptr<GS_Session> Create(GSContextPtr context);

            /**
             * Creating compiler session
             * @return Compiler session ptr
             */
            static std::unique_ptr<GS_Session> Create();

        public:

            /**
             * Run compiler session
             * @return Compiling result
             */
            CompilingResult Run();

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
             * @return Source or nullopt
             */
            std::optional<IO::GS_Source> GetSource(U64 sourceHash) const;

            /**
             * Get source from source manager by source name
             * @param sourceName Source name
             * @return Source or nullopt
             */
            std::optional<IO::GS_Source> GetSource(IO::GS_SourceName sourceName) const;

            /**
             * Get file source from source manager by file name
             * @param fileName File name
             * @return File source or nullopt
             */
            std::optional<IO::GS_Source> GetFileSource(UString fileName) const;

            /**
             * Get custom source from source manager by source name
             * @return Custom source or nullopt
             */
            std::optional<IO::GS_Source> GetCustomSource(UString sourceName) const;

            /**
             * Getter for sources from source manager
             * @return Sources
             */
            ConstLRef<IO::GSSourcePtrArray> GetSources() const;

        public:

            /**
             * Writing message to message handler
             * @param message Message
             * @return
             */
            Void Write(IO::GS_Message message);

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
             * Getter for message handler
             * @return Message handler
             */
            LRef<IO::GS_MessageHandler> GetMessageHandler();

        public:

            /**
             * Getter for context
             * @return Context
             */
            LRef<GS_Context> GetContext();

            /**
             * Getter for AST context
             * @return AST context
             */
            LRef<AST::GS_ASTContext> GetASTContext();

            /**
             * Getter for table of symbols
             * @return Table of symbols
             */
            LRef<Semantic::GS_TableOfSymbols> GetTableOfSymbols();

        private:

            /**
             * Context
             */
            GSContextPtr _context;

            /**
             * AST context
             */
            AST::GSASTContextPtr _astContext;

            /**
             * Table of symbols
             */
            Semantic::GSTableOfSymbolsPtr _tableOfSymbols;
        };

        /**
         * Session ptr type
         */
        using GSSessionPtr = std::unique_ptr<GS_Session>;

        /**
         * Session ptr array type
         */
        using GSSessionPtrArray = std::vector<GSSessionPtr>;

    }

}

#endif //GSLANGUAGE_GS_SESSION_H
