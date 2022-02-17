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

#include <Semantic/GS_TableOfSymbols.h>

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

            return std::make_shared<AST::GS_TranslationUnitDeclaration>(nodes, globalScope);
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

/**
 * Constant Folding Visitor
 */

class CFVisitor : public AST::GS_Transformer {
public:

    AST::GSNodePtr visitUnaryExpression(SharedPtr<AST::GS_UnaryExpression> unaryExpression) override {
        AST::GS_Transformer::visitUnaryExpression(unaryExpression);

        auto expression = unaryExpression->getExpression();
        auto operation = unaryExpression->getUnaryOperation();
        auto scope = unaryExpression->getScope();

        if (IsConstantExpression(expression)) {
            auto value = std::reinterpret_pointer_cast<AST::GS_ConstantExpression>(expression)->getValue();

            auto result = Fold(value, operation);

            if (result != nullptr) {
                scope->removeNode(unaryExpression);

                auto newExpression = std::make_shared<AST::GS_ConstantExpression>(result, scope);

                scope->addNode(newExpression);

                return newExpression;
            }
        }
    }

    AST::GSNodePtr visitBinaryExpression(SharedPtr<AST::GS_BinaryExpression> binaryExpression) override {
        AST::GS_Transformer::visitBinaryExpression(binaryExpression);

        auto firstExpression = binaryExpression->getFirstExpression();
        auto secondExpression = binaryExpression->getSecondExpression();
        auto operation = binaryExpression->getBinaryOperation();
        auto &scope = binaryExpression->getScope();

        if (IsConstantExpression(firstExpression) && IsConstantExpression(secondExpression)) {
            auto firstValue = std::reinterpret_pointer_cast<AST::GS_ConstantExpression>(firstExpression)->getValue();
            auto secondValue = std::reinterpret_pointer_cast<AST::GS_ConstantExpression>(secondExpression)->getValue();

            auto result = Fold(firstValue, secondValue, operation);

            if (result != nullptr) {
                scope->removeNode(binaryExpression);

                auto newExpression = std::make_shared<AST::GS_ConstantExpression>(result, scope);

                scope->addNode(newExpression);

                return newExpression;
            }
        }

        return binaryExpression;
    }

private:

    AST::GSValuePtr Fold(ConstLRef<AST::GSValuePtr> value, AST::UnaryOperation operation) {
        if (value->getType()->getName() == U"I32") {
            auto number = value->getValueWithCast<I32>();

            switch (operation) {
                case AST::UnaryOperation::Minus:
                    number = -number;

                    break;
                default:
                    return nullptr;
            }

            return std::make_shared<AST::GS_I32Value>(number);
        }

        return nullptr;
    }

    AST::GSValuePtr Fold(ConstLRef<AST::GSValuePtr> firstValue, ConstLRef<AST::GSValuePtr> secondValue, AST::BinaryOperation operation) {
        if (firstValue->getType()->getName() == U"I32" && secondValue->getType()->getName() == U"I32") {
            auto firstNumber = firstValue->getValueWithCast<I32>();
            auto secondNumber = secondValue->getValueWithCast<I32>();

            I32 result = 0;

            switch (operation) {
                case AST::BinaryOperation::Plus:
                    result = firstNumber + secondNumber;

                    break;
                case AST::BinaryOperation::Minus:
                    result = firstNumber - secondNumber;

                    break;
                case AST::BinaryOperation::Star:
                    result = firstNumber * secondNumber;

                    break;
                case AST::BinaryOperation::Slash:
                    result = firstNumber / secondNumber;

                    break;
                default:
                    return nullptr;
            }

            return std::make_shared<AST::GS_I32Value>(result);
        }

        return nullptr;
    }

    Bool IsConstantExpression(ConstLRef<AST::GSNodePtr> node) {
        if (node->isExpression()) {
            auto expression = std::reinterpret_pointer_cast<AST::GS_Expression>(node);

            if (expression->getExpressionType() == AST::ExpressionType::ConstantExpression) {
                return true;
            }

            return false;
        }

        return false;
    }
};

