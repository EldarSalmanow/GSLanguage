#include <Driver/Driver.h>

#include <GS_ASTDumper.h>

namespace GSLanguageCompiler::Debug {

    class GS_ASTDumpVisitor : public AST::GS_Visitor {
    public:

        GS_ASTDumpVisitor()
                : _tabsNumber(0) {}

    public:

        Void VisitTranslationUnitDeclaration(LRef<Driver::GS_Session> session,
                                             AST::NodePtrLRef<AST::GS_TranslationUnitDeclaration> translationUnitDeclaration) override {
            Print("TranslationUnitDeclaration: {"_us, session);

            IncTab();

            Print("Name: "_us + translationUnitDeclaration->GetName(), session);

            Print("Nodes: {"_us, session);

            IncTab();

            for (auto &node : translationUnitDeclaration->GetNodes()) {
                VisitNode(session, node);
            }

            DecTab();

            Print("}"_us, session);

            DecTab();

            Print("}"_us, session);
        }

        Void VisitFunctionDeclaration(LRef<Driver::GS_Session> session,
                                      AST::NodePtrLRef<AST::GS_FunctionDeclaration> functionDeclaration) override {
            Print("FunctionDeclaration: {"_us, session);

            IncTab();

            Print("Name: "_us + functionDeclaration->GetName(), session);

            auto signature = functionDeclaration->GetSignature();

            auto paramTypes = signature.GetParams();
            auto returnType = signature.GetReturnType();

            auto signatureMessage = "Signature: ("_us;

            for (auto &paramType : paramTypes) {
                signatureMessage += paramType.GetName() + " "_us;
            }

            signatureMessage += ") -> "_us + returnType->GetName();

            Print(signatureMessage, session);

            Print("Body: {"_us, session);

            IncTab();

            for (auto &statement : functionDeclaration->GetBody()) {
                VisitStatement(session, statement);
            }

            DecTab();

            Print("}"_us, session);

            DecTab();

            Print("}"_us, session);
        }

        Void VisitVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                               AST::NodePtrLRef<AST::GS_VariableDeclarationStatement> variableDeclarationStatement) override {
            Print("VariableDeclarationStatement: {"_us, session);

            IncTab();

            Print("Name: "_us + variableDeclarationStatement->GetName(), session);

            if (variableDeclarationStatement->GetType()) {
                Print("Type: "_us + variableDeclarationStatement->GetType()->GetName(), session);
            } else {
                Print("Type: <unknown>"_us, session);
            }

            Print("Expression: {"_us, session);

            IncTab();

            VisitExpression(session, variableDeclarationStatement->GetExpression());

            DecTab();

            Print("}"_us, session);

            DecTab();

            Print("}"_us, session);
        }

        Void VisitAssignmentStatement(LRef<Driver::GS_Session> session,
                                      AST::NodePtrLRef<AST::GS_AssignmentStatement> assignmentStatement) override {
            Print("AssignmentStatement: {"_us, session);

            IncTab();

            Print("LValueExpression: {"_us, session);

            IncTab();

            VisitExpression(session,
                            assignmentStatement->GetLValueExpression());

            DecTab();

            Print("}"_us, session);

            Print("RValueExpression: {"_us, session);

            IncTab();

            VisitExpression(session,
                            assignmentStatement->GetRValueExpression());

            DecTab();

            Print("}"_us, session);

            DecTab();

            Print("}"_us, session);
        }

        Void VisitExpressionStatement(LRef<Driver::GS_Session> session,
                                      AST::NodePtrLRef<AST::GS_ExpressionStatement> expressionStatement) override {
            Print("ExpressionStatement: {"_us, session);

            IncTab();

            VisitExpression(session, expressionStatement->GetExpression());

            DecTab();

            Print("}"_us, session);
        }

        Void VisitConstantExpression(LRef<Driver::GS_Session> session,
                                     AST::NodePtrLRef<AST::GS_ConstantExpression> constantExpression) override {
            Print("ConstantExpression: {"_us, session);

            IncTab();

            Print("Value: {"_us, session);

            IncTab();

            auto value = AST::ToValue<AST::GS_LiteralValue>(constantExpression->GetValue());
            auto typeName = value->GetType()->GetName();

            Print("Type: " + typeName.AsUTF8(), session);

            if (typeName == "I32"_us) {
                Print("Value: "_us + UString(std::to_string(value->GetValueWithCast<I32>())), session);
            } else if (typeName == "String"_us) {
                Print("Value: "_us + value->GetValueWithCast<UString>(), session);
            }

            DecTab();

            Print("}"_us, session);

            DecTab();

            Print("}"_us, session);
        }

