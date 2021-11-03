#include <Statements/GS_DeclarationStatement.h>

namespace GSLanguageCompiler::AST {

    GS_DeclarationStatement::GS_DeclarationStatement(GSStatementPtr &statement)
            : _statement(std::move(statement)) {}

    GSStatementPtr GS_DeclarationStatement::getStatement() {
        return _statement;
    }

    Void GS_DeclarationStatement::accept(GS_Visitor *visitor) {
        visitor->visit(this);
    }

    StatementType GS_DeclarationStatement::getStatementType() {
        return StatementType::DeclarationStatement;
    }

}
