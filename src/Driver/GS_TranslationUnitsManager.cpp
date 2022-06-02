#include <GS_TranslationUnitsManager.h>

namespace GSLanguageCompiler::Driver {

    GS_TranslationUnitsManager::GS_TranslationUnitsManager(GSTranslationUnitPtrArray units)
            : _units(std::move(units)) {}

    std::shared_ptr<GS_TranslationUnitsManager> GS_TranslationUnitsManager::Create(GSTranslationUnitPtrArray units) {
        return std::make_shared<GS_TranslationUnitsManager>(std::move(units));
    }

    std::shared_ptr<GS_TranslationUnitsManager> GS_TranslationUnitsManager::Create() {
        return GS_TranslationUnitsManager::Create(GSTranslationUnitPtrArray());
    }

    Vector<CompilingResult> GS_TranslationUnitsManager::CompileUnits() {
        Vector<CompilingResult> compilingResults;

        for (auto &unit : _units) {
            auto result = unit->Compile();

            compilingResults.emplace_back(result);
        }

        return compilingResults;
    }

    Void GS_TranslationUnitsManager::AddUnit(GSTranslationUnitPtr unit) {
        _units.emplace_back(std::move(unit));
    }

    GSTranslationUnitPtrArray GS_TranslationUnitsManager::GetUnits() const {
        return _units;
    }

}