        Void VisitUnaryExpression(LRef<Driver::GS_Session> session,
                                  AST::NodePtrLRef<AST::GS_UnaryExpression> unaryExpression) override {
            Print("UnaryExpression: {"_us, session);

            IncTab();

            Print("Expression: {"_us, session);

            IncTab();

            VisitExpression(session,
                            unaryExpression->GetExpression());

            DecTab();

            Print("}"_us, session);

            auto operation = unaryExpression->GetUnaryOperation();

            UString stringOperation;

            switch (operation) {
                case AST::UnaryOperation::Minus:
                    stringOperation = "Minus (-)"_us;

                    break;
            }

            Print("Operation: "_us + stringOperation, session);

            DecTab();

            Print("}"_us, session);
        }

        Void VisitBinaryExpression(LRef<Driver::GS_Session> session,
                                   AST::NodePtrLRef<AST::GS_BinaryExpression> binaryExpression) override {
            Print("BinaryExpression: {"_us, session);

            IncTab();

            Print("FirstExpression: {"_us, session);

            IncTab();

            VisitExpression(session,
                            binaryExpression->GetFirstExpression());

            DecTab();

            Print("}"_us, session);

            Print("SecondExpression: {"_us, session);

            IncTab();

            VisitExpression(session,
                            binaryExpression->GetSecondExpression());

            DecTab();

            Print("}"_us, session);

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

            Print("Operation: "_us + stringOperation, session);

            DecTab();

            Print("}"_us, session);
        }

        Void VisitArrayExpression(LRef<Driver::GS_Session> session,
                                  AST::NodePtrLRef<AST::GS_ArrayExpression> arrayExpression) override {
            Print("ArrayExpression: {"_us, session);

            IncTab();

            Print("Expressions: {"_us, session);

            IncTab();

            for (auto &expression : arrayExpression->GetExpressions()) {
                VisitExpression(session, expression);
            }

            DecTab();

            Print("}"_us, session);

            DecTab();

            Print("}"_us, session);
        }

        Void VisitVariableUsingExpression(LRef<Driver::GS_Session> session,
                                          AST::NodePtrLRef<AST::GS_VariableUsingExpression> variableUsingExpression) override {
            Print("VariableUsingExpression: {"_us, session);

            IncTab();

            Print("Name: "_us + variableUsingExpression->GetName(), session);

            DecTab();

            Print("}"_us, session);
        }

        Void VisitFunctionCallingExpression(LRef<Driver::GS_Session> session,
                                            AST::NodePtrLRef<AST::GS_FunctionCallingExpression> functionCallingExpression) override {
            Print("FunctionCallingExpression: {"_us, session);

            IncTab();

            Print("Name: "_us + functionCallingExpression->GetName(), session);

            Print("Params: {"_us, session);

            IncTab();

            for (auto &param : functionCallingExpression->GetArguments()) {
                VisitExpression(session,
                                param);
            }

            DecTab();

            Print("}"_us, session);

            DecTab();

            Print("}"_us, session);
        }

    private:

        Void Print(ConstLRef<UString> message, LRef<Driver::GS_Session> session) {
            auto &outputStream = session.StdOut();

            for (U64 i = 0; i < _tabsNumber; ++i) {
                outputStream << "  "_us;
            }

            outputStream << message << "\n"_us;
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

    GS_ASTDumper::GS_ASTDumper(AST::GSNodePtr node, LRef<Driver::GS_Session> session)
            : _node(std::move(node)), _session(session) {}

    std::shared_ptr<GS_ASTDumper> GS_ASTDumper::Create(AST::GSNodePtr node, LRef<Driver::GS_Session> session) {
        return std::make_shared<GS_ASTDumper>(std::move(node), session);
    }

    Void GS_ASTDumper::Dump() {
        GS_ASTDumpVisitor visitor;

        visitor.VisitNode(_session, _node);
    }

    Void DumpAST(AST::GSNodePtr node, LRef<Driver::GS_Session> session) {
        auto dumper = GS_ASTDumper::Create(std::move(node), session);

        dumper->Dump();
    }

}
