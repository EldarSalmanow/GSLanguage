#ifndef GSLANGUAGE_GS_SESSION_H
#define GSLANGUAGE_GS_SESSION_H

#include <Driver/GS_CompilationUnit.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for representation compiler sessions
     */
    class GS_Session {
    public:

        explicit GS_Session(GSContextPtr context);

    public:

        static std::shared_ptr<GS_Session> Create(GSContextPtr context);

        static std::shared_ptr<GS_Session> Create();

    public:

        CompilingResult Run();

    public:

        GSContextPtr GetContext() const;

    private:

        GSContextPtr _context;
    };

    using GSSessionPtr = std::shared_ptr<GS_Session>;

    using GSSessionPtrArray = std::vector<GSSessionPtr>;

}

#endif //GSLANGUAGE_GS_SESSION_H
