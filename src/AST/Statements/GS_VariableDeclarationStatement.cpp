#include <AST/Statements/GS_VariableDeclarationStatement.h>

namespace GSLanguageCompiler::AST {

    GS_VariableDeclarationStatement::GS_VariableDeclarationStatement(String name, GSTypePtr type, GSExpressionPtr expression, GSScopePtr scope)
            : _name(std::move(name)), _type(std::move(type)), _expression(std::move(expression)), GS_Statement(std::move(scope)) {}

    String GS_VariableDeclarationStatement::getName() {
        return _name;
    }

    GSTypePtr GS_VariableDeclarationStatement::getType() {
        return _type;
    }

    GSExpressionPtr GS_VariableDeclarationStatement::getExpression() {
        return _expression;
    }

    Void GS_VariableDeclarationStatement::accept(GS_Visitor *visitor) {
        visitor->visit(this);
    }

    StatementType GS_VariableDeclarationStatement::getStatementType() {
        return StatementType::VariableDeclarationStatement;
    }

}
