#include <GS_TranslationUnitConfig.h>

namespace GSLanguageCompiler::Driver {

    GS_TranslationUnitConfig::GS_TranslationUnitConfig(UString inputName, UString outputName)
            : _inputName(std::move(inputName)), _outputName(std::move(outputName)) {}

    SharedPtr<GS_TranslationUnitConfig> GS_TranslationUnitConfig::Create(UString inputName, UString outputName) {
        return std::make_shared<GS_TranslationUnitConfig>(std::move(inputName), std::move(outputName));
    }

    SharedPtr<GS_TranslationUnitConfig> GS_TranslationUnitConfig::Create(UString inputName) {
        auto outputName = inputName + U".o"_us;

        return GS_TranslationUnitConfig::Create(std::move(inputName), outputName);
    }

    UString GS_TranslationUnitConfig::GetInputName() const {
        return _inputName;
    }

    UString GS_TranslationUnitConfig::GetOutputName() const {
        return _outputName;
    }

}
