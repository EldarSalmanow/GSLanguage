#ifndef GSLANGUAGE_GS_SESSIONSMANAGER_H
#define GSLANGUAGE_GS_SESSIONSMANAGER_H

#include <Driver/GS_Session.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for managing compiler sessions
     */
    class GS_SessionsManager {
    public:

        /**
         * Creating sessions manager
         * @param sessions Compiler sessions
         */
        explicit GS_SessionsManager(GSSessionPtrArray sessions);

    public:

        /**
         * Creating sessions manager
         * @param sessions Sessions
         * @return Sessions manager ptr
         */
        static std::shared_ptr<GS_SessionsManager> Create(GSSessionPtrArray sessions);

        /**
         * Creating sessions manager
         * @return Sessions manager ptr
         */
        static std::shared_ptr<GS_SessionsManager> Create();

    public:

        /**
         * Running compiler sessions
         * @return Compiling results
         */
        std::vector<CompilingResult> RunSessions();

        /**
         * Adding session
         * @param session Session
         * @return
         */
        Void AddSession(GSSessionPtr session);

    public:

        /**
         * Getter for sessions
         * @return Sessions
         */
        GSSessionPtrArray GetSessions() const;

    private:

        /**
         * Sessions
         */
        GSSessionPtrArray _sessions;
    };

}

#endif //GSLANGUAGE_GS_SESSIONSMANAGER_H
