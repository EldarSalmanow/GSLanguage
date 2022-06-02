#ifndef GSLANGUAGE_GS_COMPILERSESSIONSMANAGER_H
#define GSLANGUAGE_GS_COMPILERSESSIONSMANAGER_H

#include <Driver/GS_CompilerSession.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for managing compiler sessions
     */
    class GS_CompilerSessionsManager {
    public:

        /**
         * Creating compiler sessions manager
         * @param sessions Compiler sessions
         */
        explicit GS_CompilerSessionsManager(GSCompilerSessionPtrArray sessions);

    public:

        /**
         * Creating compiler sessions manager
         * @param sessions Compiler sessions
         * @return Compiler sessions manager ptr
         */
        static std::shared_ptr<GS_CompilerSessionsManager> Create(GSCompilerSessionPtrArray sessions);

        /**
         * Creating compiler sessions manager
         * @return Compiler sessions manager ptr
         */
        static std::shared_ptr<GS_CompilerSessionsManager> Create();

    public:

        /**
         * Running compiler sessions
         * @return Compiling results
         */
        std::vector<CompilingResult> RunSessions();

        /**
         * Adding compiler session
         * @param session Compiler session
         * @return
         */
        Void AddSession(GSCompilerSessionPtr session);

    public:

        /**
         * Getter for compiler sessions
         * @return Compiler sessions
         */
        GSCompilerSessionPtrArray GetSessions() const;

    private:

        /**
         * Compiler sessions
         */
        GSCompilerSessionPtrArray _sessions;
    };

}

#endif //GSLANGUAGE_GS_COMPILERSESSIONSMANAGER_H
