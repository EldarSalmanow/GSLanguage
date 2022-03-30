#include <args.hxx>

#include <GS_CompilerSessionConfig.h>

namespace GSLanguageCompiler::Driver {

    GS_CompilerSessionConfig::GS_CompilerSessionConfig(GSTranslationUnitConfigPtrArray unitConfigs)
            : _unitConfigs(std::move(unitConfigs)) {}

    SharedPtr<GS_CompilerSessionConfig> GS_CompilerSessionConfig::Create(GSTranslationUnitConfigPtrArray unitConfigs) {
        return std::make_shared<GS_CompilerSessionConfig>(std::move(unitConfigs));
    }

    SharedPtr<GS_CompilerSessionConfig> GS_CompilerSessionConfig::Create(I32 argc, Ptr<Ptr<C8>> argv) {
        args::ArgumentParser parser("GSLanguageCompiler - Compiler for GSLanguage");
        args::HelpFlag helpFlag(parser, "help", "Display help description about GSLanguageCompiler", {'h', "help"});
        args::ValueFlag<String> inputFile(parser, "file", "File for compiling", {'f', "file"}, args::Options::Required);
        args::ValueFlag<String> outputFile(parser, "output", "Output file", {'o', "out"});

        try {
            parser.ParseCLI(argc, argv);
        } catch (LRef<args::Help> help) {
            std::cout << parser;

            return nullptr;
        } catch (LRef<args::Error> error) {
            std::cout << error.what() << std::endl << std::endl;

            std::cout << parser;

            return nullptr;
        }

        GSTranslationUnitConfigPtrArray unitConfigs;

        if (inputFile) {
            auto unitConfig = GS_TranslationUnitConfig::Create(inputFile.Get());

            unitConfigs.emplace_back(unitConfig);
        }

        auto compilerConfig = GS_CompilerSessionConfig::Create(unitConfigs);

        return compilerConfig;
    }

    GSTranslationUnitConfigPtrArray GS_CompilerSessionConfig::GetUnitConfigs() const {
        return _unitConfigs;
    }

}
