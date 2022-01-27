#include <Statements/GS_ExpressionStatement.h>

namespace GSLanguageCompiler::AST {

    GS_ExpressionStatement::GS_ExpressionStatement(GSExpressionPtr expression, GSScopePtr scope)
            : _expression(std::move(expression)), GS_Statement(std::move(scope)) {}

    LRef<GSExpressionPtr> GS_ExpressionStatement::getExpression() {
        return _expression;
    }

    StatementType GS_ExpressionStatement::getStatementType() const {
        return StatementType::ExpressionStatement;
    }

}
