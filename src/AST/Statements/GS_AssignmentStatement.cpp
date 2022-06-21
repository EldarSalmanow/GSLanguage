#include <Statements/GS_AssignmentStatement.h>

namespace GSLanguageCompiler::AST {

    GS_AssignmentStatement::GS_AssignmentStatement(GSExpressionPtr lvalueExpression, GSExpressionPtr rvalueExpression)
            : _lvalueExpression(nullptr), _rvalueExpression(nullptr) {
        if (IsLValueExpression(lvalueExpression)) {
            _lvalueExpression = std::move(lvalueExpression);
        }

        if (IsRValueExpression(rvalueExpression)) {
            _rvalueExpression = std::move(rvalueExpression);
        }
    }

    std::shared_ptr<GS_AssignmentStatement> GS_AssignmentStatement::Create(GSExpressionPtr lvalueExpression, GSExpressionPtr rvalueExpression) {
        return std::make_shared<GS_AssignmentStatement>(std::move(lvalueExpression), std::move(rvalueExpression));
    }

    LRef<GSExpressionPtr> GS_AssignmentStatement::GetLValueExpression() {
        return _lvalueExpression;
    }

    LRef<GSExpressionPtr> GS_AssignmentStatement::GetRValueExpression() {
        return _rvalueExpression;
    }

    StatementType GS_AssignmentStatement::GetStatementType() const {
        return StatementType::AssignmentStatement;
    }

}
