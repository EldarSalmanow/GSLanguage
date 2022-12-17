#ifndef GSLANGUAGE_GS_COMPILER_H
#define GSLANGUAGE_GS_COMPILER_H

#include <Driver/GS_SessionsManager.h>

namespace GSLanguageCompiler::Driver {

    // todo use session manager ?

    /**
     * Class for startup and manage GSLanguageCompiler
     */
    class GS_Compiler {
    public:

        /**
         * Constructor for compiler
         * @param sessions Sessions
         */
        explicit GS_Compiler(GSSessionPtrArray sessions);

    public:

        /**
         * Creating compiler
         * @param sessions Sessions
         * @return Compiler ptr
         */
        static std::unique_ptr<GS_Compiler> Create(GSSessionPtrArray sessions);

        /**
         * Creating compiler
         * @return Compiler ptr
         */
        static std::unique_ptr<GS_Compiler> Create();

    public:

        /**
         * Creating compiler with one session, created on arguments
         * @param arguments Arguments for one session
         * @return Compiler ptr
         */
        static std::unique_ptr<GS_Compiler> Create(GS_Arguments arguments);

    public:

        /**
         * Start compiler with one session, created on arguments
         * @param argc Arguments counter
         * @param argv Arguments values
         * @return Compiling result
         */
        static CompilingResult Start(I32 argc, Ptr<Ptr<C>> argv);

    public:

        /**
         * Run sessions in compiler
         * @return Sessions compiling result
         */
        CompilingResult Run();

    public:

        /**
         * Add session to compiler
         * @param session Session
         * @return Session
         */
        ConstLRef<GS_Session> AddSession(GSSessionPtr session);

    public:

        /**
         * Getter for sessions
         * @return Sessions
         */
        ConstLRef<GSSessionPtrArray> GetSessions() const;

    private:

        /**
         * Sessions
         */
        GSSessionPtrArray _sessions;
    };

    /**
     * Compiler ptr type
     */
    using GSCompilerPtr = std::unique_ptr<GS_Compiler>;

}

#endif //GSLANGUAGE_GS_COMPILER_H
