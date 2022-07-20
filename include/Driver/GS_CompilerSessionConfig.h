#ifndef GSLANGUAGE_GS_COMPILERSESSIONCONFIG_H
#define GSLANGUAGE_GS_COMPILERSESSIONCONFIG_H

#include <vector>

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler {

    namespace IO {

        class GS_MessageHandler;

        class GS_SourceManager;

    }

    namespace AST {

        class GS_ASTContext;

    }

    namespace Driver {

        // TODO refactor writing compiling result system

        /**
         * Class for representation all session configs of compiler
         */
        class GS_CompilerSessionConfig {
        public:

            /**
             * Constructor for compiler session config
             * @param outputFileName Output file name for write compiling result
             * @param messageHandler Message handler for writing compiling process messages
             * @param sourceManager Source manager for containing sources for compiling
             * @param astContext AST context for parsing and analyzing source code
             */
            GS_CompilerSessionConfig(UString outputFileName, std::shared_ptr<IO::GS_MessageHandler> messageHandler, std::shared_ptr<IO::GS_SourceManager> sourceManager, std::shared_ptr<AST::GS_ASTContext> astContext);

        public:

            /**
             * Creating compiler session config
             * @param outputFileName Output file name
             * @param messageHandler Message handler
             * @param sourceManager Source manager
             * @param astContext AST context
             * @return Compiler session config ptr
             */
            static std::shared_ptr<GS_CompilerSessionConfig> Create(UString outputFileName, std::shared_ptr<IO::GS_MessageHandler> messageHandler, std::shared_ptr<IO::GS_SourceManager> sourceManager, std::shared_ptr<AST::GS_ASTContext> astContext);

            /**
             * Creating compiler session config
             * @param outputFileName Output file name
             * @param sourceManager Source manager
             * @return Compiler session config ptr
             */
            static std::shared_ptr<GS_CompilerSessionConfig> Create(UString outputFileName, std::shared_ptr<IO::GS_SourceManager> sourceManager);

            /**
             * Creating compiler config with parsing command line arguments
             * @param argc Arguments counter
             * @param argv Arguments value
             * @return Compiler config ptr
             */
            static std::shared_ptr<GS_CompilerSessionConfig> Create(I32 argc, Ptr<Ptr<C>> argv);

        public:

            /**
             * Getter for output file name
             * @return Output file name
             */
            UString GetOutputFileName() const;

            /**
             * Getter for message handler
             * @return Message handler
             */
            std::shared_ptr<IO::GS_MessageHandler> GetMessageHandler() const;

            /**
             * Getter for source manager
             * @return Source manager
             */
            std::shared_ptr<IO::GS_SourceManager> GetSourceManager() const;

            /**
             * Getter for AST context
             * @return AST context
             */
            std::shared_ptr<AST::GS_ASTContext> GetASTContext() const;

        private:

            /**
             * Output file name
             */
            UString _outputFileName;

            /**
             * Message handler
             */
            std::shared_ptr<IO::GS_MessageHandler> _messageHandler;

            /**
             * Source manager
             */
            std::shared_ptr<IO::GS_SourceManager> _sourceManager;

            /**
             * AST context
             */
            std::shared_ptr<AST::GS_ASTContext> _astContext;
        };

        /**
         * Compiler session config ptr type
         */
        using GSCompilerSessionConfigPtr = std::shared_ptr<GS_CompilerSessionConfig>;

        /**
         * Compiler session config ptr array type
         */
        using GSCompilerSessionConfigPtrArray = std::vector<GSCompilerSessionConfigPtr>;

    }

}

#endif //GSLANGUAGE_GS_COMPILERSESSIONCONFIG_H
