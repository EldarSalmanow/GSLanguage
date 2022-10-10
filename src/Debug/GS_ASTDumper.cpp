#include <Driver/Driver.h>

#include <GS_ASTDumper.h>

namespace GSLanguageCompiler::Debug {

    class GS_ASTDumpVisitor : public AST::GS_Visitor {
    public:

        GS_ASTDumpVisitor()
                : _tabsNumber(0) {}

    public:

        Void VisitTranslationUnitDeclaration(AST::NodePtrLRef<AST::GS_TranslationUnitDeclaration> translationUnitDeclaration,
                                             LRef<Driver::GSContextPtr> context) override {
            Print("TranslationUnitDeclaration: {"_us, context);

            IncTab();

            Print("Name: "_us + translationUnitDeclaration->GetName(), context);

            Print("Nodes: {"_us, context);

            IncTab();

            for (auto &node : translationUnitDeclaration->GetNodes()) {
                VisitNode(node, context);
            }

            DecTab();

            Print("}"_us, context);

            DecTab();

            Print("}"_us, context);
        }

        Void VisitFunctionDeclaration(AST::NodePtrLRef<AST::GS_FunctionDeclaration> functionDeclaration,
                                      LRef<Driver::GSContextPtr> context) override {
            Print("FunctionDeclaration: {"_us, context);

            IncTab();

            Print("Name: "_us + functionDeclaration->GetName(), context);

            auto signature = functionDeclaration->GetSignature();

            auto paramTypes = signature.GetParamTypes();
            auto returnType = signature.GetReturnType();

            auto signatureMessage = "Signature: ("_us;

            for (auto &paramType : paramTypes) {
                signatureMessage += paramType->GetName() + " "_us;
            }

            signatureMessage += ") -> "_us + returnType->GetName();

            Print(signatureMessage, context);

            Print("Body: {"_us, context);

            IncTab();

            for (auto &statement : functionDeclaration->GetBody()) {
                VisitStatement(statement, context);
            }

            DecTab();

            Print("}"_us, context);

            DecTab();

            Print("}"_us, context);
        }

        Void VisitVariableDeclarationStatement(AST::NodePtrLRef<AST::GS_VariableDeclarationStatement> variableDeclarationStatement,
                                               LRef<Driver::GSContextPtr> context) override {
            Print("VariableDeclarationStatement: {"_us, context);

            IncTab();

            Print("Name: "_us + variableDeclarationStatement->GetName(), context);

            Print("Type: "_us + variableDeclarationStatement->GetType()->GetName(), context);

            Print("Expression: {"_us, context);

            IncTab();

            VisitExpression(variableDeclarationStatement->GetExpression(), context);

            DecTab();

            Print("}"_us, context);

            DecTab();

            Print("}"_us, context);
        }

        Void VisitAssignmentStatement(AST::NodePtrLRef<AST::GS_AssignmentStatement> assignmentStatement,
                                      LRef<Driver::GSContextPtr> context) override {
            Print("AssignmentStatement: {"_us, context);

            IncTab();

            Print("LValueExpression: {"_us, context);

            IncTab();

            VisitExpression(assignmentStatement->GetLValueExpression(), context);

            DecTab();

            Print("}"_us, context);

            Print("RValueExpression: {"_us, context);

            IncTab();

            VisitExpression(assignmentStatement->GetRValueExpression(), context);

            DecTab();

            Print("}"_us, context);

            DecTab();

            Print("}"_us, context);
        }

        Void VisitExpressionStatement(AST::NodePtrLRef<AST::GS_ExpressionStatement> expressionStatement,
                                      LRef<Driver::GSContextPtr> context) override {
            Print("ExpressionStatement: {"_us, context);

            IncTab();

            VisitExpression(expressionStatement->GetExpression(), context);

            DecTab();

            Print("}"_us, context);
        }

        Void VisitConstantExpression(AST::NodePtrLRef<AST::GS_ConstantExpression> constantExpression,
                                     LRef<Driver::GSContextPtr> context) override {
            Print("ConstantExpression: {"_us, context);

            IncTab();

            Print("Value: {"_us, context);

            IncTab();

            auto value = AST::GSValueCast<AST::GS_LiteralValue>(constantExpression->GetValue());
            auto typeName = value->GetType()->GetName();

            Print("Type: " + typeName.AsUTF8(), context);

            if (typeName == "I32"_us) {
                Print("Value: "_us + UString(std::to_string(value->GetValueWithCast<I32>())), context);
            } else if (typeName == "String"_us) {
                Print("Value: "_us + value->GetValueWithCast<UString>(), context);
            }

            DecTab();

            Print("}"_us, context);

            DecTab();

            Print("}"_us, context);
        }

