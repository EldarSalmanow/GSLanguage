#ifndef GSLANGUAGE_GS_TRANSLATIONUNITCONFIG_H
#define GSLANGUAGE_GS_TRANSLATIONUNITCONFIG_H

#include <Driver/GS_SessionContext.h>

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
         * @param sessionContext Session context
         */
        GS_TranslationUnitConfig(U64 sourceHash, GSSessionContextPtr sessionContext);

    public:

        /**
         * Creating translation unit config
         * @param sourceHash Source hash
         * @param sessionContext Session context
         * @return Translation unit config ptr
         */
        static std::shared_ptr<GS_TranslationUnitConfig> Create(U64 sourceHash, GSSessionContextPtr sessionContext);

    public:

        /**
         * Getter for source hash
         * @return Source hash
         */
        U64 GetSourceHash() const;

        /**
         * Getter for session context
         * @return Session context
         */
        GSSessionContextPtr GetSessionContext() const;

    private:

        /**
         * Source hash
         */
        U64 _sourceHash;

        /**
         * Session context
         */
        GSSessionContextPtr _sessionContext;
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
