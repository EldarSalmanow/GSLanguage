#include <AST/Statements/GS_VariableDeclarationStatement.h>

namespace GSLanguageCompiler::AST {

    GS_VariableDeclarationStatement::GS_VariableDeclarationStatement(String name, GSTypePtr type)
            : _name(std::move(name)), _type(std::move(type)) {}

    String GS_VariableDeclarationStatement::getName() {
        return _name;
    }

    GSTypePtr GS_VariableDeclarationStatement::getType() {
        return _type;
    }

    Void GS_VariableDeclarationStatement::accept(GS_Visitor *visitor) {
        visitor->visit(this);
    }

    StatementType GS_VariableDeclarationStatement::getStatementType() {
        return StatementType::VariableDeclarationStatement;
    }

}
