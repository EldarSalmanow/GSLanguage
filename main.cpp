//#include <Driver/GS_TranslationUnitsManager.h>
//
//using namespace GSLanguageCompiler;

#include <Lexer/GS_TokenStream.h>
#include <AST/GS_IncludeAll.h>
#include <AST/GS_TranslationUnit.h>

using namespace GSLanguageCompiler;

namespace New {

    class GS_Parser {
    public:

        explicit GS_Parser(Ptr<Lexer::GS_TokenStream> stream)
                : _stream(stream) {}

    public:

        AST::GS_TranslationUnit Parse() {
            
        }

    public:

        SharedPtr<AST::GS_FunctionDeclaration> ParseFunctionDeclaration(ConstLRef<AST::GSScopePtr> scope) {
            if (!IsTokenType(Lexer::TokenType::KeywordFunc)) {
                return nullptr;
            }

            NextToken(); // skip 'func'

            if (!IsTokenType(Lexer::TokenType::Identifier)) {
                return nullptr;
            }

            auto functionName = TokenValue();

            NextToken(); // skip function name

            if (!IsTokenType(Lexer::TokenType::SymbolLeftParen)) {
                return nullptr;
            }

            NextToken(); // skip '('

            if (!IsTokenType(Lexer::TokenType::SymbolRightParen)) {
                return nullptr;
            }

            NextToken(); // skip ')'

            if (!IsTokenType(Lexer::TokenType::SymbolLeftBrace)) {
                return nullptr;
            }

            AST::GSStatementPtrArray functionBody;

            AST::GSScopePtr functionScope;

            while (!IsTokenType(Lexer::TokenType::SymbolRightBrace)) {
                auto statement = ParseStatement(functionScope);

                functionBody.emplace_back(statement);
            }

            auto function = std::make_shared<AST::GS_FunctionDeclaration>(functionName, functionBody, scope);

            scope->addNode(function);

            return function;
        }

        AST::GSStatementPtr ParseStatement(ConstLRef<AST::GSScopePtr> scope) {
            NextToken();

            return nullptr;
        }

        SharedPtr<AST::GS_AssignmentStatement> ParseAssignmentStatement(ConstLRef<AST::GSScopePtr> scope) {
            auto lvalueExpression = ParseLValueExpression(scope);

            if (!IsTokenType(Lexer::TokenType::SymbolEq)) {
                return nullptr;
            }

            NextToken(); // skip '='

            auto rvalueExpression = ParseRValueExpression(scope);

            return std::make_shared<AST::GS_AssignmentStatement>(lvalueExpression, rvalueExpression, scope);
        }

        SharedPtr<AST::GS_VariableDeclarationStatement> ParseVariableDeclarationStatement(ConstLRef<AST::GSScopePtr> scope) {
            if (!IsTokenType(Lexer::TokenType::KeywordVar)) {
                return nullptr;
            }

            NextToken(); // skip 'var'

            if (!IsTokenType(Lexer::TokenType::Identifier)) {
                return nullptr;
            }

            auto variableName = TokenValue();

            NextToken(); // skip variable name

            if (IsTokenType(Lexer::TokenType::SymbolColon)) {
                NextToken(); // skip ':'

                if (!IsTokenType(Lexer::TokenType::Identifier)) {
                    return nullptr;
                }

                auto stringVariableType = TokenValue();

                AST::GSTypePtr variableType;

                if (stringVariableType == U"I32") {
                    variableType = std::make_shared<AST::GS_I32Type>();
                } else if (stringVariableType == U"String") {
                    variableType = std::make_shared<AST::GS_StringType>();
                } else if (stringVariableType == U"Void") {
                    return nullptr;
                } else {
                    return nullptr;
                }
            }
        }

        AST::GSExpressionPtr ParseLValueExpression(ConstLRef<AST::GSScopePtr> scope) {
            if (IsTokenType(Lexer::TokenType::Identifier)) {
                auto variableName = TokenValue();

                NextToken();

                return std::make_shared<AST::GS_VariableUsingExpression>(variableName, scope);
            }

            return nullptr;
        }

