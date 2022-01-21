//#include <Driver/GS_TranslationUnitsManager.h>
//
//using namespace GSLanguageCompiler;
//
//I32 main() {
//    Driver::GS_TranslationUnit unit(U"../test.gs");
//
//    return unit.compile();
//}

#include <Lexer/Lexer.h>

#include <AST/AST.h>

using namespace GSLanguageCompiler;

namespace New {

    Map<Lexer::TokenType, I32> OperatorsPrecedence = {
            {Lexer::TokenType::SymbolStar,  2},
            {Lexer::TokenType::SymbolSlash, 2},
            {Lexer::TokenType::SymbolPlus,  1},
            {Lexer::TokenType::SymbolMinus, 1}
    };

    class GS_Parser {
    public:

        explicit GS_Parser(Ptr<Lexer::GS_TokenStream> stream)
                : _stream(stream), _token(_stream->getToken()) {}

    public:

        AST::GSTranslationUnitPtr Parse() {
            AST::GSNodePtrArray nodes;

            auto globalScope = std::make_shared<AST::GS_Scope>(nullptr);

            while (!IsTokenType(Lexer::TokenType::EndOfFile)) {
                auto node = ParseDeclaration(globalScope);

                nodes.emplace_back(node);
            }

            return std::make_shared<AST::GS_TranslationUnit>(nodes, globalScope);
        }

    public:

        AST::GSDeclarationPtr ParseDeclaration(ConstLRef<AST::GSScopePtr> scope) {
            if (IsTokenType(Lexer::TokenType::KeywordFunc)) {
                return ParseFunctionDeclaration(scope);
            }

            return nullptr;
        }

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

            NextToken(); // skip '{'

            auto function = std::make_shared<AST::GS_FunctionDeclaration>(functionName, scope);

            while (!IsTokenType(Lexer::TokenType::SymbolRightBrace)) {
                auto statement = ParseStatement(function->getFunctionScope());

                function->addStatement(statement);
            }

            NextToken(); // skip '}'

            scope->addNode(function);

            return function;
        }

        AST::GSStatementPtr ParseStatement(ConstLRef<AST::GSScopePtr> scope) {
            if (IsTokenType(Lexer::TokenType::KeywordVar)) {
                return ParseVariableDeclarationStatement(scope);
            }

            auto expression = ParseExpression(scope);

            if (IsTokenType(Lexer::TokenType::SymbolEq)) {
                return ParseAssignmentStatement(expression, scope);
            }

            return ParseExpressionStatement(scope);
        }

        SharedPtr<AST::GS_AssignmentStatement> ParseAssignmentStatement(ConstLRef<AST::GSScopePtr> scope) {
            auto lvalueExpression = ParseLValueExpression(scope);

            if (!IsTokenType(Lexer::TokenType::SymbolEq)) {
                return nullptr;
            }

            NextToken(); // skip '='

            auto rvalueExpression = ParseRValueExpression(scope);

            auto assignmentStatement = std::make_shared<AST::GS_AssignmentStatement>(lvalueExpression, rvalueExpression, scope);

            scope->addNode(assignmentStatement);

            return assignmentStatement;
        }

