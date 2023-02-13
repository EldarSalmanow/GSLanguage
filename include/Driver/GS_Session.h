#ifndef GSLANGUAGE_GS_SESSION_H
#define GSLANGUAGE_GS_SESSION_H

#include <IO/IO.h>

#include <AST/AST.h>

#include <Driver/GS_Arguments.h>

namespace GSLanguageCompiler {

    namespace Semantic {

        /**
         * Declaring table of symbols for compiler session
         */
        class GS_TableOfSymbols;

        /**
         * Declaring table of symbols ptr type for compiler session
         */
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
         * Converting compiling result to result
         * @param compilingResult Compiling result
         * @return Result
         */
        Result ToResult(CompilingResult compilingResult);

        /**
         * Converting compiling result to exit code
         * @param compilingResult Compiling result
         * @return Exit code
         */
        I32 ToExitCode(CompilingResult compilingResult);

        /**
         * Class for creating one compilation unit (one output file) and controlling compilation process
         */
        class GS_Session {
        public:

            /*
             *
             * GS_Session PUBLIC CONSTRUCTORS
             *
             */

            /**
             * Constructor for compiler session
             * @param stdIOStreamsManager Standard IO streams manager
             * @param sourceManager Source manager
             * @param messageStreamsManager Message streams manager
             * @param astContext AST context
             * @param tableOfSymbols Table of symbols
             */
            GS_Session(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                       IO::GSSourceManagerPtr sourceManager,
                       IO::GSMessageStreamsManagerPtr messageStreamsManager,
                       AST::GSASTContextPtr astContext,
                       Semantic::GSTableOfSymbolsPtr tableOfSymbols);

        public:

            /*
             *
             * GS_Session PUBLIC STATIC CREATE METHODS
             * TODO Add Create methods
             *
             */

            /**
             * Creating compiler session
             * @param stdIOStreamsManager Standard IO streams manager
             * @param sourceManager Source manager
             * @param messageStreamsManager Message streams manager
             * @param astContext AST context
             * @param tableOfSymbols Table of symbols
             * @return Compiler session ptr
             */
            static std::unique_ptr<GS_Session> Create(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                                                      IO::GSSourceManagerPtr sourceManager,
                                                      IO::GSMessageStreamsManagerPtr messageStreamsManager,
                                                      AST::GSASTContextPtr astContext,
                                                      Semantic::GSTableOfSymbolsPtr tableOfSymbols);

            /**
             * Creating compiler session
             * @return Compiler session ptr
             */
            static std::unique_ptr<GS_Session> Create();

            /**
             * Creating compiler session on arguments
             * @return Compiler session ptr
             * @todo Use output file name
             */
            static std::unique_ptr<GS_Session> Create(GS_Arguments arguments);

        public:

            /*
             *
             * GS_Session PUBLIC METHODS
             *
             */

            /**
             * Run compiler session
             * @return Compiling result
             * @todo Update
             */
            CompilingResult Run();

            /**
             * Getting standard input stream from standard IO streams manager for reading data from stream
             * @return Standard input stream
             */
            LRef<std::istream> StdIn();

            /**
             * Getting standard output stream from standard IO streams manager for writing data in stream
             * @return Standard output stream
             */
            LRef<std::ostream> StdOut();

            /**
             * Getting standard error stream from standard IO streams manager for writing data in stream
             * @return Standard error stream
             */
            LRef<std::ostream> StdErr();

            /**
             * Getting standard logger stream from standard IO streams manager for writing data in stream
             * @return Standard logger stream
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
             * Getter for sources from source manager
             * @return Sources
             */
            ConstLRef<IO::GSSourcePtrArray> GetSources() const;

            /**
             * Getting output message stream from message streams manager for writing message in stream
             * @return Output message stream
             */
            LRef<IO::GS_MessageStream> Out();

            /**
             * Getting error message stream from message streams manager for writing message in stream
             * @return Error message stream
             */
            LRef<IO::GS_MessageStream> Err();

            /**
             * Getting logger message stream from message streams manager for writing message in stream
             * @return Logger message stream
             */
            LRef<IO::GS_MessageStream> Log();

            /**
             * Creating message builder for creating message
             * @param messageText Message text
             * @param messageLevel Message level
             * @param messageLocationRange Optional message byte source location range
             * @return Message builder
             */
            IO::GS_MessageBuilder Message(UString messageText,
                                          IO::MessageLevel messageLevel,
                                          std::optional<IO::GSByteSourceRange> messageLocationRange) const;

            /**
             * Creating message builder for creating message
             * @param messageText Message text
             * @param messageLevel Message level
             * @param messageLocationRange Message byte source location range
             * @return Message builder
             */
            IO::GS_MessageBuilder Message(UString messageText,
                                          IO::MessageLevel messageLevel,
                                          IO::GSByteSourceRange messageLocationRange) const;

            /**
             * Creating message builder for creating message
             * @param messageText Message text
             * @param messageLevel Message level
             * @param messageSourceLocation Message byte source location [sourceLocation, sourceLocation + 1) (one symbol)
             * @return Message builder
             */
            IO::GS_MessageBuilder Message(UString messageText,
                                          IO::MessageLevel messageLevel,
                                          IO::GS_ByteSourceLocation messageSourceLocation) const;

            /**
             * Creating message builder for creating message
             * @param messageText Message text
             * @param messageLevel Message level
             * @return Message builder
             */
            IO::GS_MessageBuilder Message(UString messageText,
                                          IO::MessageLevel messageLevel) const;

            /**
             * Creating message builder for creating message
             * @return Message builder
             */
            IO::GS_MessageBuilder Message() const;

            // TODO Add new message Create or printing message methods ?

            /**
             * Creating message builder for creating 'note' message
             * @return Message builder
             */
            IO::GS_MessageBuilder NoteMessage() const;

            /**
             * Creating message builder for creating 'warning' message
             * @return Message builder
             */
            IO::GS_MessageBuilder WarningMessage() const;

            /**
             * Creating message builder for creating 'error' message
             * @return Message builder
             */
            IO::GS_MessageBuilder ErrorMessage() const;

            /**
             * Creating message builder for creating 'fatal' message
             * @return Message builder
             */
            IO::GS_MessageBuilder FatalMessage() const;

        public:

            /*
             *
             * GS_Session PUBLIC GETTERS
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

            /*
             *
             * GS_Session PRIVATE FIELDS
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
