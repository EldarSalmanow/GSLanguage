#include <Lexer/Lexer.h>
#include <Parser/Parser.h>

#include <Debug/Debug.h>

#include <GS_Session.h>

namespace GSLanguageCompiler::Driver {

    GS_Session::GS_Session(GSContextPtr context)
            : _context(std::move(context)) {}

    std::shared_ptr<GS_Session> GS_Session::Create(GSContextPtr context) {
        return std::make_shared<GS_Session>(std::move(context));
    }

    std::shared_ptr<GS_Session> GS_Session::Create() {
        return GS_Session::Create(GS_Context::Create());
    }

    CompilingResult GS_Session::Run() {
        // TODO

        AST::GSTranslationUnitDeclarationPtrArray units;

        for (auto &inputSource : _context->GetInputSources()) {
            auto source = inputSource->GetSource();

            auto tokens = Lexer::GS_Lexer::Create(source, _context).Tokenize();

            auto unit = Parser::GS_Parser::Create(tokens, _context).ParseProgram();

            units.emplace_back(unit);

            Debug::DumpAST(unit);
        }

        return CompilingResult::Success;
    }

    GSContextPtr GS_Session::GetContext() const {
        return _context;
    }

}
