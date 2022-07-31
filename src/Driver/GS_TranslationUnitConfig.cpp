#include <GS_TranslationUnitConfig.h>

namespace GSLanguageCompiler::Driver {

    GS_TranslationUnitConfig::GS_TranslationUnitConfig(U64 sourceHash, GSSessionContextPtr sessionContext)
            : _sourceHash(sourceHash), _sessionContext(std::move(sessionContext)) {}

    std::shared_ptr<GS_TranslationUnitConfig> GS_TranslationUnitConfig::Create(U64 sourceHash, GSSessionContextPtr sessionContext) {
        return std::make_shared<GS_TranslationUnitConfig>(sourceHash, std::move(sessionContext));
    }

    U64 GS_TranslationUnitConfig::GetSourceHash() const {
        return _sourceHash;
    }

    GSSessionContextPtr GS_TranslationUnitConfig::GetSessionContext() const {
        return _sessionContext;
    }

}