        Void VisitUnaryExpression(AST::NodePtrLRef<AST::GS_UnaryExpression> unaryExpression,
                                  LRef<Driver::GSContextPtr> context) override {
            Print("UnaryExpression: {"_us, context);

            IncTab();

            Print("Expression: {"_us, context);

            IncTab();

            VisitExpression(unaryExpression->GetExpression(), context);

            DecTab();

            Print("}"_us, context);

            auto operation = unaryExpression->GetUnaryOperation();

            UString stringOperation;

            switch (operation) {
                case AST::UnaryOperation::Minus:
                    stringOperation = "Minus (-)"_us;

                    break;
            }

            Print("Operation: "_us + stringOperation, context);

            DecTab();

            Print("}"_us, context);
        }

        Void VisitBinaryExpression(AST::NodePtrLRef<AST::GS_BinaryExpression> binaryExpression,
                                   LRef<Driver::GSContextPtr> context) override {
            Print("BinaryExpression: {"_us, context);

            IncTab();

            Print("FirstExpression: {"_us, context);

            IncTab();

            VisitExpression(binaryExpression->GetFirstExpression(), context);

            DecTab();

            Print("}"_us, context);

            Print("SecondExpression: {"_us, context);

            IncTab();

            VisitExpression(binaryExpression->GetSecondExpression(), context);

            DecTab();

            Print("}"_us, context);

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

            Print("Operation: "_us + stringOperation, context);

            DecTab();

            Print("}"_us, context);
        }

        Void VisitVariableUsingExpression(AST::NodePtrLRef<AST::GS_VariableUsingExpression> variableUsingExpression,
                                          LRef<Driver::GSContextPtr> context) override {
            Print("VariableUsingExpression: {"_us, context);

            IncTab();

            Print("Name: "_us + variableUsingExpression->GetName(), context);

            DecTab();

            Print("}"_us, context);
        }

        Void VisitFunctionCallingExpression(AST::NodePtrLRef<AST::GS_FunctionCallingExpression> functionCallingExpression,
                                            LRef<Driver::GSContextPtr> context) override {
            Print("FunctionCallingExpression: {"_us, context);

            IncTab();

            Print("Name: "_us + functionCallingExpression->GetName(), context);

            Print("Params: {"_us, context);

            IncTab();

            for (auto &param : functionCallingExpression->GetParams()) {
                VisitExpression(param, context);
            }

            DecTab();

            Print("}"_us, context);

            DecTab();

            Print("}"_us, context);
        }

    private:

        Void Print(ConstLRef<UString> message, LRef<Driver::GSContextPtr> context) {
            auto outputStream = context->GetStdOutStream();

            auto &stdOutputStream = outputStream->GetOutStream();

            for (U64 i = 0; i < _tabsNumber; ++i) {
                stdOutputStream << "  "_us;
            }

            stdOutputStream << message << "\n"_us;
        }

        Void IncTab() {
            ++_tabsNumber;
        }

        Void DecTab() {
            --_tabsNumber;
        }

    private:

        U64 _tabsNumber;
    };

    GS_ASTDumper::GS_ASTDumper(AST::GSNodePtr node, LRef<Driver::GSContextPtr> context)
            : _node(std::move(node)), _context(context) {}

    std::shared_ptr<GS_ASTDumper> GS_ASTDumper::Create(AST::GSNodePtr node, LRef<Driver::GSContextPtr> context) {
        return std::make_shared<GS_ASTDumper>(std::move(node), context);
    }

    Void GS_ASTDumper::Dump() {
        GS_ASTDumpVisitor visitor;

        visitor.VisitNode(_node, _context);
    }

    Void DumpAST(AST::GSNodePtr node, LRef<Driver::GSContextPtr> context) {
        auto dumper = GS_ASTDumper::Create(std::move(node), context);

        dumper->Dump();
    }

}
