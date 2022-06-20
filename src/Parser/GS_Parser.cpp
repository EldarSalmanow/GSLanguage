#include <map>

#include <GS_Parser.h>
#include <functional>

namespace GSLanguageCompiler::Parser {

    std::map<Lexer::TokenType, I32> OperatorsPrecedence = {
            {Lexer::TokenType::SymbolStar,  2},
            {Lexer::TokenType::SymbolSlash, 2},
            {Lexer::TokenType::SymbolPlus,  1},
            {Lexer::TokenType::SymbolMinus, 1}
    };

    GS_Parser::GS_Parser(LRef<Lexer::GS_TokenStream> tokenStream, AST::GSASTContextPtr context, IO::GSMessageHandlerPtr messageHandler)
            : _stream(tokenStream),
              _context(std::move(context)),
              _builder(AST::GS_ASTBuilder::Create(_context)),
              _messageHandler(std::move(messageHandler)) {}

    GS_Parser GS_Parser::Create(LRef<Lexer::GS_TokenStream> tokenStream, AST::GSASTContextPtr context, IO::GSMessageHandlerPtr messageHandler) {
        return GS_Parser(tokenStream, std::move(context), std::move(messageHandler));
    }

    GS_Parser GS_Parser::Create(LRef<Lexer::GS_TokenStream> tokenStream, IO::GSMessageHandlerPtr messageHandler) {
        return GS_Parser::Create(tokenStream, AST::GS_ASTContext::Create(), std::move(messageHandler));
    }

    GS_Parser GS_Parser::Create(LRef<Lexer::GS_TokenStream> tokenStream) {
        return GS_Parser::Create(tokenStream, AST::GS_ASTContext::Create(), IO::GS_MessageHandler::Create());
    }

    AST::GSTranslationUnitDeclarationPtr GS_Parser::Parse() {
        return ParseTranslationUnitDeclaration();
    }

    AST::GSTranslationUnitDeclarationPtr GS_Parser::ParseTranslationUnitDeclaration() {
        auto unit = _builder->CreateTranslationUnitDeclaration(TokenLocation().GetStartLocation().GetSourceName());

        while (!IsTokenType(Lexer::TokenType::EndOfFile)) {
            auto declaration = ParseDeclaration();

            if (!declaration) {
                return nullptr;
            }

            unit->AddNode(declaration);
        }

        return unit;
    }

    AST::GSDeclarationPtr GS_Parser::ParseDeclaration() {
        if (IsTokenType(Lexer::TokenType::KeywordFunc)) {
            return ParseFunctionDeclaration();
        }

        return nullptr;
    }

    std::shared_ptr<AST::GS_FunctionDeclaration> GS_Parser::ParseFunctionDeclaration() {
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

        auto function = _builder->CreateFunctionDeclaration(functionName);

        while (!IsTokenType(Lexer::TokenType::SymbolRightBrace)) {
            auto statement = ParseStatement();

            function->AddStatement(statement);
        }

        NextToken(); // skip '}'

        return function;
    }

    AST::GSStatementPtr GS_Parser::ParseStatement() {
        AST::GSStatementPtr statement;

        statement = TryParse(&GS_Parser::ParseVariableDeclarationStatement);

        if (statement) {
            return statement;
        }

        statement = TryParse(&GS_Parser::ParseAssignmentStatement);

        if (statement) {
            return statement;
        }

        return ParseExpressionStatement();
    }

    std::shared_ptr<AST::GS_AssignmentStatement> GS_Parser::ParseAssignmentStatement() {
        auto lvalueExpression = ParseLValueExpression();

        if (!IsTokenType(Lexer::TokenType::SymbolEq)) {
            return nullptr;
        }

        NextToken(); // skip '='

        auto rvalueExpression = ParseRValueExpression();

        auto assignmentStatement = _builder->CreateAssignmentStatement(lvalueExpression, rvalueExpression);

        return assignmentStatement;
    }

