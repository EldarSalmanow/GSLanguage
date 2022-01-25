#include <Statements/GS_ExpressionStatement.h>

namespace GSLanguageCompiler::AST {

    GS_ExpressionStatement::GS_ExpressionStatement(GSExpressionPtr expression, GSScopePtr scope)
            : _expression(std::move(expression)), GS_Statement(std::move(scope)) {}

    GSExpressionPtr GS_ExpressionStatement::getExpression() const {
        return _expression;
    }

    Any GS_ExpressionStatement::accept(Ptr<GS_Visitor> visitor) {
        return visitor->visit(this);
    }

    StatementType GS_ExpressionStatement::getStatementType() const {
        return StatementType::ExpressionStatement;
    }

}
