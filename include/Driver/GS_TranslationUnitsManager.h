#ifndef GSLANGUAGE_GS_TRANSLATIONUNITSMANAGER_H
#define GSLANGUAGE_GS_TRANSLATIONUNITSMANAGER_H

#include <Driver/GS_TranslationUnit.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for managing translation units
     */
    class GS_TranslationUnitsManager {
    public:

        /**
         * Constructor for translation units manager
         * @param units Translation unit ptrs
         */
        explicit GS_TranslationUnitsManager(GSTranslationUnitPtrArray units);

    public:

        /**
         * Creating translation units manager
         * @param units Translation unit ptrs
         * @return Translation unit ptrs
         */
        static SharedPtr<GS_TranslationUnitsManager> Create(GSTranslationUnitPtrArray units);

        /**
         * Creating translation units manager
         * @return Translation unit ptrs
         */
        static SharedPtr<GS_TranslationUnitsManager> Create();

    public:

        /**
         * Compile all units
         * @return Compiling result
         */
        I32 CompileUnits();

        /**
         * Adding translation unit
         * @param unit Translation unit ptr
         * @return
         */
        Void AddUnit(GSTranslationUnitPtr unit);

    public:

        /**
         * Getter for translation unit ptrs
         * @return Translation unit ptrs
         */
        GSTranslationUnitPtrArray GetUnits();

    private:

        /**
         * Translation unit ptrs
         */
        GSTranslationUnitPtrArray _units;
    };

}

#endif //GSLANGUAGE_GS_TRANSLATIONUNITSMANAGER_H
