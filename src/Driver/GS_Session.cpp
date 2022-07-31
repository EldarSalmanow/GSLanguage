#include <IO/IO.h>

#include <GS_Session.h>

namespace GSLanguageCompiler::Driver {

    GS_Session::GS_Session(GSSessionContextPtr sessionContext)
            : _sessionContext(std::move(sessionContext)) {}

    std::shared_ptr<GS_Session> GS_Session::Create(GSSessionContextPtr sessionContext) {
        return std::make_shared<GS_Session>(std::move(sessionContext));
    }

    CompilingResult GS_Session::Run() {
        auto unitsManager = Driver::GS_TranslationUnitsManager::Create();

        for (auto &source : _sessionContext->GetIOContext()->GetInputSources()) {
            auto unitConfig = Driver::GS_TranslationUnitConfig::Create(source->GetHash(), _sessionContext);

            auto unit = Driver::GS_TranslationUnit::Create(unitConfig);

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

    GSToolchainPtr GS_Session::GetDefaultToolchain() {
#if defined(GS_OS_WINDOWS)

        return std::make_shared<GS_MSVCToolchain>();
      
#else
     
        return nullptr;
        
#endif
    }
    
    GSSessionContextPtr GS_Session::GetSessionContext() const {
        return _sessionContext;
    }

}
