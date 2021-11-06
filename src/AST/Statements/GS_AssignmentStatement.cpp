#include <Statements/GS_AssignmentStatement.h>

namespace GSLanguageCompiler::AST {

    GS_AssignmentStatement::GS_AssignmentStatement(GSExpressionPtr lvalueExpression, GSExpressionPtr rvalueExpression, GSScopePtr scope)
            : _lvalueExpression(std::move(lvalueExpression)), _rvalueExpression(std::move(rvalueExpression)), GS_Statement(std::move(scope)) {}

    GSExpressionPtr GS_AssignmentStatement::getLValueExpression() {
        return _lvalueExpression;
    }

    GSExpressionPtr GS_AssignmentStatement::getRValueExpression() {
        return _rvalueExpression;
    }

    Void GS_AssignmentStatement::accept(GS_Visitor *visitor) {
        visitor->visit(this);
    }

    StatementType GS_AssignmentStatement::getStatementType() {
        return StatementType::AssignmentStatement;
    }

}
