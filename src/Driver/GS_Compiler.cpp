#include <args.hxx>

#include <GS_Compiler.h>

namespace GSLanguageCompiler::Driver {

    GS_Compiler::GS_Compiler(GSCompilerConfigPtr config)
            : _config(std::move(config)) {}

    SharedPtr<GS_Compiler> GS_Compiler::Create(GSCompilerConfigPtr config) {
        return std::make_shared<GS_Compiler>(std::move(config));
    }

    I32 GS_Compiler::Start(I32 argc, Ptr<Ptr<C8>> argv) {
        // TODO beautify arguments parsing and update it

        args::ArgumentParser parser("GSLanguageCompiler - Compiler for GSLanguage");
        args::HelpFlag helpFlag(parser, "help", "Display help description about GSLanguageCompiler", {'h', "help"});
        args::ValueFlag<String> inputFile(parser, "file", "File for compiling", {'f', "file"}, args::Options::Required);
        args::ValueFlag<String> outputFile(parser, "output", "Output file", {'o', "out"});

        try {
            parser.ParseCLI(argc, argv);
        } catch (args::Help &help) {
            std::cout << parser;

            return 0;
        } catch (args::Error &error) {
            std::cout << error.what() << std::endl;

            std::cout << parser;

            return 1;
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

        auto compiler = GS_Compiler::Create(compilerConfig);

        return compiler->Run();
    }

    I32 GS_Compiler::Run() {
        auto unitConfigs = _config->GetUnitConfigs();

        auto unitsManager = GS_TranslationUnitsManager::Create();

        for (auto &unitConfig : unitConfigs) {
            auto unit = GS_TranslationUnit::Create(unitConfig);

            unitsManager->AddUnit(unit);
        }

        auto result = unitsManager->CompileUnits();

        return result;
    }

    GSCompilerConfigPtr GS_Compiler::GetConfig() const {
        return _config;
    }

}
