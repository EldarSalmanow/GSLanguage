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
            static std::shared_ptr<GS_Session> Create(GSContextPtr context);

            /**
             * Creating compiler session
             * @return Compiler session ptr
             */
            static std::shared_ptr<GS_Session> Create();

        public:

            /**
             * Run compiler session
             * @return Compiling result
             */
            CompilingResult Run();

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
            ConstLRef<IO::GS_Source> AddSource(IO::GSSourcePtr source);

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

            /**
             * Writing message to message handler
             * @param message Message
             * @return
             */
            Void Write(IO::GSMessagePtr message);

        public:

            /**
             * Getter for standard IO streams manager
             * @return Standard IO streams manager
             */
            IO::GSStdIOStreamsManagerPtr GetStdIOStreamsManager() const;

            /**
             * Getter for source manager
             * @return Source manager
             */
            IO::GSSourceManagerPtr GetSourceManager() const;

            /**
             * Getter for message handler
             * @return Message handler
             */
            IO::GSMessageHandlerPtr GetMessageHandler() const;

        public:

            /**
             * Getter for context
             * @return Context
             */
            GSContextPtr GetContext() const;

            /**
             * Getter for AST context
             * @return AST context
             */
            AST::GSASTContextPtr GetASTContext() const;

            /**
             * Getter for table of symbols
             * @return Table of symbols
             */
            Semantic::GSTableOfSymbolsPtr GetTableOfSymbols() const;

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
        using GSSessionPtr = std::shared_ptr<GS_Session>;

        /**
         * Session ptr array type
         */
        using GSSessionPtrArray = std::vector<GSSessionPtr>;

    }

}

#endif //GSLANGUAGE_GS_SESSION_H