//class CFTransformer : public AST::GS_Transformer {
//public:
//
//    AST::GSNodePtr visit(SharedPtr<AST::GS_UnaryExpression> unaryExpression) override {
//        Transform(unaryExpression);
//
//        auto expression = unaryExpression->getExpression();
//        auto operation = unaryExpression->getUnaryOperation();
//        auto scope = unaryExpression->getScope();
//
//        if (IsConstantExpression(expression)) {
//            auto value = std::reinterpret_pointer_cast<AST::GS_ConstantExpression>(expression)->getValue();
//
//            auto result = Fold(value, operation);
//
//            if (result != nullptr) {
//                scope->removeNode(unaryExpression);
//
//                auto newExpression = std::make_shared<AST::GS_ConstantExpression>(result, scope);
//
//                scope->addNode(newExpression);
//
//                return newExpression;
//            }
//        }
//
//        return unaryExpression;
//    }
//
//    AST::GSNodePtr visit(SharedPtr<AST::GS_BinaryExpression> binaryExpression) override {
//        Transform(binaryExpression);
//
//        auto firstExpression = binaryExpression->getFirstExpression();
//        auto secondExpression = binaryExpression->getSecondExpression();
//        auto operation = binaryExpression->getBinaryOperation();
//        auto scope = binaryExpression->getScope();
//
//        if (IsConstantExpression(firstExpression) && IsConstantExpression(secondExpression)) {
//            auto firstValue = std::reinterpret_pointer_cast<AST::GS_ConstantExpression>(firstExpression)->getValue();
//            auto secondValue = std::reinterpret_pointer_cast<AST::GS_ConstantExpression>(secondExpression)->getValue();
//
//            auto result = Fold(firstValue, secondValue, operation);
//
//            if (result != nullptr) {
//                scope->removeNode(binaryExpression);
//
//                auto newExpression = std::make_shared<AST::GS_ConstantExpression>(result, scope);
//
//                scope->addNode(newExpression);
//
//                return newExpression;
//            }
//        }
//
//        return binaryExpression;
//    }
//
//private:
//
//    template<typename T>
//    Void Transform(LRef<SharedPtr<T>> node) {
//        auto transformedNode = std::reinterpret_pointer_cast<T>(AST::GS_Transformer::visit(node));
//
//        node.swap(transformedNode);
//    }
//
//    AST::GSValuePtr Fold(ConstLRef<AST::GSValuePtr> value, AST::UnaryOperation operation) {
//        if (value->getType()->getName() == U"I32") {
//            auto number = value->getValueWithCast<I32>();
//
//            switch (operation) {
//                case AST::UnaryOperation::Minus:
//                    number = -number;
//
//                    break;
//                default:
//                    return nullptr;
//            }
//
//            return std::make_shared<AST::GS_I32Value>(number);
//        }
//
//        return nullptr;
//    }
//
//    AST::GSValuePtr Fold(ConstLRef<AST::GSValuePtr> firstValue, ConstLRef<AST::GSValuePtr> secondValue, AST::BinaryOperation operation) {
//        if (firstValue->getType()->getName() == U"I32" && secondValue->getType()->getName() == U"I32") {
//            auto firstNumber = firstValue->getValueWithCast<I32>();
//            auto secondNumber = secondValue->getValueWithCast<I32>();
//
//            I32 result = 0;
//
//            switch (operation) {
//                case AST::BinaryOperation::Plus:
//                    result = firstNumber + secondNumber;
//
//                    break;
//                case AST::BinaryOperation::Minus:
//                    result = firstNumber - secondNumber;
//
//                    break;
//                case AST::BinaryOperation::Star:
//                    result = firstNumber * secondNumber;
//
//                    break;
//                case AST::BinaryOperation::Slash:
//                    result = firstNumber / secondNumber;
//
//                    break;
//                default:
//                    return nullptr;
//            }
//
//            return std::make_shared<AST::GS_I32Value>(result);
//        }
//
//        return nullptr;
//    }
//
//    Bool IsConstantExpression(ConstLRef<AST::GSNodePtr> node) {
//        if (node->isExpression()) {
//            auto expression = std::reinterpret_pointer_cast<AST::GS_Expression>(node);
//
//            if (expression->getExpressionType() == AST::ExpressionType::ConstantExpression) {
//                return true;
//            }
//
//            return false;
//        }
//
//        return false;
//    }
//};