        AST::GSExpressionPtr ParseRValueExpression(ConstLRef<AST::GSScopePtr> scope) {
            NextToken();

            return nullptr;
        }

    public:

        Bool IsTokenType(Lexer::TokenType type) {
            return CurrentToken()->getTokenType() == type;
        }

        UString TokenValue() {
            if (TokenType() != Lexer::TokenType::Identifier &&
                TokenType() != Lexer::TokenType::LiteralNumber &&
                TokenType() != Lexer::TokenType::LiteralString) {
                return UString();
            }

            return ReinterpretCast<Ptr<Lexer::GS_ValueToken>>(CurrentToken().get())->getValue();
        }

        Lexer::TokenType TokenType() {
            return CurrentToken()->getTokenType();
        }

        Lexer::GSTokenPtr CurrentToken() {
            return _token;
        }

        Void NextToken() {
            _token = _stream->getToken();
        }

    private:

        Ptr<Lexer::GS_TokenStream> _stream;

        Lexer::GSTokenPtr _token;
    };

}

AST::GSScopePtr CreateGlobalScope() {
    return std::make_shared<AST::GS_Scope>(nullptr);
}

AST::GSTypePtr CreateVoidType() {
    return std::make_shared<AST::GS_VoidType>();
}

AST::GSTypePtr CreateI32Type() {
    return std::make_shared<AST::GS_I32Type>();
}

AST::GSTypePtr CreateStringType() {
    return std::make_shared<AST::GS_StringType>();
}

AST::GSValuePtr CreateValue(I32 value) {
    return std::make_shared<AST::GS_I32Value>(value);
}

AST::GSValuePtr CreateValue(ConstLRef<UString> value) {
    return std::make_shared<AST::GS_StringValue>(value);
}

SharedPtr<AST::GS_ConstantExpression> CreateConstant(ConstLRef<AST::GSValuePtr> value, ConstLRef<AST::GSScopePtr> scope) {
    auto expression = std::make_shared<AST::GS_ConstantExpression>(value, scope);

    scope->addNode(expression);

    return expression;
}

SharedPtr<AST::GS_ConstantExpression> CreateConstant(I32 value, ConstLRef<AST::GSScopePtr> scope) {
    return CreateConstant(CreateValue(value), scope);
}

SharedPtr<AST::GS_ConstantExpression> CreateConstant(ConstLRef<UString> value, ConstLRef<AST::GSScopePtr> scope) {
    return CreateConstant(CreateValue(value), scope);
}

SharedPtr<AST::GS_VariableDeclarationStatement> CreateVariable(ConstLRef<UString> name, ConstLRef<AST::GSTypePtr> type, ConstLRef<AST::GSExpressionPtr> expression, ConstLRef<AST::GSScopePtr> scope) {
    auto statement = std::make_shared<AST::GS_VariableDeclarationStatement>(name, type, expression, scope);

    scope->addNode(statement);

    return statement;
}

SharedPtr<AST::GS_FunctionDeclaration> CreateFunction(ConstLRef<UString> name, ConstLRef<AST::GSScopePtr> scope) {
    auto function = std::make_shared<AST::GS_FunctionDeclaration>(name, scope);

    scope->addNode(function);

    return function;
}

SharedPtr<AST::GS_FunctionDeclaration> CreateFunction(ConstLRef<UString> name, ConstLRef<AST::GSStatementPtrArray> statements,  ConstLRef<AST::GSScopePtr> scope) {
    auto function = std::make_shared<AST::GS_FunctionDeclaration>(name, statements, scope);

    scope->addNode(function);

    return function;
}

I32 main() {
    auto globalScope = CreateGlobalScope();

    auto function = CreateFunction(U"main", globalScope);

    function->addStatement(CreateVariable(U"a", CreateI32Type(), CreateConstant(12, function->getFunctionScope()), function->getFunctionScope()));

//    Driver::GS_TranslationUnit unit(U"../test.gs");
//
//    return unit.compile();
}
