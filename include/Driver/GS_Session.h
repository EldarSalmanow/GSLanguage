#ifndef GSLANGUAGE_GS_SESSION_H
#define GSLANGUAGE_GS_SESSION_H

#include <Driver/GS_SessionContext.h>

#include <Driver/GS_TranslationUnitsManager.h>

#include <Driver/GS_Toolchains.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for representation compiler sessions
     */
    class GS_Session {
    public:

        /**
         * Constructor for compiler session
         * @param sessionContext Compiler session context
         */
        explicit GS_Session(GSSessionContextPtr sessionContext);

    public:

        /**
         * Creating compiler session
         * @param sessionContext Compiler session context
         * @return Compiler session ptr
         */
        static std::shared_ptr<GS_Session> Create(GSSessionContextPtr sessionContext);

    public:

        /**
         * Run compiler session
         * @return Compiling result
         */
        CompilingResult Run();

    public:

        /**
         * Getter for default toolchain
         * @return Default toolchain
         */
        GSToolchainPtr GetDefaultToolchain();

    public:

        /**
         * Getter for compiler session context
         * @return Compiler session context
         */
        GSSessionContextPtr GetSessionContext() const;

    private:

        /**
         * Compiler session context
         */
        GSSessionContextPtr _sessionContext;
    };

    /**
     * Session ptr type
     */
    using GSSessionPtr = std::shared_ptr<GS_Session>;

    /**
     * Session ptr array type
     */
    using GSSessionPtrArray = std::vector<GSSessionPtr>;

}

#endif //GSLANGUAGE_GS_SESSION_H
