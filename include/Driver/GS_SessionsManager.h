#ifndef GSLANGUAGE_GS_SESSIONSMANAGER_H
#define GSLANGUAGE_GS_SESSIONSMANAGER_H

#include <Driver/GS_Session.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for managing compiler sessions
     */
    class GS_SessionsManager {
    public:

        /*
         *
         * GS_SessionsManager PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Creating sessions manager
         * @param sessions Compiler sessions
         */
        explicit GS_SessionsManager(GSSessionPtrArray sessions);

    public:

        /*
         *
         * GS_SessionsManager PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating sessions manager
         * @param sessions Sessions
         * @return Sessions manager ptr
         */
        static std::unique_ptr<GS_SessionsManager> Create(GSSessionPtrArray sessions);

        /**
         * Creating sessions manager
         * @return Sessions manager ptr
         */
        static std::unique_ptr<GS_SessionsManager> Create();

    public:

        /*
         *
         * GS_SessionsManager PUBLIC METHODS
         *
         */

        /**
         * Running compiler sessions
         * @return Compiling results
         */
        std::vector<CompilingResult> RunSessions();

        /**
         * Adding session
         * @param session Session
         * @return Session
         */
        ConstLRef<GS_Session> AddSession(GSSessionPtr session);

    public:

        /*
         *
         * GS_SessionsManager PUBLIC GETTERS
         *
         */

        /**
         * Getter for sessions
         * @return Sessions
         */
        ConstLRef<GSSessionPtrArray> GetSessions() const;

    private:

        /*
         *
         * GS_SessionsManager PRIVATE FIELDS
         *
         */

        /**
         * Sessions
         */
        GSSessionPtrArray _sessions;
    };

    /**
     * Sessions manager ptr type
     */
    using GSSessionsManagerPtr = std::unique_ptr<GS_SessionsManager>;

}

#endif //GSLANGUAGE_GS_SESSIONSMANAGER_H
