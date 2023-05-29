#ifndef GSLANGUAGE_GS_SESSION_H
#define GSLANGUAGE_GS_SESSION_H

#include <IO/IO.h>

#include <AST/AST.h>

#include <Semantic/Semantic.h>

#include <Driver/GS_Arguments.h>

namespace GSLanguageCompiler {

    namespace CodeGenerator {

        /**
         * Defining code generation backend for compiler session
         */
        class GS_CGBackend;

        /**
         * Defining code generation backend ptr type for compiler session
         */
        using GSCGBackendPtr = std::shared_ptr<GS_CGBackend>;

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
             * @param stdIOStreamManager Standard IO stream manager
             * @param sourceManager Source manager
             * @param messageStreamManager Message stream manager
             * @param astContext AST context
             * @param tableOfSymbols Table of symbols
             * @param cgBackend Code generation backend
             */
            GS_Session(IO::GSStdIOStreamManagerPtr stdIOStreamManager,
                       IO::GSSourceManagerPtr sourceManager,
                       IO::GSMessageStreamManagerPtr messageStreamManager,
                       AST::GSASTContextPtr astContext,
                       Semantic::GSTableOfSymbolsPtr tableOfSymbols,
                       CodeGenerator::GSCGBackendPtr cgBackend);

        public:

            /*
             * TODO: Add Create methods
             */

            /*
             *
             * GS_Session PUBLIC STATIC CREATE METHODS
             *
             */

            /**
             * Creating compiler session
             * @param stdIOStreamManager Standard IO stream manager
             * @param sourceManager Source manager
             * @param messageStreamManager Message stream manager
             * @param astContext AST context
             * @param tableOfSymbols Table of symbols
             * @param cgBackend Code generation backend
             * @return Compiler session ptr
             */
            static std::unique_ptr<GS_Session> Create(IO::GSStdIOStreamManagerPtr stdIOStreamManager,
                                                      IO::GSSourceManagerPtr sourceManager,
                                                      IO::GSMessageStreamManagerPtr messageStreamManager,
                                                      AST::GSASTContextPtr astContext,
                                                      Semantic::GSTableOfSymbolsPtr tableOfSymbols,
                                                      CodeGenerator::GSCGBackendPtr cgBackend);

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
             * Getting standard input stream
             * @return Standard input stream
             */
            LRef<std::istream> StdIn();

            /**
             * Getting standard output stream
             * @return Standard output stream
             */
            LRef<std::ostream> StdOut();

            /**
             * Getting standard error stream
             * @return Standard error stream
             */
            LRef<std::ostream> StdErr();

            /**
             * Getting standard logger stream
             * @return Standard logger stream
             */
            LRef<std::ostream> StdLog();

            /**
             * Adding source
             * @param source Source
             * @return Source
             */
            ConstLRef<IO::GS_Source> AddSource(IO::GSSourcePtr source);

            /**
             * Adding file source
             * @param name File name
             * @return File source
             */
            ConstLRef<IO::GS_Source> AddFileSource(UString name);

            /**
             * Adding string source
             * @param source Source code
             * @return String source
             */
            ConstLRef<IO::GS_Source> AddStringSource(UString source);

            /**
             * Adding custom source
             * @param source Source code
             * @param name Source name
             * @return Custom source
             */
            ConstLRef<IO::GS_Source> AddCustomSource(UString source,
                                                     UString name);

            /**
             * Getting source by source hash
             * @param sourceHash Source hash
             * @return Source or null
             */
            std::optional<IO::GS_Source> GetSource(U64 sourceHash) const;

            /**
             * Getting source by source name
             * @param sourceName Source name
             * @return Source or null
             */
            std::optional<IO::GS_Source> GetSource(IO::GS_SourceName sourceName) const;

            /**
             * Getting file source by file name
             * @param fileName File name
             * @return File source or null
             */
            std::optional<IO::GS_Source> GetFileSource(UString fileName) const;

            /**
             * Getting custom source by source name
             * @return Custom source or null
             */
            std::optional<IO::GS_Source> GetCustomSource(UString sourceName) const;

            /**
             * Getter for sources
             * @return Sources
             */
            ConstLRef<IO::GSSourcePtrArray> GetSources() const;

            /**
             * Getting output message stream
             * @return Output message stream
             */
            LRef<IO::GS_MessageStream> Out();

            /**
             * Getting error message stream
             * @return Error message stream
             */
            LRef<IO::GS_MessageStream> Err();

            /**
             * Getting logger message stream
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

            /*
             * TODO: Add new message Create or printing message methods?
             */

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
             * GS_Session PUBLIC GETTER METHODS
             *
             */

            /**
             * Getter for standard IO stream manager
             * @return Standard IO stream manager
             */
            LRef<IO::GS_StdIOStreamManager> GetStdIOStreamManager();

            /**
             * Getter for source manager
             * @return Source manager
             */
            LRef<IO::GS_SourceManager> GetSourceManager();

            /**
             * Getter for message stream manager
             * @return Message stream manager
             */
            LRef<IO::GS_MessageStreamManager> GetMessageStreamManager();

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

            /**
             * Getter for code generation backend
             * @return Code generation backend
             */
            LRef<CodeGenerator::GSCGBackendPtr> GetCGBackend();

        private:

            /*
             *
             * GS_Session PRIVATE FIELDS
             *
             */

            /**
             * Standard IO stream manager
             */
            IO::GSStdIOStreamManagerPtr _stdIOStreamManager;

            /**
             * Source manager
             */
            IO::GSSourceManagerPtr _sourceManager;

            /**
             * Message stream manager
             */
            IO::GSMessageStreamManagerPtr _messageStreamManager;

            /**
             * AST context
             */
            AST::GSASTContextPtr _astContext;

            /**
             * Table of symbols
             */
            Semantic::GSTableOfSymbolsPtr _tableOfSymbols;

            /**
             * Code generation backend
             */
            CodeGenerator::GSCGBackendPtr _cgBackend;
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
