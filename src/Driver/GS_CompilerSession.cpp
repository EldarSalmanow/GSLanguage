#include <GS_CompilerSession.h>

namespace GSLanguageCompiler::Driver {

    GS_CompilerSession::GS_CompilerSession(GSCompilerSessionConfigPtr compilerSessionConfig)
            : _config(std::move(compilerSessionConfig)) {}

    SharedPtr<GS_CompilerSession> GS_CompilerSession::Create(GSCompilerSessionConfigPtr compilerSessionConfig) {
        return std::make_shared<GS_CompilerSession>(std::move(compilerSessionConfig));
    }

    CompilingResult GS_CompilerSession::Run() {
        auto unitConfigs = _config->GetUnitConfigs();

        auto unitsManager = GS_TranslationUnitsManager::Create();

        for (auto &unitConfig : unitConfigs) {
            auto unit = GS_TranslationUnit::Create(unitConfig);

            unitsManager->AddUnit(unit);
        }

        auto compilingResults = unitsManager->CompileUnits();

        for (auto &compilingResult : compilingResults) {
            if (compilingResult == CompilingResult::Failure) {
                return CompilingResult::Failure;
            }
        }

        auto toolchain = GetDefaultToolchain();

        auto linker = toolchain->GetLinker();

        auto linkerResult = linker->Link(unitsManager->GetUnits(), _config->GetOutputName());

        if (!linkerResult) {
            return CompilingResult::Failure;
        }

        return CompilingResult::Success;
    }

    GSToolchainPtr GS_CompilerSession::GetDefaultToolchain() {
#if defined(GS_OS_WINDOWS)
      
        return std::make_shared<GS_MSVCToolchain>();
      
#else
     
        return nullptr;
        
#endif
    }
    
    GSCompilerSessionConfigPtr GS_CompilerSession::GetConfig() const {
        return _config;
    }

}