//class PrintVisitor : public AST::GS_BaseVisitor {
//public:
//
//    Void visit(ConstLRef<AST::GSNodePtr> node) override {
//        AST::GS_BaseVisitor::visit(node);
//    }
//
//    Void visit(SharedPtr<AST::GS_TranslationUnitDeclaration> translationUnitDeclaration) override {
//        Print("TranslationUnitDeclaration: {");
//
//        AddTab();
//
//        Print("Nodes: {");
//
//        AddTab();
//
//        for (auto &node : translationUnitDeclaration->getNodes()) {
//            visit(node);
//        }
//
//        SubTab();
//
//        Print("}");
//
//        SubTab();
//
//        Print("}");
//    }
//
//    Void visit(SharedPtr<AST::GS_FunctionDeclaration> functionDeclaration) override {
//        Print("FunctionDeclaration: {");
//
//        AddTab();
//
//        Print("Name: " + functionDeclaration->getName().asString());
//
//        Print("Body: {");
//
//        AddTab();
//
//        for (auto &statement : functionDeclaration->getBody()) {
//            visit(statement);
//        }
//
//        SubTab();
//
//        Print("}");
//
//        SubTab();
//
//        Print("}");
//    }
//
//    Void visit(SharedPtr<AST::GS_VariableDeclarationStatement> variableDeclarationStatement) override {
//        Print("VariableDeclarationStatement: {");
//
//        AddTab();
//
//        Print("Name: " + variableDeclarationStatement->getName().asString());
//
//        Print("Type: " + variableDeclarationStatement->getType()->getName().asString());
//
//        Print("Expression: {");
//
//        AddTab();
//
//        visit(variableDeclarationStatement->getExpression());
//
//        SubTab();
//
//        Print("}");
//
//        SubTab();
//
//        Print("}");
//    }
//
//    Void visit(SharedPtr<AST::GS_AssignmentStatement> assignmentStatement) override {
//        Print("AssignmentStatement: {");
//
//        AddTab();
//
//        Print("LValueExpression: {");
//
//        AddTab();
//
//        visit(assignmentStatement->getLValueExpression());
//
//        SubTab();
//
//        Print("}");
//
//        Print("RValueExpression: {");
//
//        AddTab();
//
//        visit(assignmentStatement->getRValueExpression());
//
//        SubTab();
//
//        Print("}");
//
//        SubTab();
//
//        Print("}");
//    }
//
//    Void visit(SharedPtr<AST::GS_ExpressionStatement> expressionStatement) override {
//        Print("ExpressionStatement: {");
//
//        AddTab();
//
//        visit(expressionStatement->getExpression());
//
//        SubTab();
//
//        Print("}");
//    }
//
//    Void visit(SharedPtr<AST::GS_ConstantExpression> constantExpression) override {
//        Print("ConstantExpression: {");
//
//        AddTab();
//
//        Print("Value: {");
//
//        AddTab();
//
//        auto value = constantExpression->getValue();
//        auto typeName = value->getType()->getName();
//
//        Print("Type: " + typeName.asString());
//
//        if (typeName == U"I32") {
//            Print("Value: " + std::to_string(value->getValueWithCast<I32>()));
//        } else if (typeName == U"String") {
//            Print("Value: " + value->getValueWithCast<UString>().asString());
//        }
//
//        SubTab();
//
//        Print("}");
//
//        SubTab();
//
//        Print("}");
//    }
//
//    Void visit(SharedPtr<AST::GS_UnaryExpression> unaryExpression) override {
//        Print("UnaryExpression: {");
//
//        AddTab();
//
//        Print("Expression: {");
//
//        AddTab();
//
//        visit(unaryExpression->getExpression());
//
//        SubTab();
//
//        Print("}");
//
//        auto operation = unaryExpression->getUnaryOperation();
//
//        String stringOperation;
//
//        switch (operation) {
//            case AST::UnaryOperation::Minus:
//                stringOperation = "Minus (-)";
//
//                break;
//        }
//
//        Print("Operation: " + stringOperation);
//
//        SubTab();
//
//        Print("}");
//    }
//
//    Void visit(SharedPtr<AST::GS_BinaryExpression> binaryExpression) override {
//        Print("BinaryExpression: {");
//
//        AddTab();
//
//        Print("FirstExpression: {");
//
//        AddTab();
//
//        visit(binaryExpression->getFirstExpression());
//
//        SubTab();
//
//        Print("}");
//
//        Print("SecondExpression: {");
//
//        AddTab();
//
//        visit(binaryExpression->getSecondExpression());
//
//        SubTab();
//
//        Print("}");
//
//        auto operation = binaryExpression->getBinaryOperation();
//
//        String stringOperation;
//
//        switch (operation) {
//            case AST::BinaryOperation::Plus:
//                stringOperation = "Plus (+)";
//
//                break;
//            case AST::BinaryOperation::Minus:
//                stringOperation = "Minus (-)";
//
//                break;
//            case AST::BinaryOperation::Star:
//                stringOperation = "Star (*)";
//
//                break;
//            case AST::BinaryOperation::Slash:
//                stringOperation = "Slash (/)";
//
//                break;
//        }
//
//        Print("Operation: " + stringOperation);
//
//        SubTab();
//
//        Print("}");
//    }
//
//    Void visit(SharedPtr<AST::GS_VariableUsingExpression> variableUsingExpression) override {
//        Print("VariableUsingExpression: {");
//
//        AddTab();
//
//        Print("Name: " + variableUsingExpression->getName().asString());
//
//        SubTab();
//
//        Print("}");
//    }
//
//    Void visit(SharedPtr<AST::GS_FunctionCallingExpression> functionCallingExpression) override {
//        Print("FunctionCallingExpression: {");
//
//        AddTab();
//
//        Print("Name: " + functionCallingExpression->getName().asString());
//
//        Print("Params: {");
//
//        AddTab();
//
//        for (auto &param : functionCallingExpression->getParams()) {
//            visit(param);
//        }
//
//        SubTab();
//
//        Print("}");
//
//        SubTab();
//
//        Print("}");
//    }
//
//private:
//
//    Void Print(String message) {
//        PrintTabs();
//
//        std::cout << message << std::endl;
//    }
//
//    Void PrintTabs() {
//        for (auto i = 0; i < tabsNumber; ++i) {
//            std::cout << "  ";
//        }
//    }
//
//    Void AddTab() {
//        ++tabsNumber;
//    }
//
//    Void SubTab() {
//        --tabsNumber;
//    }
//
//private:
//
//    I32 tabsNumber = 0;
//};

