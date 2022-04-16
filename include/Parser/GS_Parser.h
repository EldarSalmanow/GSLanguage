#ifndef GSLANGUAGE_GS_PARSER_H
#define GSLANGUAGE_GS_PARSER_H

#include <Lexer/Lexer.h>

#include <AST/AST.h>

namespace GSLanguageCompiler::Parser {

    // TODO reorganise parsing process
    class GS_Parser {
    public:

        explicit GS_Parser(LRef<Lexer::GS_TokenStream> tokenStream);

    public:

        AST::GSTranslationUnitDeclarationPtr Parse();

    private:

        AST::GSDeclarationPtr ParseDeclaration();

        SharedPtr<AST::GS_FunctionDeclaration> ParseFunctionDeclaration();

        AST::GSStatementPtr ParseStatement();

        SharedPtr<AST::GS_AssignmentStatement> ParseAssignmentStatement();

        SharedPtr<AST::GS_AssignmentStatement> ParseAssignmentStatement(ConstLRef<AST::GSExpressionPtr> lvalueExpression);

        SharedPtr<AST::GS_VariableDeclarationStatement> ParseVariableDeclarationStatement();

        SharedPtr<AST::GS_ExpressionStatement> ParseExpressionStatement();

        SharedPtr<AST::GS_ExpressionStatement> ParseExpressionStatement(ConstLRef<AST::GSExpressionPtr> expression);

        AST::GSExpressionPtr ParseExpression();

        AST::GSExpressionPtr ParseLValueExpression();

        AST::GSExpressionPtr ParseRValueExpression();

        AST::GSExpressionPtr ParseVariableUsingExpression();

        AST::GSExpressionPtr ParseBinaryExpression(I32 expressionPrecedence, LRef<AST::GSExpressionPtr> expression);

        AST::GSExpressionPtr ParseUnaryExpression();

        AST::GSExpressionPtr ParseConstantExpression();

        AST::GSTypePtr ParseType();

    public:

        I32 TokenPrecedence();

        Bool IsTokenType(Lexer::TokenType type);

        UString TokenValue();

        Lexer::TokenType TokenType();

        Lexer::GS_Token CurrentToken();

        Void NextToken();

    private:

        Lexer::GS_TokenStream _stream;
    };

    /**
     * Class for generating and parsing AST
     */
//    class GS_Parser {
//    public:
//
//        /**
//         * Constructor for GS_Parser
//         * @param stream Input tokens stream
//         */
//        explicit GS_Parser(Ptr<Lexer::GS_TokenStream> stream);
//
//    public:
//
//        /**
//         * Main function for start parsing
//         * @return Program AST
//         */
//        AST::GSDeclarationPtrArray parse();
//
//    private:
//
//        /**
//         * Parse program
//         * @return Program AST
//         */
//        AST::GSDeclarationPtrArray _parseProgram();
//
//        /**
//         * Parse declaration
//         * @return Declaration node
//         */
//        AST::GSDeclarationPtr _parseDeclaration();
//
//        /**
//         * Parse function declaration
//         * @return Function declaration node
//         */
//        AST::GSDeclarationPtr _parseFunctionDeclaration();
//
//        /**
//         * Parse statement
//         * @return Statement node
//         */
//        AST::GSStatementPtr _parseStatement();
//
//        /**
//         * Parse variable declaration
//         * @return Variable declaration node
//         */
//        AST::GSStatementPtr _parseVariableDeclaration();
//
//        /**
//         * Parse assignment statement
//         * @return Assignment statement node
//         */
//        AST::GSStatementPtr _parseAssignmentStatement();
//
//        /**
//         * Parse expression
//         * @return Expression node
//         */
//        AST::GSExpressionPtr _parseExpression();
//
//        /**
//         * Parse binary expression
//         * @param expressionPrecedence Expression precedence
//         * @param expression Expression
//         * @return Binary expression node
//         */
//        AST::GSExpressionPtr _parseBinaryExpression(I32 expressionPrecedence, AST::GSExpressionPtr expression);
//
//        /**
//         * Parse unary expression
//         * @return Unary expression node
//         */
//        AST::GSExpressionPtr _parseUnaryExpression();
//
//        /**
//         * Parse primary expression
//         * @return Primary expression nodes
//         */
//        AST::GSExpressionPtr _parsePrimaryExpression();
//
//    private:
//
//        /**
//         *
//         * @return
//         */
//        Void _nextToken();
//
//        /**
//         * Current token precedence
//         * @return Current token precedence
//         */
//        I32 _currentTokenPrecedence();
//
//        /**
//         *
//         * @param type
//         * @return
//         */
//        Bool _isEqualTokenTypes(Lexer::TokenType type);
//
//    private:
//
//        /**
//         * Input tokens stream
//         */
//        Ptr<Lexer::GS_TokenStream> _tokenStream;
//
//        /**
//         *
//         */
//        Lexer::GSTokenPtr _token;
//    };

}

#endif //GSLANGUAGE_GS_PARSER_H
