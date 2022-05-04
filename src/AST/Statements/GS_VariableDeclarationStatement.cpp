#include <Statements/GS_VariableDeclarationStatement.h>

namespace GSLanguageCompiler::AST {

    GS_VariableDeclarationStatement::GS_VariableDeclarationStatement(UString name, Semantic::GSTypePtr type, GSExpressionPtr expression)
            : _name(std::move(name)), _type(std::move(type)), _expression(std::move(expression)) {}

    SharedPtr<GS_VariableDeclarationStatement> GS_VariableDeclarationStatement::Create(UString name, Semantic::GSTypePtr type, GSExpressionPtr expression) {
        return std::make_shared<GS_VariableDeclarationStatement>(std::move(name), std::move(type), std::move(expression));
    }

    SharedPtr<GS_VariableDeclarationStatement> GS_VariableDeclarationStatement::Create(UString name, Semantic::GSTypePtr type) {
        return GS_VariableDeclarationStatement::Create(std::move(name), std::move(type), GSExpressionPtr());
    }

    SharedPtr<GS_VariableDeclarationStatement> GS_VariableDeclarationStatement::Create(UString name, GSExpressionPtr expression) {
        return GS_VariableDeclarationStatement::Create(std::move(name), Semantic::GSTypePtr(), std::move(expression));
    }

    LRef<UString> GS_VariableDeclarationStatement::GetName() {
        return _name;
    }

    LRef<Semantic::GSTypePtr> GS_VariableDeclarationStatement::GetType() {
        return _type;
    }

    LRef<GSExpressionPtr> GS_VariableDeclarationStatement::GetExpression() {
        return _expression;
    }

    StatementType GS_VariableDeclarationStatement::GetStatementType() const {
        return StatementType::VariableDeclarationStatement;
    }

}
