#ifndef GSLANGUAGE_GS_TRANSLATIONUNIT_H
#define GSLANGUAGE_GS_TRANSLATIONUNIT_H

#include <Driver/GS_TranslationUnitConfig.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Compiling result
     */
    enum class CompilingResult {
        Success,
        Failure
    };

    /**
     * Class for representation translation unit
     */
    class GS_TranslationUnit {
    public:

        /**
         * Constructor for translation unit
         * @param config Unit config
         */
        explicit GS_TranslationUnit(GSTranslationUnitConfigPtr config);

    public:

        /**
         * Creating translation unit
         * @param config Unit config
         * @return Translation unit ptr
         */
        static std::shared_ptr<GS_TranslationUnit> Create(GSTranslationUnitConfigPtr config);

    public:

        /**
         * Compile translation unit
         * @return Compiling result
         */
        CompilingResult Compile();

    public:

        /**
         * Getter for config
         * @return Config
         */
        GSTranslationUnitConfigPtr GetConfig() const;

    private:

        /**
         * Unit config
         */
        GSTranslationUnitConfigPtr _config;
    };

    /**
     * Translation unit ptr type
     */
    using GSTranslationUnitPtr = std::shared_ptr<GS_TranslationUnit>;

    /**
     * Translation unit ptr array type
     */
    using GSTranslationUnitPtrArray = std::vector<GSTranslationUnitPtr>;

}

#endif //GSLANGUAGE_GS_TRANSLATIONUNIT_H
