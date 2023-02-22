#ifndef GSLANGUAGE_GS_SESSIONMANAGER_H
#define GSLANGUAGE_GS_SESSIONMANAGER_H

#include <Driver/GS_Session.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for managing compiler sessions
     */
    class GS_SessionManager {
    public:

        /*
         *
         * GS_SessionManager PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Creating session manager
         * @param sessions Sessions
         */
        explicit GS_SessionManager(GSSessionPtrArray sessions);

    public:

        /*
         *
         * GS_SessionManager PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating session manager
         * @param sessions Sessions
         * @return Session manager ptr
         */
        static std::unique_ptr<GS_SessionManager> Create(GSSessionPtrArray sessions);

        /**
         * Creating session manager
         * @return Session manager ptr
         */
        static std::unique_ptr<GS_SessionManager> Create();

    public:

        /*
         *
         * GS_SessionManager PUBLIC METHODS
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
         * GS_SessionManager PUBLIC GETTER METHODS
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
         * GS_SessionManager PRIVATE FIELDS
         *
         */

        /**
         * Sessions
         */
        GSSessionPtrArray _sessions;
    };

    /**
     * Session manager ptr type
     */
    using GSSessionManagerPtr = std::unique_ptr<GS_SessionManager>;

}

#endif //GSLANGUAGE_GS_SESSIONMANAGER_H
