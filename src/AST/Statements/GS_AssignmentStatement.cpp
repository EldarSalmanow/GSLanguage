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

    Void GS_AssignmentStatement::accept(GS_Visitor *visitor) {
        visitor->visit(this);
    }

    StatementType GS_AssignmentStatement::getStatementType() {
        return StatementType::AssignmentStatement;
    }

}
