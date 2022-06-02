#include <Statements/GS_ExpressionStatement.h>

namespace GSLanguageCompiler::AST {

    GS_ExpressionStatement::GS_ExpressionStatement(GSExpressionPtr expression)
            : _expression(std::move(expression)) {}

    std::shared_ptr<GS_ExpressionStatement> GS_ExpressionStatement::Create(GSExpressionPtr expression) {
        return std::make_shared<GS_ExpressionStatement>(std::move(expression));
    }

    LRef<GSExpressionPtr> GS_ExpressionStatement::GetExpression() {
        return _expression;
    }

    StatementType GS_ExpressionStatement::GetStatementType() const {
        return StatementType::ExpressionStatement;
    }

}
