#ifndef GSLANGUAGE_GS_COMPILERSESSIONCONFIG_H
#define GSLANGUAGE_GS_COMPILERSESSIONCONFIG_H

#include <Driver/GS_TranslationUnitConfig.h>

namespace GSLanguageCompiler {

    namespace IO {

        class GS_MessageHandler;

    }

    namespace AST {

        class GS_ASTContext;

    }

    namespace Driver {

        /**
         * Class for representation all session configs of compiler
         */
        class GS_CompilerSessionConfig {
        public:

            /**
             * Constructor for compiler session config
             * @param unitConfigs Unit configs
             * @param outputName Output name
             * @param messageHandler Message handler
             * @param astContext AST context
             */
            GS_CompilerSessionConfig(GSTranslationUnitConfigPtrArray unitConfigs, UString outputName, std::shared_ptr<IO::GS_MessageHandler> messageHandler, std::shared_ptr<AST::GS_ASTContext> astContext);

        public:

            /**
             * Creating compiler config
             * @param unitConfigs Unit configs
             * @param outputName Output name
             * @param messageHandler Message handler
             * @param astContext AST context
             * @return Compiler config ptr
             */
            static std::shared_ptr<GS_CompilerSessionConfig> Create(GSTranslationUnitConfigPtrArray unitConfigs, UString outputName, std::shared_ptr<IO::GS_MessageHandler> messageHandler, std::shared_ptr<AST::GS_ASTContext> astContext);

            /**
             * Creating compiler config
             * @param unitConfigs Unit configs
             * @param outputName Output name
             * @return Compiler config ptr
             */
            static std::shared_ptr<GS_CompilerSessionConfig> Create(GSTranslationUnitConfigPtrArray unitConfigs, UString outputName);

            /**
             * Creating compiler config with parsing command line arguments
             * @param argc Arguments counter
             * @param argv Arguments value
             * @return Compiler config ptr
             */
            static std::shared_ptr<GS_CompilerSessionConfig> Create(I32 argc, Ptr<Ptr<C>> argv);

        public:

            /**
             * Getter for unit configs
             * @return Unit configs
             */
            GSTranslationUnitConfigPtrArray GetUnitConfigs() const;

            /**
             * Getter for output name
             * @return Output name
             */
            UString GetOutputName() const;

            /**
             * Getter for message handler
             * @return Message handler
             */
            std::shared_ptr<IO::GS_MessageHandler> GetMessageHandler() const;

            /**
             * Getter for AST context
             * @return AST context
             */
            std::shared_ptr<AST::GS_ASTContext> GetASTContext() const;

        private:

            /**
             * Unit configs
             */
            GSTranslationUnitConfigPtrArray _unitConfigs;

            /**
             * Output name
             */
            UString _outputName;

            /**
             * Message handler
             */
            std::shared_ptr<IO::GS_MessageHandler> _messageHandler;

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
