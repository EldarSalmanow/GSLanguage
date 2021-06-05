#include <Statements/GS_AssignmentStatement.h>

namespace GSLanguageCompiler::Parser {

    GS_AssignmentStatement::GS_AssignmentStatement(GS_VariableDeclarationStatement &variableDeclaration,
                                                   GSExpressionPointer expression) {
        this->_variableDeclaration = variableDeclaration;
        this->_expression = expression;

        this->_variableDeclaration.setType("Null");
    }

    GS_VariableDeclarationStatement GS_AssignmentStatement::getVariableDeclarationStatement() {
        return this->_variableDeclaration;
    }

    GSExpressionPointer GS_AssignmentStatement::getExpression() {
        return this->_expression;
    }

    StatementType GS_AssignmentStatement::getStatementType() {
        return StatementType::ASSIGNMENT;
    }

    std::string GS_AssignmentStatement::generateCode() {
        return this->_variableDeclaration.generateCode()
        + this->_expression->generateCode()
        + "save " + this->_variableDeclaration.getName() + "\n";
    }

    std::string GS_AssignmentStatement::toStringForDebug() {
        return "["
               + this->_variableDeclaration.toStringForDebug()
               + " = "
               + this->_expression->toStringForDebug()
               + "]";
    }

}