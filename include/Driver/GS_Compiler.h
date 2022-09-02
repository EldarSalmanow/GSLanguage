#ifndef GSLANGUAGE_GS_COMPILER_H
#define GSLANGUAGE_GS_COMPILER_H

#include <Driver/GS_SessionsManager.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for startup and manage GSLanguageCompiler
     */
    class GS_Compiler {
    public:

        explicit GS_Compiler(GSSessionPtrArray sessions);

    public:

        static std::shared_ptr<GS_Compiler> Create(GSSessionPtrArray sessions);

        static std::shared_ptr<GS_Compiler> Create();

    public:

        static std::shared_ptr<GS_Compiler> Create(GS_Arguments arguments);

    public:

        static CompilingResult Start(I32 argc, Ptr<Ptr<C>> argv);

    public:

        CompilingResult Run();

    public:

        Void AddSession(GSSessionPtr session);

    public:

        GSSessionPtrArray GetSessions() const;

    private:

        GSSessionPtrArray _sessions;
    };

    using GSCompilerPtr = std::shared_ptr<GS_Compiler>;

}

#endif //GSLANGUAGE_GS_COMPILER_H
