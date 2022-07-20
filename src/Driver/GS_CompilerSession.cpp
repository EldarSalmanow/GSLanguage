#include <IO/GS_SourceManager.h>

#include <GS_CompilerSession.h>

namespace GSLanguageCompiler::Driver {

    GS_CompilerSession::GS_CompilerSession(GSCompilerSessionConfigPtr compilerSessionConfig)
            : _config(std::move(compilerSessionConfig)) {}

    std::shared_ptr<GS_CompilerSession> GS_CompilerSession::Create(GSCompilerSessionConfigPtr compilerSessionConfig) {
        return std::make_shared<GS_CompilerSession>(std::move(compilerSessionConfig));
    }

    CompilingResult GS_CompilerSession::Run() {
        auto unitsManager = GS_TranslationUnitsManager::Create();

        auto SM = _config->GetSourceManager();

        for (auto &source : SM->GetSources()) {
            auto sourceHash = source->GetHash();

            auto unitConfig = GS_TranslationUnitConfig::Create(sourceHash, _config);

            auto unit = GS_TranslationUnit::Create(unitConfig);

            unitsManager->AddUnit(unit);
        }

        auto compilingResults = unitsManager->CompileUnits();

        for (auto &compilingResult : compilingResults) {
            if (compilingResult == CompilingResult::Failure) {
                return CompilingResult::Failure;
            }
        }

        // TODO enable in future

//        auto toolchain = GetDefaultToolchain();
//
//        auto linker = toolchain->GetLinker();
//
//        auto linkerResult = linker->Link(unitsManager->GetUnits(), _config->GetOutputFileName());
//
//        if (!linkerResult) {
//            return CompilingResult::Failure;
//        }

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