    std::shared_ptr<AST::GS_VariableDeclarationStatement> GS_Parser::ParseVariableDeclarationStatement() {
        UString variableName;
        Semantic::GSTypePtr variableType;
        AST::GSExpressionPtr variableExpression;

        if (!IsTokenType(Lexer::TokenType::KeywordVar)) {
            return nullptr;
        }

        NextToken(); // skip 'var'

        if (!IsTokenType(Lexer::TokenType::Identifier)) {
            return nullptr;
        }

        variableName = TokenValue();

        NextToken(); // skip variable name

        if (IsTokenType(Lexer::TokenType::SymbolColon)) {
            NextToken(); // skip ':'

            variableType = ParseType();
        }

        if (!IsTokenType(Lexer::TokenType::SymbolEq)) {
            return nullptr;
        }

        NextToken(); // skip '='

        variableExpression = ParseRValueExpression();

        auto variable = _builder->CreateVariableDeclarationStatement(variableName, variableType, variableExpression);

        return variable;
    }

    std::shared_ptr<AST::GS_ExpressionStatement> GS_Parser::ParseExpressionStatement() {
        auto expression = ParseExpression();

        auto expressionStatement = _builder->CreateExpressionStatement(expression);

        return expressionStatement;
    }

    template<typename T>
    class Result {
    public:

        Result()
                : _hasValue(false) {}

        explicit Result(T value)
                : _value(value), _hasValue(true) {}

    public:

        static Result<T> Create(T value) {
            return Result<T>(value);
        }

        static Result<T> Create() {
            return Result<T>();
        }

    public:

        Result<T> Then(std::function<T()> function) const {
            if (!HasValue()) {
                return *this;
            }

            auto result = function();

            return Result<T>::Create(result);
        }

    public:

        inline T Value() const {
            return _value;
        }

        inline Bool HasValue() const {
            return _hasValue;
        }

    public:

        inline operator Bool() const {
            return HasValue();
        }

    private:

        T _value;

        Bool _hasValue;
    };

    template<>
    class Result<void> {
    public:

        Result()
                : _hasValue(true) {}

    public:

        static Result<void> Create() {
            return Result<void>();
        }

    public:

        Result<void> Then(std::function<void()> function) const {
            if (!HasValue()) {
                return *this;
            }

            function();

            return Result<void>::Create();
        }

    public:

        inline Bool HasValue() const {
            return _hasValue;
        }

    public:

        inline operator Bool() const {
            return _hasValue;
        }

    private:

        Bool _hasValue;
    };

    template<typename T>
    Result<T> Run(std::function<T()> function) {
        auto result = function();

        return Result<T>::Create(result);
    }

    template<>
    Result<void> Run<void>(std::function<void()> function) {
        function();

        return Result<void>::Create();
    }

    void f() {
        auto result = Run(std::function([] () {
            if (1 > 0) {
                return 1;
            } else {
                return 0;
            }
        })).Then(std::function([] () {
            if (2 > 0) {
                return 2;
            } else {
                return 1;
            }
        }));
    }

    AST::GSExpressionPtr GS_Parser::ParseExpression() {
        AST::GSExpressionPtr expression;

        expression = TryParse(&GS_Parser::ParseRValueExpression);

        if (expression) {
            return expression;
        }

        expression = TryParse(&GS_Parser::ParseLValueExpression);

        if (expression) {
            return expression;
        }

        return nullptr;
    }

    AST::GSExpressionPtr GS_Parser::ParseLValueExpression() {
        if (IsTokenType(Lexer::TokenType::Identifier)) {
            return ParseVariableUsingExpression();
        }

        return nullptr;
    }

    AST::GSExpressionPtr GS_Parser::ParseVariableUsingExpression() {
        if (!IsTokenType(Lexer::TokenType::Identifier)) {
            return nullptr;
        }

        auto variableName = TokenValue();
        auto variableNameLocation = TokenLocation();

        NextToken(); // skip variable name

        return _builder->CreateVariableUsingExpression(variableName, variableNameLocation);
    }

    /*
     *
     * unary_expr
     *
     * binary_expr
     *
     * primary_expr
     *
     * -(f() + -(f() + f()))
     *
     */

    AST::GSExpressionPtr GS_Parser::ParseRValueExpression() {
        auto expression = ParseUnaryExpression();

        return ParseBinaryExpression(0, expression);
    }

