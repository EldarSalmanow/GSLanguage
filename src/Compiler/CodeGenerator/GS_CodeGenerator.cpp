#include <GS_CodeGenerator.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CodeGenerator::GS_CodeGenerator(Parser::GSStatementPointerArray &statements) {
        this->_statements = statements;
    }

    GSGeneratedCode GS_CodeGenerator::generateCode() {
        GSGeneratedCode generatedCode;

        _textSection.addLineToSection("section .text\n"
                                      "global _Fmain4\n\n"
                                      "extern ExitProcess\n\n"
                                      "_Fmain4:\n");
        _dataSection.addLineToSection("section .data\n");
        _bssSection.addLineToSection("section .bss\n");

        _statementIterator = _statements.begin();

        while (_statementIterator != _statements.end()) {
            switch (_statementIterator[0]->getStatementType()) {
                case Parser::StatementType::ASSIGNMENT:
                    _generateAssignmentStatement();
                    break;
                case Parser::StatementType::VARIABLE_DECLARATION:
                    _generateVariableDeclarationStatement();
                    break;
            }
        }

        _textSection.addLineToSection("\tmov eax, 0\n"
                                      "\tcall _FSystem6Exit4\n");

        _textSection.addLineToSection("_FSystem6Exit4:\n"
                                      "\tpush eax\n"
                                      "\tcall ExitProcess\n");

        generatedCode += _dataSection.getSectionCode();
        generatedCode += _bssSection.getSectionCode();
        generatedCode += _textSection.getSectionCode();

//        for (auto statement : _statements) {
//            generatedCode += statement->generateCode();
//        }

        return generatedCode;
    }

    void GS_CodeGenerator::_generateAssignmentStatement() {
        GSGeneratedCode assignmentStatementCode;

        Parser::GS_AssignmentStatement assignmentStatement = *static_cast<Parser::GS_AssignmentStatement *>(_statementIterator[0].get());

        Parser::GS_VariableDeclarationStatement variableDeclarationStatement = assignmentStatement.getVariableDeclarationStatement();

        std::string variableName;
        std::string dataSize;
        std::string moveSize;
        int dataNumberSize;

//        if (variableDeclarationStatement.getType() == "Int") {
//            dataSize = "resd"; // reserve 4 bytes
//            moveSize = "dword";
//            dataNumberSize = 1;
//        } else {
//            throw Exceptions::GS_NotSupportedException("Compiling for string and other types not supported!");
//        }
        // TODO rewrite generating for assignment statement

        dataSize = "resd"; // reserve 4 bytes
        moveSize = "dword";
        dataNumberSize = 1;

        variableName = "_V"
                       + variableDeclarationStatement.getName()
                       + std::to_string(variableDeclarationStatement.getName().size());

        _bssSection.addLineToSection(
                "\t" + variableName + " " + dataSize + " " + std::to_string(dataNumberSize) + "\n");

        _textSection.addLineToSection(_generateExpression(assignmentStatement.getExpression()));
        _textSection.addLineToSection("\tmov " + moveSize + "[" + variableName + "], eax\n");

        ++_statementIterator;

        return;
    }

    void GS_CodeGenerator::_generateVariableDeclarationStatement() {
        throw Exceptions::GS_NotSupportedException("Generating code for variable declaration statements not supported!");
    }

    std::string GS_CodeGenerator::_generateExpression(Parser::GSExpressionPointer expression) {
        switch (expression->getExpressionType()) {
            case Parser::ExpressionType::VALUE:
                return _generateValueExpression(expression);
            case Parser::ExpressionType::BINARY:
                return _generateBinaryExpression(expression);
            case Parser::ExpressionType::UNARY:
                return _generateUnaryExpression(expression);
        }
    }

    std::string GS_CodeGenerator::_generateValueExpression(Parser::GSExpressionPointer expression) {
        Parser::GS_ValueExpression valueExpression = *static_cast<Parser::GS_ValueExpression *>(expression.get());
        return "\tmov eax, " + std::to_string(std::any_cast<int>(valueExpression.getValue()->getData())) + "\n";
    }

    std::string GS_CodeGenerator::_generateBinaryExpression(Parser::GSExpressionPointer expression) {
        throw Exceptions::GS_NotSupportedException("Generating code for binary expressions not supported!");
    }

    std::string GS_CodeGenerator::_generateUnaryExpression(Parser::GSExpressionPointer expression) {
        throw Exceptions::GS_NotSupportedException("Generating code for unary expressions not supported!");
    }

}