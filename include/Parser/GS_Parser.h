#ifndef GSLANGUAGE_GS_PARSER_H
#define GSLANGUAGE_GS_PARSER_H

#include <Lexer/GS_TokenStream.h>

#include <AST/GS_IncludeAll.h>

namespace GSLanguageCompiler::Parser {

    /**
     * Class for generating and parsing AST
     */
    class GS_Parser {
    public:

        /**
         * Constructor for GS_Parser
         * @param stream Input tokens stream
         */
        explicit GS_Parser(Lexer::GS_TokenStream stream);

    public:

        /**
         * Main function for start parsing
         * @return Program AST
         */
        AST::GSDeclarationPtrArray parse();

    private:

        /**
         * Parse program
         * @return Program AST
         */
        AST::GSDeclarationPtrArray _parseProgram();

        /**
         * Parse declaration
         * @return Declaration node
         */
        AST::GSDeclarationPtr _parseDeclaration();

        /**
         * Parse function declaration
         * @return Function declaration node
         */
        AST::GSDeclarationPtr _parseFunctionDeclaration();

        /**
         * Parse statement
         * @return Statement node
         */
        AST::GSStatementPtr _parseStatement();

        /**
         * Parse variable declaration
         * @return Variable declaration node
         */
        AST::GSStatementPtr _parseVariableDeclaration();

        /**
         * Parse assignment statement
         * @return Assignment statement node
         */
        AST::GSStatementPtr _parseAssignmentStatement();

        /**
         * Parse expression
         * @return Expression node
         */
        AST::GSExpressionPtr _parseExpression();

        /**
         * Parse binary expression
         * @param expressionPrecedence Expression precedence
         * @param expression Expression
         * @return Binary expression node
         */
        AST::GSExpressionPtr _parseBinaryExpression(I32 expressionPrecedence, AST::GSExpressionPtr expression);

        /**
         * Parse unary expression
         * @return Unary expression node
         */
        AST::GSExpressionPtr _parseUnaryExpression();

        /**
         * Parse primary expression
         * @return Primary expression nodes
         */
        AST::GSExpressionPtr _parsePrimaryExpression();

    private:

        /**
         * Current token precedence
         * @return Current token precedence
         */
        I32 _currentTokenPrecedence();

    private:

        /**
         * Input tokens stream
         */
        Lexer::GS_TokenStream _tokenStream;

        /**
         * Operators precedence
         */
        Map<Lexer::TokenType, I32> _operatorsPrecedence;
    };

}

#endif //GSLANGUAGE_GS_PARSER_H
