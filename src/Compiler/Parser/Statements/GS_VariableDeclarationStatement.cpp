#include <Statements/GS_VariableDeclarationStatement.h>

namespace GSLanguageCompiler::Parser {

    GS_VariableDeclarationStatement::GS_VariableDeclarationStatement(const std::string &name) {
        this->_name = name;
        this->_type = "Null";
    }

    GS_VariableDeclarationStatement::GS_VariableDeclarationStatement(const std::string &name, const std::string &type) {
        this->_name = name;
        this->_type = type;
    }

    std::string GS_VariableDeclarationStatement::getType() {
        return this->_type;
    }

    std::string GS_VariableDeclarationStatement::getName() {
        return this->_name;
    }

    void GS_VariableDeclarationStatement::setType(const std::string &type) {
        this->_type = type;
    }

    StatementType GS_VariableDeclarationStatement::getStatementType() {
        return StatementType::VARIABLE_DECLARATION;
    }

    std::string GS_VariableDeclarationStatement::generateCode() {
        return "reserve " + this->_name + "\n";
    }

    std::string GS_VariableDeclarationStatement::toStringForDebug() {
        return "["
               + this->_name
               + ": "
//               + convertLiteralToString(this->_type)
               + "]";
    }

}