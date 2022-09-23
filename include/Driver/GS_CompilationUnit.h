#ifndef GSLANGUAGE_GS_COMPILATIONUNIT_H
#define GSLANGUAGE_GS_COMPILATIONUNIT_H

#include <IO/IO.h>

#include <Driver/GS_Context.h>

namespace GSLanguageCompiler::Driver {

    enum class CompilingResult : I32 {
        Success = 0,
        Failure = 1
    };

    class GS_CompilationUnit {
    public:

        GS_CompilationUnit(IO::GSSourcePtr source, Driver::GSContextPtr context);

    public:

        static std::shared_ptr<GS_CompilationUnit> Create(IO::GSSourcePtr source, Driver::GSContextPtr context);

    public:

        CompilingResult Compile();

    public:

        IO::GSSourcePtr GetSource() const;

        Lexer::GSTokenArray GetTokens() const;

        AST::GSNodePtr GetNode() const;

        Driver::GSContextPtr GetContext() const;

    private:

        IO::GSSourcePtr _source;

        Lexer::GSTokenArray _tokens;

        AST::GSNodePtr _node;

        Driver::GSContextPtr _context;
    };

    using GSCompilationUnitPtr = std::shared_ptr<GS_CompilationUnit>;

    using GSCompilationUnitPtrArray = std::vector<GSCompilationUnitPtr>;

}

#endif //GSLANGUAGE_GS_COMPILATIONUNIT_H
