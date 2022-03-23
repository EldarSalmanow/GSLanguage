#include <Declarations/GS_FunctionDeclaration.h>

#include <Statements/GS_VariableDeclarationStatement.h>

namespace GSLanguageCompiler::AST {

    GS_VariableDeclarationStatement::GS_VariableDeclarationStatement(UString name, GSTypePtr type, GSExpressionPtr expression, GSScopePtr scope)
            : _name(std::move(name)), _type(std::move(type)), _expression(std::move(expression)), GS_Statement(std::move(scope)) {}

    SharedPtr<GS_VariableDeclarationStatement> GS_VariableDeclarationStatement::Create(UString name, GSTypePtr type, GSExpressionPtr expression, GSScopePtr scope) {
        return std::make_shared<GS_VariableDeclarationStatement>(std::move(name), std::move(type), std::move(expression), std::move(scope));
    }

    SharedPtr<GS_VariableDeclarationStatement> GS_VariableDeclarationStatement::Create(UString name, GSTypePtr type, GSScopePtr scope) {
        return GS_VariableDeclarationStatement::Create(std::move(name), std::move(type), GSExpressionPtr(), std::move(scope));
    }

    SharedPtr<GS_VariableDeclarationStatement> GS_VariableDeclarationStatement::Create(UString name, GSExpressionPtr expression, GSScopePtr scope) {
        return GS_VariableDeclarationStatement::Create(std::move(name), GSTypePtr(), std::move(expression), std::move(scope));
    }

    LRef<UString> GS_VariableDeclarationStatement::GetName() {
        return _name;
    }

    LRef<GSTypePtr> GS_VariableDeclarationStatement::GetType() {
        return _type;
    }

    LRef<GSExpressionPtr> GS_VariableDeclarationStatement::GetExpression() {
        return _expression;
    }

    StatementType GS_VariableDeclarationStatement::GetStatementType() const {
        return StatementType::VariableDeclarationStatement;
    }

}
