#ifndef GSLANGUAGE_GS_TRANSLATIONUNITSMANAGER_H
#define GSLANGUAGE_GS_TRANSLATIONUNITSMANAGER_H

#include <Driver/GS_TranslationUnit.h>

namespace GSLanguageCompiler::Driver {

    class GS_TranslationUnitsManager {
    public:

        explicit GS_TranslationUnitsManager(Vector<GS_TranslationUnit> files);

    public:

        I32 compileUnits();

    public:

        Vector<GS_TranslationUnit> getTranslationUnits();

    private:

        Vector<GS_TranslationUnit> _translationUnits;
    };

}

#endif //GSLANGUAGE_GS_TRANSLATIONUNITSMANAGER_H
