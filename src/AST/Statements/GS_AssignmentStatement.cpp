#include <Statements/GS_AssignmentStatement.h>

namespace GSLanguageCompiler::AST {

    GS_AssignmentStatement::GS_AssignmentStatement(GSExpressionPtr lvalueExpression, GSExpressionPtr rvalueExpression, GSScopePtr scope)
            : _lvalueExpression(std::move(lvalueExpression)), _rvalueExpression(std::move(rvalueExpression)), GS_Statement(std::move(scope)) {}

    GSExpressionPtr GS_AssignmentStatement::getLValueExpression() const {
        return _lvalueExpression;
    }

    GSExpressionPtr GS_AssignmentStatement::getRValueExpression() const {
        return _rvalueExpression;
    }

    Any GS_AssignmentStatement::accept(Ptr<GS_Visitor> visitor) {
        return visitor->visit(this);
    }

    StatementType GS_AssignmentStatement::getStatementType() const {
        return StatementType::AssignmentStatement;
    }

}