        SharedPtr<AST::GS_AssignmentStatement> ParseAssignmentStatement(ConstLRef<AST::GSExpressionPtr> lvalueExpression, ConstLRef<AST::GSScopePtr> scope) {
            if (!IsTokenType(Lexer::TokenType::SymbolEq)) {
                return nullptr;
            }

            NextToken(); // skip '='

            auto rvalueExpression = ParseRValueExpression(scope);

            auto assignmentStatement = std::make_shared<AST::GS_AssignmentStatement>(lvalueExpression, rvalueExpression, scope);

            scope->addNode(assignmentStatement);

            return assignmentStatement;
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

                auto variableType = ParseType();

                if (variableType->getName() == U"Void") {
                    return nullptr;
                }

                if (IsTokenType(Lexer::TokenType::SymbolEq)) {
                    NextToken(); // skip '='

                    auto variableExpression = ParseRValueExpression(scope);

                    auto variable = std::make_shared<AST::GS_VariableDeclarationStatement>(variableName, variableType, variableExpression, scope);

                    scope->addNode(variable);

                    return variable;
                }

                auto variable = std::make_shared<AST::GS_VariableDeclarationStatement>(variableName, variableType, scope);

                scope->addNode(variable);

                return variable;
            } else if (IsTokenType(Lexer::TokenType::SymbolEq)) {
                NextToken(); // skip '='

                auto variableExpression = ParseRValueExpression(scope);

                auto variable = std::make_shared<AST::GS_VariableDeclarationStatement>(variableName, variableExpression, scope);

                scope->addNode(variable);

                return variable;
            }

            return nullptr;
        }

        SharedPtr<AST::GS_ExpressionStatement> ParseExpressionStatement(ConstLRef<AST::GSScopePtr> scope) {
            auto expression = ParseExpression(scope);

            auto expressionStatement = std::make_shared<AST::GS_ExpressionStatement>(expression, scope);

            scope->addNode(expressionStatement);

            return expressionStatement;
        }

        SharedPtr<AST::GS_ExpressionStatement> ParseExpressionStatement(ConstLRef<AST::GSExpressionPtr> expression, ConstLRef<AST::GSScopePtr> scope) {
            auto expressionStatement = std::make_shared<AST::GS_ExpressionStatement>(expression, scope);

            scope->addNode(expressionStatement);

            return expressionStatement;
        }

        AST::GSExpressionPtr ParseExpression(ConstLRef<AST::GSScopePtr> scope) {
            auto expression = ParseLValueExpression(scope);

            if (!expression) {
                expression = ParseRValueExpression(scope);
            }

            return expression;
        }

        AST::GSExpressionPtr ParseLValueExpression(ConstLRef<AST::GSScopePtr> scope) {
            if (IsTokenType(Lexer::TokenType::Identifier)) {
                return ParseVariableUsingExpression(scope);
            }

            return nullptr;
        }

        AST::GSExpressionPtr ParseRValueExpression(ConstLRef<AST::GSScopePtr> scope) {
            auto expression = ParseUnaryExpression(scope);

            return ParseBinaryExpression(0, expression, scope);
        }

        AST::GSExpressionPtr ParseVariableUsingExpression(ConstLRef<AST::GSScopePtr> scope) {
            if (!IsTokenType(Lexer::TokenType::Identifier)) {
                return nullptr;
            }

            auto variableName = TokenValue();

            NextToken();

            return std::make_shared<AST::GS_VariableUsingExpression>(variableName, scope);
        }

        AST::GSExpressionPtr ParseBinaryExpression(I32 expressionPrecedence, LRef<AST::GSExpressionPtr> expression, ConstLRef<AST::GSScopePtr> scope) {
            while (true) {
                auto currentTokenPrecedence = TokenPrecedence();

                if (currentTokenPrecedence < expressionPrecedence) {
                    return expression;
                }

                AST::BinaryOperation binaryOperator;

                switch (TokenType()) {
                    case Lexer::TokenType::SymbolPlus:
                        binaryOperator = AST::BinaryOperation::Plus;

                        break;
                    case Lexer::TokenType::SymbolMinus:
                        binaryOperator = AST::BinaryOperation::Minus;

                        break;
                    case Lexer::TokenType::SymbolStar:
                        binaryOperator = AST::BinaryOperation::Star;

                        break;
                    case Lexer::TokenType::SymbolSlash:
                        binaryOperator = AST::BinaryOperation::Slash;

                        break;
                    default:
                        throw std::runtime_error("Unknown binary operator!");
                }

                NextToken(); // skip binary operator

                auto secondExpression = ParseUnaryExpression(scope);

                auto nextTokenPrecedence = TokenPrecedence();

                if (currentTokenPrecedence < nextTokenPrecedence) {
                    secondExpression = ParseBinaryExpression(currentTokenPrecedence + 1, secondExpression, scope);
                }

                expression = std::make_shared<AST::GS_BinaryExpression>(binaryOperator, expression, secondExpression, scope);
            }
        }

        AST::GSExpressionPtr ParseUnaryExpression(ConstLRef<AST::GSScopePtr> scope) {
            if (IsTokenType(Lexer::TokenType::SymbolMinus)) {
                NextToken(); // skip '-'

                auto constantExpression = ParseConstantExpression(scope);

                return std::make_shared<AST::GS_UnaryExpression>(AST::UnaryOperation::Minus, constantExpression, scope);
            }

            return ParseConstantExpression(scope);
        }

        AST::GSExpressionPtr ParseConstantExpression(ConstLRef<AST::GSScopePtr> scope) {
            if (IsTokenType(Lexer::TokenType::LiteralNumber)) {
                auto tokenValue = std::make_shared<AST::GS_I32Value>(std::stoi(TokenValue().asString())); // TODO create converting from string to number

                NextToken();

                return std::make_shared<AST::GS_ConstantExpression>(tokenValue, scope);
            } else if (IsTokenType(Lexer::TokenType::LiteralString)) {
                auto tokenValue = std::make_shared<AST::GS_StringValue>(TokenValue());

                NextToken();

                return std::make_shared<AST::GS_ConstantExpression>(tokenValue, scope);
            } else if (IsTokenType(Lexer::TokenType::Identifier)) {
                return ParseVariableUsingExpression(scope);
            }

            return nullptr;
        }

        AST::GSTypePtr ParseType() {
            if (!IsTokenType(Lexer::TokenType::Identifier)) {
                return nullptr;
            }

            auto stringVariableType = TokenValue();

            NextToken(); // skip variable type

            AST::GSTypePtr variableType = nullptr;

            if (stringVariableType == U"Void") {
                variableType = std::make_shared<AST::GS_VoidType>();
            } else if (stringVariableType == U"I32") {
                variableType = std::make_shared<AST::GS_I32Type>();
            } else if (stringVariableType == U"String") {
                variableType = std::make_shared<AST::GS_StringType>();
            }

            return variableType;
        }

    public:

        I32 TokenPrecedence() {
            auto precedence = OperatorsPrecedence[TokenType()];

            if (!precedence) {
                return -1;
            }

            return precedence;
        }

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

