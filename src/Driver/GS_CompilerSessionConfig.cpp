#include <args.hxx>

#include <GS_CompilerSessionConfig.h>

namespace GSLanguageCompiler::Driver {

    GS_CompilerSessionConfig::GS_CompilerSessionConfig(GSTranslationUnitConfigPtrArray unitConfigs, UString outputName)
            : _unitConfigs(std::move(unitConfigs)), _outputName(std::move(outputName)) {}

    std::shared_ptr<GS_CompilerSessionConfig> GS_CompilerSessionConfig::Create(GSTranslationUnitConfigPtrArray unitConfigs, UString outputName) {
        return std::make_shared<GS_CompilerSessionConfig>(std::move(unitConfigs), std::move(outputName));
    }

    std::shared_ptr<GS_CompilerSessionConfig> GS_CompilerSessionConfig::Create(I32 argc, Ptr<Ptr<C>> argv) {
        args::ArgumentParser parser("GSLanguageCompiler - Compiler for GSLanguage");
        args::HelpFlag helpFlag(parser, "help", "Display help description about GSLanguageCompiler", {'h', "help"});
        args::ValueFlag<String> inputFile(parser, "file", "File for compiling", {'f', "file"}, args::Options::Required);
        args::ValueFlag<String> outputFile(parser, "output", "Output file", {'o', "out"}, args::Options::Required);

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

}
