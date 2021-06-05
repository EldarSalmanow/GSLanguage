#ifndef GSLANGUAGE_GS_CODEGENERATOR_H
#define GSLANGUAGE_GS_CODEGENERATOR_H

#include <Compiler/Parser/GS_Parser.h>

#include <Compiler/CodeGenerator/GS_Section.h>
#include <Compiler/CodeGenerator/GS_VariablesTable.h>

namespace GSLanguageCompiler::CodeGenerator {

    typedef std::string GSGeneratedCode;

    /**
     *
     */
    class GS_CodeGenerator {
    public:

        /**
         *
         * @param statements
         */
        GS_CodeGenerator(Parser::GSStatementPointerArray &statements);

    public:

        /**
         *
         * @return
         */
        GSGeneratedCode generateCode();

    private:

        /**
         *
         * @return
         */
        void _generateAssignmentStatement();

        /**
         *
         * @return
         */
        void _generateVariableDeclarationStatement();

        /**
         *
         * @param expression
         * @return
         */
        std::string _generateExpression(Parser::GSExpressionPointer expression);

        /**
         *
         * @param expression
         * @return
         */
        std::string _generateValueExpression(Parser::GSExpressionPointer expression);

        /**
         *
         * @param expression
         * @return
         */
        std::string _generateBinaryExpression(Parser::GSExpressionPointer expression);

        /**
         *
         * @param expression
         * @return
         */
        std::string _generateUnaryExpression(Parser::GSExpressionPointer expression);

    private:

        /**
         *
         */
        Parser::GSStatementPointerArray _statements;

        /**
         *
         */
        Parser::GSStatementPointerArray::iterator _statementIterator;

        /**
         *
         */
        GS_Section _textSection;

        /**
         *
         */
        GS_Section _dataSection;

        /**
         *
         */
        GS_Section _bssSection;

    };

    typedef std::shared_ptr<GS_CodeGenerator> GSCodeGeneratorPointer;

}

#endif //GSLANGUAGE_GS_CODEGENERATOR_H
