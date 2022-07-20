#ifndef GSLANGUAGE_GS_TRANSLATIONUNITCONFIG_H
#define GSLANGUAGE_GS_TRANSLATIONUNITCONFIG_H

#include <Driver/GS_CompilerSessionConfig.h>

namespace GSLanguageCompiler::Driver {

    // TODO replace source hash to source ?

    /**
     * Class for representation translation unit configs
     */
    class GS_TranslationUnitConfig {
    public:

        /**
         * Constructor for translation unit config
         * @param sourceHash Source hash for getting source for compiling from source manager
         * @param sessionConfig Session config
         */
        GS_TranslationUnitConfig(U64 sourceHash, GSCompilerSessionConfigPtr sessionConfig);

    public:

        /**
         * Creating translation unit config
         * @param sourceHash Source hash
         * @param sessionConfig Session config
         * @return Translation unit config ptr
         */
        static std::shared_ptr<GS_TranslationUnitConfig> Create(U64 sourceHash, GSCompilerSessionConfigPtr sessionConfig);

    public:

        /**
         * Getter for source hash
         * @return Source hash
         */
        U64 GetSourceHash() const;

        /**
         * Getter for session config
         * @return Session config
         */
        GSCompilerSessionConfigPtr GetSessionConfig() const;

    private:

        /**
         * Source hash
         */
        U64 _sourceHash;

        /**
         * Session config
         */
        GSCompilerSessionConfigPtr _sessionConfig;
    };

    /**
     * Translation unit config ptr type
     */
    using GSTranslationUnitConfigPtr = std::shared_ptr<GS_TranslationUnitConfig>;

    /**
     * Translation unit config ptr array type
     */
    using GSTranslationUnitConfigPtrArray = std::vector<GSTranslationUnitConfigPtr>;

}

#endif //GSLANGUAGE_GS_TRANSLATIONUNITCONFIG_H
