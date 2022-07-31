#ifndef GSLANGUAGE_GS_COMPILER_H
#define GSLANGUAGE_GS_COMPILER_H

#include <Driver/GS_SessionsManager.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for startup and manage GSLanguageCompiler
     */
    class GS_Compiler {
    public:

        /**
         * Constructor for compiler
         * @param sessionContexts Compiler session contexts
         */
        explicit GS_Compiler(GSSessionContextPtrArray sessionContexts);

    public:

        /**
         * Creating compiler
         * @param sessionContexts Compiler session contexts
         * @return Compiler ptr
         */
        static std::shared_ptr<GS_Compiler> Create(GSSessionContextPtrArray sessionContexts);

        /**
         * Creating compiler
         * @return Compiler ptr
         */
        static std::shared_ptr<GS_Compiler> Create();

    public:

        /**
         * Compiler entry point for create and startup one compiler session
         * @param argc Arguments counter
         * @param argv Arguments value
         * @return Compiler result. 0 - success, any results - failure
         */
        static I32 Start(I32 argc, Ptr<Ptr<C>> argv);

    public:

        /**
         * Run compiling process
         * @return Compiling result. 0 - success, any results - failure
         */
        I32 Run();

    public:

        /**
         * Adding session context
         * @param sessionContext Session context
         * @return
         */
        Void AddSessionContext(GSSessionContextPtr sessionContext);

    public:

        /**
         * Getter for compiler session contexts
         * @return Compiler session contexts
         */
        GSSessionContextPtrArray GetSessionContexts() const;

    private:

        /**
         * Compiler session contexts
         */
        GSSessionContextPtrArray _sessionContexts;
    };

}

#endif //GSLANGUAGE_GS_COMPILER_H
