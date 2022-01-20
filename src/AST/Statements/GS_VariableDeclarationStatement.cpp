#include <AST/Statements/GS_VariableDeclarationStatement.h>

namespace GSLanguageCompiler::AST {

    GS_VariableDeclarationStatement::GS_VariableDeclarationStatement(UString name, GSTypePtr type, GSScopePtr scope)
            : _name(std::move(name)), _type(std::move(type)), _expression(nullptr), GS_Statement(std::move(scope)) {}

    GS_VariableDeclarationStatement::GS_VariableDeclarationStatement(UString name, GSExpressionPtr expression, GSScopePtr scope)
            : _name(std::move(name)), _type(nullptr), _expression(std::move(expression)), GS_Statement(std::move(scope)) {}

    GS_VariableDeclarationStatement::GS_VariableDeclarationStatement(UString name, GSTypePtr type, GSExpressionPtr expression, GSScopePtr scope)
            : _name(std::move(name)), _type(std::move(type)), _expression(std::move(expression)), GS_Statement(std::move(scope)) {}

    UString GS_VariableDeclarationStatement::getName() const {
        return _name;
    }

    GSTypePtr GS_VariableDeclarationStatement::getType() const {
        return _type;
    }

    GSExpressionPtr GS_VariableDeclarationStatement::getExpression() const {
        return _expression;
    }

    Void GS_VariableDeclarationStatement::accept(Ptr<GS_Visitor> visitor) {
        visitor->visit(this);
    }

    StatementType GS_VariableDeclarationStatement::getStatementType() const {
        return StatementType::VariableDeclarationStatement;
    }

}
