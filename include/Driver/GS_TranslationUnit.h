#ifndef GSLANGUAGE_GS_TRANSLATIONUNIT_H
#define GSLANGUAGE_GS_TRANSLATIONUNIT_H

#include <Driver/GS_TranslationUnitConfig.h>

namespace GSLanguageCompiler {

    namespace AST {

        /**
         * Declaring translation unit declaration node
         */
        class GS_TranslationUnitDeclaration;

    }

    /**
     * Compiling result
     */
    enum class CompilingResult {
        Success,
        Failure
    };

    namespace Driver {

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
            static SharedPtr<GS_TranslationUnit> Create(GSTranslationUnitConfigPtr config);

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
             * Run front compiling process for translation unit
             * @param inputFile Input file name
             * @return AST translation unit declaration node ptr
             */
            SharedPtr<AST::GS_TranslationUnitDeclaration> RunFrontEnd(UString inputFile);

            /**
             * Run middle compilation process for translation unit
             * @param translationUnitDeclaration Translation unit declaration
             * @return
             */
            Bool RunMiddleEnd(LRef<SharedPtr<AST::GS_TranslationUnitDeclaration>> translationUnitDeclaration);

            /**
             * Run back compilation process for translation unit
             * @param translationUnitDeclaration Translation unit declaration
             * @return
             */
            Bool RunBackEnd(LRef<SharedPtr<AST::GS_TranslationUnitDeclaration>> translationUnitDeclaration);

        private:

            /**
             * Unit config
             */
            GSTranslationUnitConfigPtr _config;
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

}

#endif //GSLANGUAGE_GS_TRANSLATIONUNIT_H
