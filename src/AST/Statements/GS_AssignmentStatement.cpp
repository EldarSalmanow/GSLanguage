#include <Statements/GS_AssignmentStatement.h>

namespace GSLanguageCompiler::AST {

    GS_AssignmentStatement::GS_AssignmentStatement(GSExpressionPtr lvalueExpression, GSExpressionPtr rvalueExpression, GSScopePtr scope)
            : _lvalueExpression(std::move(lvalueExpression)), _rvalueExpression(std::move(rvalueExpression)), GS_Statement(std::move(scope)) {}

    SharedPtr<GS_AssignmentStatement> GS_AssignmentStatement::Create(GSExpressionPtr lvalueExpression, GSExpressionPtr rvalueExpression, GSScopePtr scope) {
        return std::make_shared<GS_AssignmentStatement>(std::move(lvalueExpression), std::move(rvalueExpression), std::move(scope));
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
