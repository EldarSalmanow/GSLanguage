#ifndef GSLANGUAGE_GS_COMPILERSESSIONCONFIG_H
#define GSLANGUAGE_GS_COMPILERSESSIONCONFIG_H

#include <filesystem>

#include <Driver/GS_TranslationUnitConfig.h>

namespace GSLanguageCompiler {

    namespace IO {

        class GS_MessageHandler;

    }

    namespace AST {

        class GS_ASTContext;

    }

    namespace Driver {

        class FileName {
        public:

            FileName(UString name, UString extension)
                    : _name(std::move(name)), _extension(std::move(extension)) {}

        public:

            static FileName Create(UString name, UString extension) {
                return FileName(std::move(name), std::move(extension));
            }

            static FileName Create(UString fileName) {
                UString name, extension;

                std::filesystem::path path(fileName.AsUTF8());

                name = path.stem().string();

                if (path.extension().empty()) {
                    // remove '.' from extension name
                    extension = path.extension().string().substr(1);
                }

                return FileName::Create(name, extension);
            }

        public:

            UString GetFileName() const {
                return _name + "." + _extension;
            }

            UString GetName() const {
                return _name;
            }

            UString GetExtension() const {
                return _extension;
            }

        private:

            UString _name;

            UString _extension;
        };

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

        class SessionConfig {
        public:

            SessionConfig(std::vector<FileName> inputFiles, FileName outputFile, std::shared_ptr<IO::GS_MessageHandler> messageHandler, std::shared_ptr<AST::GS_ASTContext> astContext)
                    : _inputFiles(std::move(inputFiles)), _outputFile(std::move(outputFile)), _messageHandler(std::move(messageHandler)), _astContext(std::move(astContext)) {}

        public:

            static std::shared_ptr<SessionConfig> Create(std::vector<FileName> inputFiles, FileName outputFile, std::shared_ptr<IO::GS_MessageHandler> messageHandler, std::shared_ptr<AST::GS_ASTContext> astContext) {
                return std::make_shared<SessionConfig>(std::move(inputFiles), std::move(outputFile), std::move(messageHandler), std::move(astContext));
            }

            static std::shared_ptr<SessionConfig> Create(std::vector<FileName> inputFiles, FileName outputFile, std::shared_ptr<IO::GS_MessageHandler> messageHandler) {
                return SessionConfig::Create(std::move(inputFiles), std::move(outputFile), std::move(messageHandler), AST::GS_ASTContext::Create());
            }

            static std::shared_ptr<SessionConfig> Create(std::vector<FileName> inputFiles, FileName outputFile, std::shared_ptr<AST::GS_ASTContext> astContext) {
                return SessionConfig::Create(std::move(inputFiles), std::move(outputFile), IO::GS_MessageHandler::Create(), std::move(astContext));
            }

            static std::shared_ptr<SessionConfig> Create(std::vector<FileName> inputFiles, FileName outputFile) {
                return SessionConfig::Create(std::move(inputFiles), std::move(outputFile), IO::GS_MessageHandler::Create(), AST::GS_ASTContext::Create());
            }

        private:

            std::vector<FileName> _inputFiles;

            FileName _outputFile;

            std::shared_ptr<IO::GS_MessageHandler> _messageHandler;

            std::shared_ptr<AST::GS_ASTContext> _astContext;
        };

    }

}

#endif //GSLANGUAGE_GS_COMPILERSESSIONCONFIG_H
