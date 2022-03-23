#include <args.hxx>

#include <GS_CompilerConfig.h>

namespace GSLanguageCompiler::Driver {

    GS_CompilerConfig::GS_CompilerConfig(GSTranslationUnitConfigPtrArray unitConfigs)
            : _unitConfigs(std::move(unitConfigs)) {}

    SharedPtr<GS_CompilerConfig> GS_CompilerConfig::Create(GSTranslationUnitConfigPtrArray unitConfigs) {
        return std::make_shared<GS_CompilerConfig>(std::move(unitConfigs));
    }

    SharedPtr<GS_CompilerConfig> GS_CompilerConfig::Create(I32 argc, Ptr<Ptr<C8>> argv) {
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
            GSTranslationUnitConfigPtr unitConfig;

            if (outputFile) {
                unitConfig = GS_TranslationUnitConfig::Create(inputFile.Get(), outputFile.Get());
            } else {
                unitConfig = GS_TranslationUnitConfig::Create(inputFile.Get());
            }

            unitConfigs.emplace_back(unitConfig);
        }

        auto compilerConfig = GS_CompilerConfig::Create(unitConfigs);

        return compilerConfig;
    }

    GSTranslationUnitConfigPtrArray GS_CompilerConfig::GetUnitConfigs() const {
        return _unitConfigs;
    }

}
