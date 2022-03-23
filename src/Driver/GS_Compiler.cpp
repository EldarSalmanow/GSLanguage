#include <GS_Compiler.h>

namespace GSLanguageCompiler::Driver {

    GS_Compiler::GS_Compiler(GSCompilerConfigPtr config)
            : _config(std::move(config)) {}

    SharedPtr<GS_Compiler> GS_Compiler::Create(GSCompilerConfigPtr config) {
        return std::make_shared<GS_Compiler>(std::move(config));
    }

    I32 GS_Compiler::Start(I32 argc, Ptr<Ptr<C8>> argv) {
        auto compilerConfig = GS_CompilerConfig::Create(argc, argv);

        if (!compilerConfig) {
            return 1;
        }

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
