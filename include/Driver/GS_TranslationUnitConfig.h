#ifndef GSLANGUAGE_GS_TRANSLATIONUNITCONFIG_H
#define GSLANGUAGE_GS_TRANSLATIONUNITCONFIG_H

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for representation translation unit configs
     */
    class GS_TranslationUnitConfig {
    public:

        /**
         * Constructor for translation unit config
         * @param inputName Input name
         * @param outputName Output name
         */
        GS_TranslationUnitConfig(UString inputName, UString outputName);

    public:

        /**
         * Creating translation unit config
         * @param inputName Input name
         * @param outputName Output name
         * @return Translation unit config ptr
         */
        static SharedPtr<GS_TranslationUnitConfig> Create(UString inputName, UString outputName);

        /**
         * Creating translation unit config
         * Output name is an input name with a different extension
         * @param inputName Input name
         * @return Translation unit config ptr
         */
        static SharedPtr<GS_TranslationUnitConfig> Create(UString inputName);

    public:

        /**
         * Getter for input name
         * @return Input name
         */
        UString GetInputName() const;

        /**
         * Getter for output name
         * @return Output name
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
     * Translation unit config ptr type
     */
    using GSTranslationUnitConfigPtr = SharedPtr<GS_TranslationUnitConfig>;

    /**
     * Translation unit config ptr array type
     */
    using GSTranslationUnitConfigPtrArray = Vector<GSTranslationUnitConfigPtr>;

}

#endif //GSLANGUAGE_GS_TRANSLATIONUNITCONFIG_H
