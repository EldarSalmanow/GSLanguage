#include <AST/Statements/GS_VariableDeclarationStatement.h>
#include <AST/Statements/GS_AssignmentStatement.h>

#include <Visitors/GS_VariablesPlaceholderVisitor.h>

namespace GSLanguageCompiler::Semantic {

    GS_VariablesPlaceholderVisitor::GS_VariablesPlaceholderVisitor(GS_VariablesPlaceholderPass *pass)
            : _pass(pass) {}

    Void GS_VariablesPlaceholderVisitor::visit(AST::GS_AssignmentStatement *assignmentStatement) {
        auto statement = assignmentStatement->getStatement();
        auto expression = assignmentStatement->getExpression();

        if (statement->getStatementType() == AST::StatementType::VariableDeclarationStatement) {
            addVariable(std::reinterpret_pointer_cast<AST::GS_VariableDeclarationStatement>(statement).get(), expression);
        }
    }

    Void GS_VariablesPlaceholderVisitor::addVariable(AST::GS_VariableDeclarationStatement *statement, AST::GSExpressionPtr &expression) {
        auto name = statement->getName();
        auto type = statement->getType();

        _pass->getTableOfSymbols()->addVariable(name, type, expression);
    }

}
