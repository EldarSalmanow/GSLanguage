#include <future>

#include <GS_TranslationUnitsManager.h>

namespace GSLanguageCompiler::Driver {

    GS_TranslationUnitsManager::GS_TranslationUnitsManager(Vector<GS_TranslationUnit> translationUnits)
            : _translationUnits(std::move(translationUnits)) {}

    I32 GS_TranslationUnitsManager::compileUnits() {
        I32 returnCode = 0;

        for (auto &unit : _translationUnits) {
            if (unit.compile()) {
                returnCode = 1;
            }
        }

        return returnCode;
    }

    Vector<GS_TranslationUnit> GS_TranslationUnitsManager::getTranslationUnits() {
        return _translationUnits;
    }

}
