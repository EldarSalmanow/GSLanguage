#include <Driver/GS_Session.h>

#include <Semantic/Passes/GS_SymbolsPlaceholderPass.h>

namespace GSLanguageCompiler::Semantic {

    Void AddFunction(ConstLRef<AST::NodePtr<AST::GS_FunctionDeclaration>> functionDeclaration,
                     LRef<GS_TableOfSymbols> tableOfSymbols) {
        auto functionName = functionDeclaration->GetName();
        auto functionSignature = functionDeclaration->GetSignature();

        tableOfSymbols.AddFunction(functionName,
                                   functionSignature);
    }

    Void AddVariable(ConstLRef<AST::NodePtr<AST::GS_VariableDeclarationStatement>> variableDeclarationStatement,
                     LRef<GS_TableOfSymbols> tableOfSymbols) {
        auto variableName = variableDeclarationStatement->GetName();
        auto variableType = variableDeclarationStatement->GetType();
        
        tableOfSymbols.AddVariable(variableName,
                                   variableType);
    }

    GS_SymbolsPlaceholderVisitor::GS_SymbolsPlaceholderVisitor() = default;

    Void GS_SymbolsPlaceholderVisitor::VisitFunctionDeclaration(LRef<Driver::GS_Session> session,
                                                                AST::NodePtrLRef<AST::GS_FunctionDeclaration> functionDeclaration) {
        GS_Visitor::VisitFunctionDeclaration(session,
                                             functionDeclaration);

        auto &tableOfSymbols = session.GetTableOfSymbols();

        AddFunction(functionDeclaration,
                    tableOfSymbols);
    }

    Void GS_SymbolsPlaceholderVisitor::VisitVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                                                         AST::NodePtrLRef<AST::GS_VariableDeclarationStatement> variableDeclarationStatement) {
        GS_Visitor::VisitVariableDeclarationStatement(session,
                                                      variableDeclarationStatement);

        auto &tableOfSymbols = session.GetTableOfSymbols();

        AddVariable(variableDeclarationStatement,
                    tableOfSymbols);
    }

    AST::GSPassPtr CreateSymbolsPlaceholderPass() {
        return std::make_shared<GS_SymbolsPlaceholderPass>();
    }

}
