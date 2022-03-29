#include <GS_TranslationUnitConfig.h>

namespace GSLanguageCompiler::Driver {

    GS_TranslationUnitConfig::GS_TranslationUnitConfig(UString inputName)
            : _inputName(std::move(inputName)) {}

    SharedPtr<GS_TranslationUnitConfig> GS_TranslationUnitConfig::Create(UString inputName) {
        return std::make_shared<GS_TranslationUnitConfig>(std::move(inputName));
    }

    UString GS_TranslationUnitConfig::GetInputName() const {
        return _inputName;
    }

}
