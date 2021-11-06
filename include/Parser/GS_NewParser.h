#ifndef GSLANGUAGE_GS_NEWPARSER_H
#define GSLANGUAGE_GS_NEWPARSER_H

#include <Lexer/GS_TokenStream.h>

#include <AST/GS_IncludeAll.h>

namespace GSLanguageCompiler::Parser::New {

    class GS_Error {
    public:

        GS_Error(String category, String concrete)
                : _category(std::move(category)), _concrete(std::move(concrete)) {}

    public:

        String errorMessage() {
            auto errorMessage = "Category: " + _category + " Concrete: " + _concrete;

            return errorMessage;
        }

    private:

        String _category, _concrete;
    };

    class GS_Parser {
    public:

        AST::GSDeclarationPtrArray parseProgram(Lexer::GS_TokenStream *tokenStream) {
            AST::GSDeclarationPtrArray declarations;

            scope = std::make_shared<AST::GS_Scope>(nullptr);

            while (!tokenStream->isEqualTypes(Lexer::TokenType::EndOfFile)) {
                auto declaration = parseDeclaration(tokenStream);

                if (!declaration) {
                    break;
                }

                declarations.emplace_back(declaration);
            }

            return declarations;
        }

        AST::GSDeclarationPtr parseDeclaration(Lexer::GS_TokenStream *tokenStream) {
            if (tokenStream->isEqualTypes(Lexer::TokenType::KeywordFunc)) {
                return parseFunctionDeclaration(tokenStream);
            }

            addError("unknown declaration", "unknown declaration");

            return nullptr;
        }

        AST::GSDeclarationPtr parseFunctionDeclaration(Lexer::GS_TokenStream *tokenStream) {
            if (!tokenStream->isEqualTypes(Lexer::TokenType::KeywordFunc)) {
                addError("function declaration", "missed keyword \'func\'");
            }

            tokenStream->next();

            if (!tokenStream->isEqualTypes(Lexer::TokenType::Identifier)) {
                addError("function declaration", "invalid function name");
            }

            auto functionName = tokenStream->tokenValue();

            tokenStream->next();

            if (!tokenStream->isEqualTypes(Lexer::TokenType::SymbolLeftParen)) {
                addError("function declaration", "missed symbol \'(\' for params list");
            }

            tokenStream->next();

            /*
             * TODO: Add supporting params list
             */

            if (!tokenStream->isEqualTypes(Lexer::TokenType::SymbolRightParen)) {
                addError("function declaration", "missed symbol \')\' for params list");
            }

            tokenStream->next();

            if (!tokenStream->isEqualTypes(Lexer::TokenType::SymbolLeftBrace)) {
                addError("function declaration", "missed symbol \'{\' for function code");
            }

            tokenStream->next();

            AST::GSStatementPtrArray body;

            while (true) {
                auto statement = parseStatement(tokenStream);

                if (!statement) {
                    break;
                }

                body.emplace_back(statement);
            }

            if (!tokenStream->isEqualTypes(Lexer::TokenType::SymbolRightBrace)) {
                addError("function declaration", "missed symbol \'}\' for function code");
            }

            tokenStream->next();

            return std::make_shared<AST::GS_FunctionDeclaration>(functionName, body, std::move(scope));
        }

        AST::GSStatementPtr parseStatement(Lexer::GS_TokenStream *tokenStream) {
            return nullptr;
        }

        Void addError(String category, String concrete) {
            errors.emplace_back(GS_Error(std::move(category), std::move(concrete)));
        }

    public:

        AST::GSScopePtr scope;

        Vector<GS_Error> errors;
    };

}

#endif //GSLANGUAGE_GS_NEWPARSER_H
