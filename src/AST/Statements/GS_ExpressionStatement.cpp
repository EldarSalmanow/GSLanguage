#include <Statements/GS_ExpressionStatement.h>

namespace GSLanguageCompiler::AST {

    GS_ExpressionStatement::GS_ExpressionStatement(GSExpressionPtr expression)
            : _expression(std::move(expression)) {}

    GSExpressionPtr GS_ExpressionStatement::getExpression() {
        return _expression;
    }

    Void GS_ExpressionStatement::accept(GS_Visitor *visitor) {
        visitor->visit(this);
    }

    StatementType GS_ExpressionStatement::getStatementType() {
        return StatementType::ExpressionStatement;
    }

}
