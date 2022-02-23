//#include <rapidjson/document.h>

//#include <Reader/Reader.h>
#include <Lexer/Lexer.h>
//#include <Parser/Parser.h>
#include <AST/AST.h>
#include <CodeGenerator/CodeGenerator.h>

#include <GS_TranslationUnit.h>

namespace GSLanguageCompiler::Driver {

    class CFVisitor : public AST::GS_Transformer {
    public:

        AST::GSNodePtr visitUnaryExpression(SharedPtr<AST::GS_UnaryExpression> unaryExpression) override {
            unaryExpression = std::reinterpret_pointer_cast<AST::GS_UnaryExpression>(AST::GS_Transformer::visitUnaryExpression(unaryExpression));

            auto expression = unaryExpression->getExpression();
            auto operation = unaryExpression->getUnaryOperation();
            auto scope = unaryExpression->getScope();

            if (IsConstantExpression(expression)) {
                auto value = std::reinterpret_pointer_cast<AST::GS_ConstantExpression>(expression)->getValue();

                auto result = Fold(value, operation);

                if (result != nullptr) {
                    auto newExpression = std::make_shared<AST::GS_ConstantExpression>(result, scope);

                    scope->replaceNode(unaryExpression, newExpression);

                    return newExpression;
                }
            }

            return unaryExpression;
        }

