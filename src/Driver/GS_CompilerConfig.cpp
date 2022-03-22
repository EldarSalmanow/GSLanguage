#include <GS_CompilerConfig.h>

namespace GSLanguageCompiler::Driver {

    GS_CompilerConfig::GS_CompilerConfig(GSTranslationUnitConfigPtrArray unitConfigs)
            : _unitConfigs(std::move(unitConfigs)) {}

    SharedPtr<GS_CompilerConfig> GS_CompilerConfig::Create(GSTranslationUnitConfigPtrArray unitConfigs) {
        return std::make_shared<GS_CompilerConfig>(std::move(unitConfigs));
    }

    GSTranslationUnitConfigPtrArray GS_CompilerConfig::GetUnitConfigs() const {
        return _unitConfigs;
    }

}
