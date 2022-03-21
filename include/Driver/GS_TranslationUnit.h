#ifndef GSLANGUAGE_GS_TRANSLATIONUNIT_H
#define GSLANGUAGE_GS_TRANSLATIONUNIT_H

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for representation translation unit
     */
    class GS_TranslationUnit {
    public:

        /**
         * Constructor for translation unit
         * @param inputName Input name
         * @param outputName Output name
         */
        GS_TranslationUnit(UString inputName, UString outputName);

    public:

        /**
         * Creating translation unit
         * @param inputName Input name
         * @param outputName Output name
         * @return Translation unit ptr
         */
        static SharedPtr<GS_TranslationUnit> Create(UString inputName, UString outputName);

    public:

        /**
         * Compile translation unit
         * @return Compiling result
         */
        I32 Compile();

    public:

        /**
         * Getter for input file name
         * @return Input file name
         */
        UString GetInputName() const;

        /**
         * Getter for output file name
         * @return Output file name
         */
        UString GetOutputName() const;

    private:

        /**
         * Input file name
         */
        UString _inputName;

        /**
         * Output file name
         */
        UString _outputName;
    };

    /**
     * Translation unit ptr type
     */
    using GSTranslationUnitPtr = SharedPtr<GS_TranslationUnit>;

    /**
     * Translation unit ptr array type
     */
    using GSTranslationUnitPtrArray = Vector<GSTranslationUnitPtr>;

}

#endif //GSLANGUAGE_GS_TRANSLATIONUNIT_H
