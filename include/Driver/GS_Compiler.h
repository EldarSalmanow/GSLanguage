#ifndef GSLANGUAGE_GS_COMPILER_H
#define GSLANGUAGE_GS_COMPILER_H

#include <Driver/GS_SessionManager.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for startup and manage GSLanguageCompiler
     */
    class GS_Compiler {
    public:

        /*
         *
         * GS_Compiler PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for compiler
         * @param sessionManager Session manager
         */
        explicit GS_Compiler(GSSessionManagerPtr sessionManager);

    public:

        /*
         *
         * GS_Compiler PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating compiler
         * @param sessionManager Session manager
         * @return Compiler ptr
         */
        static std::unique_ptr<GS_Compiler> Create(GSSessionManagerPtr sessionManager);

        /**
         * Creating compiler
         * @return Compiler ptr
         */
        static std::unique_ptr<GS_Compiler> Create();

        /**
         * Creating compiler with one session, created on arguments
         * @param arguments Arguments for one session
         * @return Compiler ptr
         */
        static std::unique_ptr<GS_Compiler> Create(GS_Arguments arguments);

    public:

        /*
         *
         * GS_Compiler PUBLIC STATIC METHODS
         *
         */

        /**
         * Start compiler with one session, created on arguments
         * @param argc Arguments counter
         * @param argv Arguments values
         * @return Compiling result
         */
        static CompilingResult Start(I32 argc, Ptr<Ptr<C>> argv);

    public:

        /*
         *
         * GS_Compiler PUBLIC METHODS
         *
         */

        /**
         * Run sessions in compiler
         * @return Sessions compiling result
         */
        CompilingResult Run();

        /**
         * Add session to sessions manager
         * @param session Session
         * @return Session
         */
        ConstLRef<GS_Session> AddSession(GSSessionPtr session);

        /**
         * Getter for sessions from sessions manager
         * @return Sessions
         */
        ConstLRef<GSSessionPtrArray> GetSessions() const;

    public:

        /*
         *
         * GS_Compiler PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for session manager
         * @return Session manager
         */
        LRef<GS_SessionManager> GetSessionManager();

    private:

        /*
         *
         * GS_Compiler PRIVATE FIELDS
         *
         */

        /**
         * Session manager
         */
        GSSessionManagerPtr _sessionManager;
    };

    /**
     * Compiler ptr type
     */
    using GSCompilerPtr = std::unique_ptr<GS_Compiler>;

}

#endif //GSLANGUAGE_GS_COMPILER_H
