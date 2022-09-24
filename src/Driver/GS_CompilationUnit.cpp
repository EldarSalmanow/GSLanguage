#include <Lexer/Lexer.h>
#include <Parser/Parser.h>

#include <GS_CompilationUnit.h>

namespace GSLanguageCompiler::Driver {

    GS_CompilationUnit::GS_CompilationUnit(IO::GSSourcePtr source, Driver::GSContextPtr context)
            : _source(std::move(source)),
              _tokens(Lexer::GSTokenArray()),
              _node(AST::GSNodePtr()),
              _context(std::move(context)) {}

    std::shared_ptr<GS_CompilationUnit> GS_CompilationUnit::Create(IO::GSSourcePtr source, Driver::GSContextPtr context) {
        return std::make_shared<GS_CompilationUnit>(std::move(source), std::move(context));
    }

    CompilingResult GS_CompilationUnit::Compile() {
        auto lexer = Lexer::GS_Lexer::Create(_context);

        _tokens = lexer.Tokenize(*this);

        auto parser = Parser::GS_Parser::Create(_context);

        _node = parser.ParseProgram(*this);

        return CompilingResult::Success;
    }

    IO::GSSourcePtr GS_CompilationUnit::GetSource() const {
        return _source;
    }

    Lexer::GSTokenArray GS_CompilationUnit::GetTokens() const {
        return _tokens;
    }

    AST::GSNodePtr GS_CompilationUnit::GetNode() const {
        return _node;
    }

    Driver::GSContextPtr GS_CompilationUnit::GetContext() const {
        return _context;
    }

}