/**
 * Symbols Placeholder Visitor
 */

//class SPVisitor : public AST::GS_BaseVisitor {
//public:
//
//    Void visit(SharedPtr<AST::GS_FunctionDeclaration> functionDeclaration) override {
//        auto name = functionDeclaration->getName();
//        auto body = functionDeclaration->getBody();
//        auto scope = functionDeclaration->getScope();
//        auto tableOfSymbols = scope->getTableOfSymbols();
//
//        tableOfSymbols->addFunction(name, body);
//    }
//
//    Void visit(SharedPtr<AST::GS_VariableDeclarationStatement> variableDeclarationStatement) override {
//        auto name = variableDeclarationStatement->getName();
//        auto type = variableDeclarationStatement->getType();
//        auto expression = variableDeclarationStatement->getExpression();
//        auto scope = variableDeclarationStatement->getScope();
//        auto tableOfSymbols = scope->getTableOfSymbols();
//
//        tableOfSymbols->addVariable(name, type, expression);
//    }
//};

//class TPVisitor : public AST::GS_BaseVisitor {
//public:
//
//    AST::GSTypePtr CalculateType(ConstLRef<AST::GSExpressionPtr> expression) {
//        switch (expression->getExpressionType()) {
//            case AST::ExpressionType::ConstantExpression: {
//                auto constantExpression = std::reinterpret_pointer_cast<AST::GS_ConstantExpression>(expression);
//
//                return constantExpression->getValue()->getType();
//            }
//            case AST::ExpressionType::UnaryExpression: {
//                auto unaryExpression = std::reinterpret_pointer_cast<AST::GS_UnaryExpression>(expression);
//
//                return CalculateType(unaryExpression->getExpression());
//            }
//            case AST::ExpressionType::BinaryExpression: {
//                auto binaryExpression = std::reinterpret_pointer_cast<AST::GS_BinaryExpression>(expression);
//
//                auto firstType = CalculateType(binaryExpression->getFirstExpression());
//                auto secondType = CalculateType(binaryExpression->getSecondExpression());
//
//                if (firstType->getName() == secondType->getName()) {
//                    return firstType;
//                }
//
//                return nullptr;
//            }
//            case AST::ExpressionType::VariableUsingExpression: {
//                auto variableUsingExpression = std::reinterpret_pointer_cast<AST::GS_VariableUsingExpression>(expression);
//
//                auto tableOfSymbols = variableUsingExpression->getScope()->getTableOfSymbols();
//
//                if (auto variable = tableOfSymbols->getVariable(variableUsingExpression->getName())) {
//                    return variable->getType();
//                }
//
//                return nullptr;
//            }
//            case AST::ExpressionType::FunctionCallingExpression: {
//                return nullptr;
//            }
//            default:
//                return nullptr;
//        }
//    }
//
//public:
//
//    Void visit(SharedPtr<AST::GS_VariableDeclarationStatement> variableDeclarationStatement) override {
//        auto &type = variableDeclarationStatement->getType();
//        auto expression = variableDeclarationStatement->getExpression();
//
//        if (type == nullptr) {
//            type = CalculateType(expression);
//        }
//    }
//};

I32 main() {
    UFileStream file;
    file.Open(U"../../test.gs", in_mode);

    Reader::GS_Reader reader(&file);

    Reader::GS_TextStream textStream(&reader);

    Lexer::GS_Lexer lexer(&textStream);

    Lexer::GSTokenPtrArray tokens;

    Lexer::GSTokenPtr token = lexer.getToken();

    while (token != nullptr) {
        if (token->getTokenType() == Lexer::TokenType::SymbolSpace) {
            token = lexer.getToken();

            continue;
        }

        tokens.emplace_back(token);

        token = lexer.getToken();
    }

    tokens.emplace_back(std::make_shared<Lexer::GS_Token>(Lexer::TokenType::EndOfFile));

    Lexer::GS_TokenStream tokenStream(tokens);

    New::GS_Parser parser(&tokenStream);

    auto unit = parser.Parse();

    CFVisitor v;
    v.visitTranslationUnitDeclaration(unit);

    return 0;
}