    AST::GSExpressionPtr GS_Parser::ParseConstantExpression() {
        auto value = ParseValue();

        if (!value) {
            return nullptr;
        }

        return _builder->CreateConstantExpression(value);
    }

    AST::GSExpressionPtr GS_Parser::ParseUnaryExpression() {
        if (IsTokenType(Lexer::TokenType::SymbolMinus)) {
            NextToken(); // skip '-'

            auto expression = ParseExpression();

            return _builder->CreateUnaryExpression(AST::UnaryOperation::Minus, expression);
        }

        return ParseExpression();
    }

    AST::GSExpressionPtr GS_Parser::ParseBinaryExpression(I32 expressionPrecedence, LRef<AST::GSExpressionPtr> expression) {
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
//                    AddError("Unknown binary operator!"_us);

                    return nullptr;
            }

            NextToken(); // skip binary operator

            auto secondExpression = ParseExpression();

            auto nextTokenPrecedence = TokenPrecedence();

            if (currentTokenPrecedence < nextTokenPrecedence) {
                secondExpression = ParseBinaryExpression(currentTokenPrecedence + 1, secondExpression);
            }

            expression = _builder->CreateBinaryExpression(binaryOperator, expression, secondExpression);
        }
    }

    AST::GSExpressionPtr GS_Parser::ParseFunctionCallingExpression() {
        if (!IsTokenType(Lexer::TokenType::Identifier)) {
            return nullptr;
        }

        auto name = TokenValue();

        NextToken(); // skip function name

        if (!IsTokenType(Lexer::TokenType::SymbolLeftParen)) {
            return nullptr;
        }

        AST::GSExpressionPtrArray params;

        while (!IsTokenType(Lexer::TokenType::SymbolRightParen)) {
            auto param = ParseExpression();

            params.emplace_back(param);
        }

        return _builder->CreateFunctionCallingExpression(name, params);
    }

    AST::GSExpressionPtr GS_Parser::ParsePrimaryExpression() {
        AST::GSExpressionPtr expression;
    }

    AST::GSValuePtr GS_Parser::ParseValue() {
        if (IsTokenType(Lexer::TokenType::LiteralNumber)) {
            auto number = std::stoi(TokenValue().AsUTF8());

            NextToken(); // skip number

            return _builder->CreateI32Value(number);
        } else if (IsTokenType(Lexer::TokenType::LiteralString)) {
            auto string = TokenValue();

            NextToken(); // skip string

            return _builder->CreateStringValue(string);
        }

        return nullptr;
    }

    Semantic::GSTypePtr GS_Parser::ParseType() {
        if (!IsTokenType(Lexer::TokenType::Identifier)) {
            return nullptr;
        }

        auto stringVariableType = TokenValue();

        NextToken(); // skip variable type

        Semantic::GSTypePtr variableType;

        if (stringVariableType == "Void"_us) {
            variableType = _builder->CreateVoidType();
        } else if (stringVariableType == "I32"_us) {
            variableType = _builder->CreateI32Type();
        } else if (stringVariableType == "String"_us) {
            variableType = _builder->CreateStringType();
        } else {
            variableType = _builder->CreateType(stringVariableType);
        }

        return variableType;
    }

    I32 GS_Parser::TokenPrecedence() {
        auto precedence = OperatorsPrecedence[TokenType()];

        if (!precedence) {
            return -1;
        }

        return precedence;
    }

    Bool GS_Parser::IsTokenType(Lexer::TokenType type) {
        return TokenType() == type;
    }

    Lexer::GS_Token GS_Parser::CurrentToken() {
        return _stream.CurrentToken();
    }

    Lexer::TokenType GS_Parser::TokenType() {
        return CurrentToken().GetType();
    }

    UString GS_Parser::TokenValue() {
        return CurrentToken().GetValue();
    }

    Lexer::GS_TokenLocation GS_Parser::TokenLocation() {
        return CurrentToken().GetLocation();
    }

    Void GS_Parser::NextToken() {
        _stream.NextToken();
    }

    Void GS_Parser::AddError(UString error) {
        _messageHandler->Print(std::move(error), IO::MessageLevel::Error);
    }

}