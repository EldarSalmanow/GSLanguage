#include <AST/Statements/GS_VariableDeclarationStatement.h>

namespace GSLanguageCompiler::AST {

    GS_VariableDeclarationStatement::GS_VariableDeclarationStatement(UString name, GSTypePtr type, GSScopePtr scope)
            : _name(std::move(name)), _type(std::move(type)), _expression(nullptr), GS_Statement(std::move(scope)) {}

    GS_VariableDeclarationStatement::GS_VariableDeclarationStatement(UString name, GSExpressionPtr expression, GSScopePtr scope)
            : _name(std::move(name)), _type(nullptr), _expression(std::move(expression)), GS_Statement(std::move(scope)) {}

    GS_VariableDeclarationStatement::GS_VariableDeclarationStatement(UString name, GSTypePtr type, GSExpressionPtr expression, GSScopePtr scope)
            : _name(std::move(name)), _type(std::move(type)), _expression(std::move(expression)), GS_Statement(std::move(scope)) {}

    LRef<UString> GS_VariableDeclarationStatement::getName() {
        return _name;
    }

    LRef<GSTypePtr> GS_VariableDeclarationStatement::getType() {
        return _type;
    }

    LRef<GSExpressionPtr> GS_VariableDeclarationStatement::getExpression() {
        return _expression;
    }

    StatementType GS_VariableDeclarationStatement::getStatementType() const {
        return StatementType::VariableDeclarationStatement;
    }

}
