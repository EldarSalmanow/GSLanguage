#include <args.hxx>

#include <IO/GS_MessageHandler.h>
#include <IO/GS_SourceManager.h>

#include <AST/GS_ASTContext.h>

#include <GS_CompilerSessionConfig.h>

namespace GSLanguageCompiler::Driver {

    GS_CompilerSessionConfig::GS_CompilerSessionConfig(UString outputFileName, std::shared_ptr<IO::GS_MessageHandler> messageHandler, std::shared_ptr<IO::GS_SourceManager> sourceManager, std::shared_ptr<AST::GS_ASTContext> astContext)
            : _outputFileName(std::move(outputFileName)),
              _messageHandler(std::move(messageHandler)),
              _sourceManager(std::move(sourceManager)),
              _astContext(std::move(astContext)) {}

    std::shared_ptr<GS_CompilerSessionConfig> GS_CompilerSessionConfig::Create(UString outputFileName, std::shared_ptr<IO::GS_MessageHandler> messageHandler, std::shared_ptr<IO::GS_SourceManager> sourceManager, std::shared_ptr<AST::GS_ASTContext> astContext) {
        return std::make_shared<GS_CompilerSessionConfig>(std::move(outputFileName), std::move(messageHandler), std::move(sourceManager), std::move(astContext));
    }

    std::shared_ptr<GS_CompilerSessionConfig> GS_CompilerSessionConfig::Create(UString outputFileName, std::shared_ptr<IO::GS_SourceManager> sourceManager) {
        return std::make_shared<GS_CompilerSessionConfig>(std::move(outputFileName), IO::GS_MessageHandler::Create(), std::move(sourceManager), AST::GS_ASTContext::Create());
    }

    std::shared_ptr<GS_CompilerSessionConfig> GS_CompilerSessionConfig::Create(I32 argc, Ptr<Ptr<C>> argv) {
        args::ArgumentParser parser("GSLanguageCompiler - Compiler for GSLanguage");
        args::HelpFlag helpFlag(parser, "help", "Display help description about GSLanguageCompiler", {'h', "help"});
        args::ValueFlag<std::string> inputFile(parser, "file", "File for compiling", {'f', "file"}, args::Options::Required);
        args::ValueFlag<std::string> outputFile(parser, "output", "Output file", {'o', "out"}, args::Options::Required);

        try {
            parser.ParseCLI(argc, argv);
        } catch (LRef<args::Help> help) {
            std::cout << parser.Help();

            return nullptr;
        } catch (LRef<args::Error> error) {
            std::cout << error.what() << std::endl << std::endl;

            std::cout << parser.Help();

            return nullptr;
        }

        UString outputFileName;

        auto sourceManager = IO::GS_SourceManager::Create();

        if (outputFile) {
            outputFileName = outputFile.Get();
        }

        if (inputFile) {
            auto sourceName = IO::GS_SourceName::CreateFile(inputFile.Get());

            auto source = IO::GS_Source::CreateFile(sourceName);

            sourceManager->AddSource(source);
        }

        return GS_CompilerSessionConfig::Create(outputFileName, sourceManager);
    }

    UString GS_CompilerSessionConfig::GetOutputFileName() const {
        return _outputFileName;
    }

    std::shared_ptr<IO::GS_MessageHandler> GS_CompilerSessionConfig::GetMessageHandler() const {
        return _messageHandler;
    }

    std::shared_ptr<IO::GS_SourceManager> GS_CompilerSessionConfig::GetSourceManager() const {
        return _sourceManager;
    }

    std::shared_ptr<AST::GS_ASTContext> GS_CompilerSessionConfig::GetASTContext() const {
        return _astContext;
    }

}
