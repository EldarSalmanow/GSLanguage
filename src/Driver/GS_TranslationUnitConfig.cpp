#include <GS_TranslationUnitConfig.h>

namespace GSLanguageCompiler::Driver {

    GS_TranslationUnitConfig::GS_TranslationUnitConfig(U64 sourceHash, GSCompilerSessionConfigPtr sessionConfig)
            : _sourceHash(sourceHash), _sessionConfig(std::move(sessionConfig)) {}

    std::shared_ptr<GS_TranslationUnitConfig> GS_TranslationUnitConfig::Create(U64 sourceHash, GSCompilerSessionConfigPtr sessionConfig) {
        return std::make_shared<GS_TranslationUnitConfig>(sourceHash, std::move(sessionConfig));
    }

    U64 GS_TranslationUnitConfig::GetSourceHash() const {
        return _sourceHash;
    }

    GSCompilerSessionConfigPtr GS_TranslationUnitConfig::GetSessionConfig() const {
        return _sessionConfig;
    }

}
