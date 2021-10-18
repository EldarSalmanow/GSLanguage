#include <Statements/GS_AssignmentStatement.h>

namespace GSLanguageCompiler::AST {

    GS_AssignmentStatement::GS_AssignmentStatement(GSStatementPtr statement, GSExpressionPtr expression)
            : _statement(std::move(statement)), _expression(std::move(expression)) {}

    GSStatementPtr GS_AssignmentStatement::getStatement() {
        return _statement;
    }

    GSExpressionPtr GS_AssignmentStatement::getExpression() {
        return _expression;
    }

    StatementType GS_AssignmentStatement::getStatementType() {
        return StatementType::AssignmentStatement;
    }

}