I32 main() {
    /**
     * func main() {
     *     var a = 10
     * }
     */
    Lexer::GS_TokenStream stream({
        std::make_shared<Lexer::GS_Token>(Lexer::TokenType::KeywordFunc),
        std::make_shared<Lexer::GS_ValueToken>(Lexer::TokenType::Identifier, U"main"),
        std::make_shared<Lexer::GS_Token>(Lexer::TokenType::SymbolLeftParen),
        std::make_shared<Lexer::GS_Token>(Lexer::TokenType::SymbolRightParen),
        std::make_shared<Lexer::GS_Token>(Lexer::TokenType::SymbolLeftBrace),
        std::make_shared<Lexer::GS_Token>(Lexer::TokenType::KeywordVar),
        std::make_shared<Lexer::GS_ValueToken>(Lexer::TokenType::Identifier, U"a"),
        std::make_shared<Lexer::GS_Token>(Lexer::TokenType::SymbolEq),
        std::make_shared<Lexer::GS_ValueToken>(Lexer::TokenType::LiteralNumber, U"10"),
        std::make_shared<Lexer::GS_Token>(Lexer::TokenType::SymbolRightBrace),
        std::make_shared<Lexer::GS_Token>(Lexer::TokenType::EndOfFile),
    });

    New::GS_Parser parser(&stream);

    auto unit = parser.Parse();

    return 0;
}
