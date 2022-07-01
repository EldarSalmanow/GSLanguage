#include <args.hxx>

#include <IO/GS_MessageHandler.h>

#include <AST/GS_ASTContext.h>

#include <GS_CompilerSessionConfig.h>

namespace GSLanguageCompiler::Driver {

    GS_CompilerSessionConfig::GS_CompilerSessionConfig(GSTranslationUnitConfigPtrArray unitConfigs, UString outputName, std::shared_ptr<IO::GS_MessageHandler> messageHandler, std::shared_ptr<AST::GS_ASTContext> astContext)
            : _unitConfigs(std::move(unitConfigs)),
              _outputName(std::move(outputName)),
              _messageHandler(std::move(messageHandler)),
              _astContext(std::move(astContext)) {}

    std::shared_ptr<GS_CompilerSessionConfig> GS_CompilerSessionConfig::Create(GSTranslationUnitConfigPtrArray unitConfigs, UString outputName, std::shared_ptr<IO::GS_MessageHandler> messageHandler, std::shared_ptr<AST::GS_ASTContext> astContext) {
        return std::make_shared<GS_CompilerSessionConfig>(std::move(unitConfigs), std::move(outputName), std::move(messageHandler), std::move(astContext));
    }

    std::shared_ptr<GS_CompilerSessionConfig> GS_CompilerSessionConfig::Create(GSTranslationUnitConfigPtrArray unitConfigs, UString outputName) {
        return GS_CompilerSessionConfig::Create(std::move(unitConfigs), std::move(outputName), IO::GS_MessageHandler::Create(), AST::GS_ASTContext::Create());
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

        GSTranslationUnitConfigPtrArray unitConfigs;

        if (inputFile) {
            auto unitConfig = GS_TranslationUnitConfig::Create(inputFile.Get());

            unitConfigs.emplace_back(unitConfig);
        }

        UString outputName;

        if (outputFile) {
            outputName = outputFile.Get();
        }

        return GS_CompilerSessionConfig::Create(unitConfigs, outputName);
    }

    GSTranslationUnitConfigPtrArray GS_CompilerSessionConfig::GetUnitConfigs() const {
        return _unitConfigs;
    }

    UString GS_CompilerSessionConfig::GetOutputName() const {
        return _outputName;
    }

    std::shared_ptr<IO::GS_MessageHandler> GS_CompilerSessionConfig::GetMessageHandler() const {
        return _messageHandler;
    }

    std::shared_ptr<AST::GS_ASTContext> GS_CompilerSessionConfig::GetASTContext() const {
        return _astContext;
    }

    void f() {
        auto tuconf = GS_TranslationUnitConfig::Create("main.gs"_us);

        auto mh = IO::GS_MessageHandler::Create(IO::GS_OutFileStream::CreateOutFile("complogs.txt"));

        auto astctx = AST::GS_ASTContext::Create();

        auto sessconf = GS_CompilerSessionConfig::Create({ tuconf }, "main.exe"_us, mh, astctx);
    }

    // GSLanguage -f main.gs lib.gs -o main.exe

    /* main.gs
     *
     * import say_hello_module
     *
     * func main() {
     *     say_hello()
     * }
     *
     */

    /* lib.gs
     *
     *
     *
     */
}
