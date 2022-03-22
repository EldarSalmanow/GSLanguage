#ifndef GSLANGUAGE_GS_COMPILERCONFIG_H
#define GSLANGUAGE_GS_COMPILERCONFIG_H

#include <Driver/GS_TranslationUnitConfig.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for representation all configs of compiler
     */
    class GS_CompilerConfig {
    public:

        /**
         * Constructor for compiler config
         * @param unitConfigs Unit configs
         */
        explicit GS_CompilerConfig(GSTranslationUnitConfigPtrArray unitConfigs);

    public:

        /**
         * Creating compiler config
         * @param unitConfigs Unit configs
         * @return Compiler configs
         */
        static SharedPtr<GS_CompilerConfig> Create(GSTranslationUnitConfigPtrArray unitConfigs);

    public:

        /**
         * Getter for unit configs
         * @return Unit configs
         */
        GSTranslationUnitConfigPtrArray GetUnitConfigs() const;

    private:

        /**
         * Unit configs
         */
        GSTranslationUnitConfigPtrArray _unitConfigs;
    };

    /**
     * Compiler config ptr type
     */
    using GSCompilerConfigPtr = SharedPtr<GS_CompilerConfig>;

}

#endif //GSLANGUAGE_GS_COMPILERCONFIG_H
