#include <AST/AST.h>

#include <GS_ASTDumper.h>

namespace GSLanguageCompiler::Debug {

    // TODO update AST dump visitor

    class GS_ASTDumpVisitor : public AST::GS_Visitor {
    public:

        Void VisitTranslationUnitDeclaration(LRef<std::shared_ptr<AST::GS_TranslationUnitDeclaration>> translationUnitDeclaration) override {
            Print("TranslationUnitDeclaration: {"_us);

            AddTab();

            Print("Name: "_us + translationUnitDeclaration->GetName());

            Print("Nodes: {"_us);

            AddTab();

            for (auto &node : translationUnitDeclaration->GetNodes()) {
                VisitNode(node);
            }

            SubTab();

            Print("}"_us);

            SubTab();

            Print("}"_us);
        }

        Void VisitFunctionDeclaration(LRef<std::shared_ptr<AST::GS_FunctionDeclaration>> functionDeclaration) override {
            Print("FunctionDeclaration: {"_us);

            AddTab();

            Print("Name: "_us + functionDeclaration->GetName());

            auto signature = functionDeclaration->GetSignature();

            auto paramTypes = signature.GetParamTypes();
            auto returnType = signature.GetReturnType();

            auto signatureMessage = "Signature: ("_us;

            for (auto &paramType : paramTypes) {
                signatureMessage += paramType->GetName() + " "_us;
            }

            signatureMessage += ") -> "_us + returnType->GetName();

            Print(signatureMessage);

            Print("Body: {"_us);

            AddTab();

            for (auto &statement : functionDeclaration->GetBody()) {
                VisitStatement(statement);
            }

            SubTab();

            Print("}"_us);

            SubTab();

            Print("}"_us);
        }

        Void VisitVariableDeclarationStatement(LRef<std::shared_ptr<AST::GS_VariableDeclarationStatement>> variableDeclarationStatement) override {
            Print("VariableDeclarationStatement: {"_us);

            AddTab();

            Print("Name: "_us + variableDeclarationStatement->GetName());

            Print("Type: "_us + variableDeclarationStatement->GetType()->GetName());

            Print("Expression: {"_us);

            AddTab();

            VisitExpression(variableDeclarationStatement->GetExpression());

            SubTab();

            Print("}"_us);

            SubTab();

            Print("}"_us);
        }

        Void VisitAssignmentStatement(LRef<std::shared_ptr<AST::GS_AssignmentStatement>> assignmentStatement) override {
            Print("AssignmentStatement: {"_us);

            AddTab();

            Print("LValueExpression: {"_us);

            AddTab();

            VisitExpression(assignmentStatement->GetLValueExpression());

            SubTab();

            Print("}"_us);

            Print("RValueExpression: {"_us);

            AddTab();

            VisitExpression(assignmentStatement->GetRValueExpression());

            SubTab();

            Print("}"_us);

            SubTab();

            Print("}"_us);
        }

        Void VisitExpressionStatement(LRef<std::shared_ptr<AST::GS_ExpressionStatement>> expressionStatement) override {
            Print("ExpressionStatement: {"_us);

            AddTab();

            VisitExpression(expressionStatement->GetExpression());

            SubTab();

            Print("}"_us);
        }

        Void VisitConstantExpression(LRef<std::shared_ptr<AST::GS_ConstantExpression>> constantExpression) override {
            Print("ConstantExpression: {"_us);

            AddTab();

            Print("Value: {"_us);

            AddTab();

            auto value = AST::GSValueCast<AST::GS_LiteralValue>(constantExpression->GetValue());
            auto typeName = value->GetType()->GetName();

            Print("Type: " + typeName.AsUTF8String());

            if (typeName == "I32"_us) {
                Print("Value: "_us + UString(std::to_string(value->GetValueWithCast<I32>())));
            } else if (typeName == "String"_us) {
                Print("Value: "_us + value->GetValueWithCast<UString>());
            }

            SubTab();

            Print("}"_us);

            SubTab();

            Print("}"_us);
        }

        Void VisitUnaryExpression(LRef<std::shared_ptr<AST::GS_UnaryExpression>> unaryExpression) override {
            Print("UnaryExpression: {"_us);

            AddTab();

            Print("Expression: {"_us);

            AddTab();

            VisitExpression(unaryExpression->GetExpression());

            SubTab();

            Print("}"_us);

            auto operation = unaryExpression->GetUnaryOperation();

            UString stringOperation;

            switch (operation) {
                case AST::UnaryOperation::Minus:
                    stringOperation = "Minus (-)"_us;

                    break;
            }

            Print("Operation: "_us + stringOperation);

            SubTab();

            Print("}"_us);
        }

        Void VisitBinaryExpression(LRef<std::shared_ptr<AST::GS_BinaryExpression>> binaryExpression) override {
            Print("BinaryExpression: {"_us);

            AddTab();

            Print("FirstExpression: {"_us);

            AddTab();

            VisitExpression(binaryExpression->GetFirstExpression());

            SubTab();

            Print("}"_us);

            Print("SecondExpression: {"_us);

            AddTab();

            VisitExpression(binaryExpression->GetSecondExpression());

            SubTab();

            Print("}"_us);

            auto operation = binaryExpression->GetBinaryOperation();

            UString stringOperation;

            switch (operation) {
                case AST::BinaryOperation::Plus:
                    stringOperation = "Plus (+)"_us;

                    break;
                case AST::BinaryOperation::Minus:
                    stringOperation = "Minus (-)"_us;

                    break;
                case AST::BinaryOperation::Star:
                    stringOperation = "Star (*)"_us;

                    break;
                case AST::BinaryOperation::Slash:
                    stringOperation = "Slash (/)"_us;

                    break;
            }

            Print("Operation: "_us + stringOperation);

            SubTab();

            Print("}"_us);
        }

        Void VisitVariableUsingExpression(LRef<std::shared_ptr<AST::GS_VariableUsingExpression>> variableUsingExpression) override {
            Print("VariableUsingExpression: {"_us);

            AddTab();

            Print("Name: "_us + variableUsingExpression->GetName());

            SubTab();

            Print("}"_us);
        }

        Void VisitFunctionCallingExpression(LRef<std::shared_ptr<AST::GS_FunctionCallingExpression>> functionCallingExpression) override {
            Print("FunctionCallingExpression: {"_us);

            AddTab();

            Print("Name: "_us + functionCallingExpression->GetName());

            Print("Params: {"_us);

            AddTab();

            for (auto &param : functionCallingExpression->GetParams()) {
                VisitExpression(param);
            }

            SubTab();

            Print("}"_us);

            SubTab();

            Print("}"_us);
        }

    private:

        Void Print(UString message) {
            PrintTabs();

            std::cout << message << std::endl;
        }

        Void PrintTabs() {
            for (auto i = 0; i < tabsNumber; ++i) {
                std::cout << "  "_us;
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

    GS_ASTDumper::GS_ASTDumper(AST::GSNodePtr node)
            : _node(std::move(node)) {}

    std::shared_ptr<GS_ASTDumper> GS_ASTDumper::Create(AST::GSNodePtr node) {
        return std::make_shared<GS_ASTDumper>(std::move(node));
    }

    Void GS_ASTDumper::Dump() {
        GS_ASTDumpVisitor visitor;

        visitor.VisitNode(_node);
    }

    Void DumpAST(AST::GSNodePtr node) {
        auto dumper = GS_ASTDumper::Create(std::move(node));

        dumper->Dump();
    }

}