        AST::GSNodePtr visitBinaryExpression(SharedPtr<AST::GS_BinaryExpression> binaryExpression) override {
            binaryExpression = std::reinterpret_pointer_cast<AST::GS_BinaryExpression>(AST::GS_Transformer::visitBinaryExpression(binaryExpression));

            auto firstExpression = binaryExpression->getFirstExpression();
            auto secondExpression = binaryExpression->getSecondExpression();
            auto operation = binaryExpression->getBinaryOperation();
            auto &scope = binaryExpression->getScope();

            if (IsConstantExpression(firstExpression) && IsConstantExpression(secondExpression)) {
                auto firstValue = std::reinterpret_pointer_cast<AST::GS_ConstantExpression>(firstExpression)->getValue();
                auto secondValue = std::reinterpret_pointer_cast<AST::GS_ConstantExpression>(secondExpression)->getValue();

                auto result = Fold(firstValue, secondValue, operation);

                if (result != nullptr) {
                    auto newExpression = std::make_shared<AST::GS_ConstantExpression>(result, scope);

                    scope->replaceNode(binaryExpression, newExpression);

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

    class PrintVisitor : public AST::GS_Visitor {
    public:

        Void visitTranslationUnitDeclaration(SharedPtr<AST::GS_TranslationUnitDeclaration> translationUnitDeclaration) override {
            Print("TranslationUnitDeclaration: {");

            AddTab();

            Print("Nodes: {");

            AddTab();

            for (auto &node: translationUnitDeclaration->getNodes()) {
                visitNode(node);
            }

            SubTab();

            Print("}");

            SubTab();

            Print("}");
        }

        Void visitFunctionDeclaration(SharedPtr<AST::GS_FunctionDeclaration> functionDeclaration) override {
            Print("FunctionDeclaration: {");

            AddTab();

            Print("Name: " + functionDeclaration->getName().asString());

            Print("Body: {");

            AddTab();

            for (auto &statement: functionDeclaration->getBody()) {
                visitStatement(statement);
            }

            SubTab();

            Print("}");

            SubTab();

            Print("}");
        }

        Void visitVariableDeclarationStatement(SharedPtr<AST::GS_VariableDeclarationStatement> variableDeclarationStatement) override {
            Print("VariableDeclarationStatement: {");

            AddTab();

            Print("Name: " + variableDeclarationStatement->getName().asString());

            Print("Type: " + variableDeclarationStatement->getType()->getName().asString());

            Print("Expression: {");

            AddTab();

            visitExpression(variableDeclarationStatement->getExpression());

            SubTab();

            Print("}");

            SubTab();

            Print("}");
        }

        Void visitAssignmentStatement(SharedPtr<AST::GS_AssignmentStatement> assignmentStatement) override {
            Print("AssignmentStatement: {");

            AddTab();

            Print("LValueExpression: {");

            AddTab();

            visitExpression(assignmentStatement->getLValueExpression());

            SubTab();

            Print("}");

            Print("RValueExpression: {");

            AddTab();

            visitExpression(assignmentStatement->getRValueExpression());

            SubTab();

            Print("}");

            SubTab();

            Print("}");
        }

        Void visitExpressionStatement(SharedPtr<AST::GS_ExpressionStatement> expressionStatement) override {
            Print("ExpressionStatement: {");

            AddTab();

            visitExpression(expressionStatement->getExpression());

            SubTab();

            Print("}");
        }

        Void visitConstantExpression(SharedPtr<AST::GS_ConstantExpression> constantExpression) override {
            Print("ConstantExpression: {");

            AddTab();

            Print("Value: {");

            AddTab();

            auto value = constantExpression->getValue();
            auto typeName = value->getType()->getName();

            Print("Type: " + typeName.asString());

            if (typeName == U"I32") {
                Print("Value: " + std::to_string(value->getValueWithCast<I32>()));
            } else if (typeName == U"String") {
                Print("Value: " + value->getValueWithCast<UString>().asString());
            }

            SubTab();

            Print("}");

            SubTab();

            Print("}");
        }

        Void visitUnaryExpression(SharedPtr<AST::GS_UnaryExpression> unaryExpression) override {
            Print("UnaryExpression: {");

            AddTab();

            Print("Expression: {");

            AddTab();

            visitExpression(unaryExpression->getExpression());

            SubTab();

            Print("}");

            auto operation = unaryExpression->getUnaryOperation();

            String stringOperation;

            switch (operation) {
                case AST::UnaryOperation::Minus:
                    stringOperation = "Minus (-)";

                    break;
            }

            Print("Operation: " + stringOperation);

            SubTab();

            Print("}");
        }

        Void visitBinaryExpression(SharedPtr<AST::GS_BinaryExpression> binaryExpression) override {
            Print("BinaryExpression: {");

            AddTab();

            Print("FirstExpression: {");

            AddTab();

            visitExpression(binaryExpression->getFirstExpression());

            SubTab();

            Print("}");

            Print("SecondExpression: {");

            AddTab();

            visitExpression(binaryExpression->getSecondExpression());

            SubTab();

            Print("}");

            auto operation = binaryExpression->getBinaryOperation();

            String stringOperation;

            switch (operation) {
                case AST::BinaryOperation::Plus:
                    stringOperation = "Plus (+)";

                    break;
                case AST::BinaryOperation::Minus:
                    stringOperation = "Minus (-)";

                    break;
                case AST::BinaryOperation::Star:
                    stringOperation = "Star (*)";

                    break;
                case AST::BinaryOperation::Slash:
                    stringOperation = "Slash (/)";

                    break;
            }

            Print("Operation: " + stringOperation);

            SubTab();

            Print("}");
        }

        Void visitVariableUsingExpression(SharedPtr<AST::GS_VariableUsingExpression> variableUsingExpression) override {
            Print("VariableUsingExpression: {");

            AddTab();

            Print("Name: " + variableUsingExpression->getName().asString());

            SubTab();

            Print("}");
        }

        Void visitFunctionCallingExpression(SharedPtr<AST::GS_FunctionCallingExpression> functionCallingExpression) override {
            Print("FunctionCallingExpression: {");

            AddTab();

            Print("Name: " + functionCallingExpression->getName().asString());

            Print("Params: {");

            AddTab();

            for (auto &param: functionCallingExpression->getParams()) {
                visitExpression(param);
            }

            SubTab();

            Print("}");

            SubTab();

            Print("}");
        }

    private:

        Void Print(String message) {
            PrintTabs();

            std::cout << message << std::endl;
        }

        Void PrintTabs() {
            for (auto i = 0; i < tabsNumber; ++i) {
                std::cout << "  ";
            }
        }

        Void AddTab() {
            ++tabsNumber;
        }

        Void SubTab() {
            --tabsNumber;
        }

    private:

        I32 tabsNumber = 0;
    };

    class PrintASTPass : public AST::GS_Pass {
    public:

        PrintASTPass()
                : AST::GS_Pass(std::make_shared<PrintVisitor>()) {}
    };

    class ConstantFoldingASTPass : public AST::GS_Pass {
    public:

        ConstantFoldingASTPass()
                : AST::GS_Pass(std::make_shared<CFVisitor>()) {}
    };

    UString tokenTypeToString(Lexer::TokenType type) {
        UString tokenTypesAsString[] = {
            #define GS_TOKENTYPE(name) U#name

            #include <Lexer/GS_Keywords.def>
        };

        return tokenTypesAsString[StaticCast<I32>(type)];
    }

    GS_TranslationUnit::GS_TranslationUnit(UString name)
            : _name(std::move(name)) {}

    I32 GS_TranslationUnit::compile() {
//        UFileStream file;
//        file.Open(U"../../test.gs", in_mode);
//
//        Reader::GS_Reader reader(&file);
//
//        Reader::GS_TextStream textStream(&reader);
//
//        Lexer::GS_Lexer lexer(&textStream);
//
//        Lexer::GSTokenPtrArray tokens;
//
//        Lexer::GSTokenPtr token = lexer.getToken();
//
//        while (token != nullptr) {
//            if (token->getTokenType() == Lexer::TokenType::SymbolSpace) {
//                token = lexer.getToken();
//
//                continue;
//            }
//
//            tokens.emplace_back(token);
//
//            token = lexer.getToken();
//        }
//
//        tokens.emplace_back(std::make_shared<Lexer::GS_Token>(Lexer::TokenType::EndOfFile));
//
//        Lexer::GS_TokenStream tokenStream(tokens);
//
//        New::GS_Parser parser(&tokenStream);

        auto globalScope = std::make_shared<AST::GS_Scope>(nullptr);

        auto function = std::make_shared<AST::GS_FunctionDeclaration>(U"main", globalScope);

        auto number_1 = std::make_shared<AST::GS_ConstantExpression>(std::make_shared<AST::GS_I32Value>(1),
                                                                     function->getFunctionScope());
        auto number_2 = std::make_shared<AST::GS_ConstantExpression>(std::make_shared<AST::GS_I32Value>(5),
                                                                     function->getFunctionScope());

        function->addStatement(std::make_shared<AST::GS_VariableDeclarationStatement>(U"a",
                                                                                      std::make_shared<AST::GS_I32Type>(),
                                                                                      std::make_shared<AST::GS_BinaryExpression>(
                                                                                              AST::BinaryOperation::Plus,
                                                                                              number_1, number_2,
                                                                                              function->getFunctionScope()),
                                                                                      function->getFunctionScope()));

        AST::GSNodePtrArray nodes = {
                function
        };

        auto unit = std::make_shared<AST::GS_TranslationUnitDeclaration>(nodes, globalScope);

        PrintASTPass printer;
        ConstantFoldingASTPass folder;

        printer.run({unit});

        folder.run({unit});

        printer.run({unit});

        return 0;
    }

    UString GS_TranslationUnit::getName() const {
        return _name;
    }

}
