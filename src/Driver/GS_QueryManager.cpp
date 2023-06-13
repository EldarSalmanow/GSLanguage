#include <Parser/Parser.h>

#include <GS_Session.h>

#include <GS_QueryManager.h>

namespace GSLanguageCompiler::Driver {

    GS_QueryManager::GS_QueryManager() = default;

    std::unique_ptr<GS_QueryManager> GS_QueryManager::Create() {
        return std::make_unique<GS_QueryManager>();
    }

    // TODO refactor

    AST::GSTranslationUnitDeclarationPtr GS_QueryManager::Compile(LRef<Driver::GS_Session> session,
                                                                  UString key) {
        auto program = session.Parse(std::move(key));

        return program;
    }

    AST::GSTranslationUnitDeclarationPtr GS_QueryManager::Parse(LRef<Driver::GS_Session> session,
                                                                UString key) {
        auto movedKey = std::move(key);

        auto tokenBuffer = session.Tokenize(movedKey);

        auto parser = Parser::GS_Parser::Create(session,
                                                tokenBuffer);

        auto program = parser.ParseProgram(movedKey);

        return program;
    }

    Lexer::GS_TokenBuffer GS_QueryManager::Tokenize(LRef<Driver::GS_Session> session,
                                                    UString key) {
        auto source = session.Read(std::move(key));

        auto lexer = Lexer::GS_Lexer::Create(session,
                                             source);

        auto tokenBuffer = lexer.Tokenize();

        return tokenBuffer;
    }

    ConstLRef<IO::GS_Source> GS_QueryManager::Read(LRef<Driver::GS_Session> session,
                                                   UString key) {
        return session.AddFileSource(std::move(key));
    }

}
