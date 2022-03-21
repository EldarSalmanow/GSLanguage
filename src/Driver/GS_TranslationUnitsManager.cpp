#include <future>

#include <GS_TranslationUnitsManager.h>

namespace GSLanguageCompiler::Driver {

    GS_TranslationUnitsManager::GS_TranslationUnitsManager(GSTranslationUnitPtrArray units)
            : _units(std::move(units)) {}

    SharedPtr<GS_TranslationUnitsManager> GS_TranslationUnitsManager::Create(GSTranslationUnitPtrArray units) {
        return std::make_shared<GS_TranslationUnitsManager>(std::move(units));
    }

    SharedPtr<GS_TranslationUnitsManager> GS_TranslationUnitsManager::Create() {
        return GS_TranslationUnitsManager::Create(GSTranslationUnitPtrArray());
    }

    I32 GS_TranslationUnitsManager::CompileUnits() {
        I32 returnCode = 0;

        for (auto &unit : _units) {
            if (unit->Compile()) {
                returnCode = 1;
            }
        }

        return returnCode;
    }

    Void GS_TranslationUnitsManager::AddUnit(GSTranslationUnitPtr unit) {
        _units.emplace_back(std::move(unit));
    }

    GSTranslationUnitPtrArray GS_TranslationUnitsManager::GetUnits() {
        return _units;
    }

}
