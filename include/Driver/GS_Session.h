#ifndef GSLANGUAGE_GS_SESSION_H
#define GSLANGUAGE_GS_SESSION_H

#include <Driver/GS_CompilationUnit.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for representation compiler sessions
     */
    class GS_Session {
    public:

        /**
         * Constructor for compiler session
         * @param context Context
         */
        explicit GS_Session(GSContextPtr context);

    public:

        /**
         * Creating compiler session
         * @param context Context
         * @return Compiler session ptr
         */
        static std::shared_ptr<GS_Session> Create(GSContextPtr context);

        /**
         * Creating compiler session
         * @return Compiler session ptr
         */
        static std::shared_ptr<GS_Session> Create();

    public:

        /**
         * Run compiler session
         * @return Compiling result
         */
        CompilingResult Run();

    public:

        /**
         * Getter for context
         * @return Context
         */
        GSContextPtr GetContext() const;

    private:

        /**
         * Context
         */
        GSContextPtr _context;
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
