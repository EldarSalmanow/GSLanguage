#include <Statements/GS_AssignmentStatement.h>

namespace GSLanguageCompiler::AST {

    GS_AssignmentStatement::GS_AssignmentStatement(GSExpressionPtr lvalueExpression, GSExpressionPtr rvalueExpression, GSScopePtr scope)
            : _lvalueExpression(std::move(lvalueExpression)), _rvalueExpression(std::move(rvalueExpression)), GS_Statement(std::move(scope)) {}

    LRef<GSExpressionPtr> GS_AssignmentStatement::getLValueExpression() {
        return _lvalueExpression;
    }

    LRef<GSExpressionPtr> GS_AssignmentStatement::getRValueExpression() {
        return _rvalueExpression;
    }

    StatementType GS_AssignmentStatement::getStatementType() const {
        return StatementType::AssignmentStatement;
    }

}
