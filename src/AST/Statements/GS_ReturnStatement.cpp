#include <Statements/GS_ReturnStatement.h>

namespace GSLanguageCompiler::AST {

    GS_ReturnStatement::GS_ReturnStatement(GSExpressionPtr expression)
            : _expression(std::move(expression)) {}

    std::shared_ptr<GS_ReturnStatement> GS_ReturnStatement::Create(GSExpressionPtr expression) {
        return std::make_shared<GS_ReturnStatement>(std::move(expression));
    }

    std::shared_ptr<GS_ReturnStatement> GS_ReturnStatement::Create() {
        return GS_ReturnStatement::Create(GSExpressionPtr());
    }

    LRef<GSExpressionPtr> GS_ReturnStatement::GetExpression() {
        return _expression;
    }

    StatementType GS_ReturnStatement::GetStatementType() const {
        return StatementType::ReturnStatement;
    }

}
