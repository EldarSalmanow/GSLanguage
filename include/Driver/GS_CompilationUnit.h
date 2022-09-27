#ifndef GSLANGUAGE_GS_COMPILATIONUNIT_H
#define GSLANGUAGE_GS_COMPILATIONUNIT_H

#include <IO/IO.h>

#include <Driver/GS_Context.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Result of compiling
     */
    enum class CompilingResult : I32 {
        Success = 0,
        Failure = 1
    };

    /**
     * Class for compiling source and containing source, tokens and AST node
     */
    class GS_CompilationUnit {
    public:

        /**
         * Constructor for compilation unit
         * @param source Source
         * @param context Context
         */
        GS_CompilationUnit(IO::GSSourcePtr source, Driver::GSContextPtr context);

    public:

        /**
         * Creating compilation unit
         * @param source Source
         * @param context Context
         * @return Compilation unit ptr
         */
        static std::shared_ptr<GS_CompilationUnit> Create(IO::GSSourcePtr source, Driver::GSContextPtr context);

    public:

        /**
         * Read, lex and parse input source and compile it
         * @return Compiling result
         */
        CompilingResult Compile();

    public:

        /**
         * Getter for source
         * @return Source
         */
        IO::GSSourcePtr GetSource() const;

        /**
         * Getter for tokens
         * @return Tokens
         */
        Lexer::GSTokenArray GetTokens() const;

        /**
         * Getter for AST node
         * @return AST node
         */
        AST::GSNodePtr GetNode() const;

        /**
         * Getter for context
         * @return Context
         */
        Driver::GSContextPtr GetContext() const;

    private:

        /**
         * Source
         */
        IO::GSSourcePtr _source;

        /**
         * Tokens
         */
        Lexer::GSTokenArray _tokens;

        /**
         * AST node
         */
        AST::GSNodePtr _node;

        /**
         * Context
         */
        Driver::GSContextPtr _context;
    };

    /**
     * Compilation unit ptr type
     */
    using GSCompilationUnitPtr = std::shared_ptr<GS_CompilationUnit>;

    /**
     * Compilation unit ptr array type
     */
    using GSCompilationUnitPtrArray = std::vector<GSCompilationUnitPtr>;

}

#endif //GSLANGUAGE_GS_COMPILATIONUNIT_H
