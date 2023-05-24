#ifndef GSLANGUAGE_GS_PARSER_H
#define GSLANGUAGE_GS_PARSER_H

#include <Lexer/Lexer.h>

#include <AST/AST.h>

namespace GSLanguageCompiler::Parser {

    /*
     * TODO: Create Grammar file (GRAMMAR.md or Grammar.md in docs or Grammar.h in Parser module)
     */

    /**
     *
     * Program
     *
     * program -> translation_unit_decl
     *
     * translation_unit_decl -> decl...
     *
     */

    /**
     * Declaration
     *
     * decl -> func_decl (, translation_unit_decl (using only in compiler infrastructure, not in real programs!))
     *
     * func_decl -> 'func' id '(' ')' '{' stmt... '}'
     *
     */

    /**
     * Statement
     *
     * stmt -> var_decl_stmt, assignment_stmt, expr_stmt
     *
     * var_decl_stmt -> 'var' id (':' id) '=' rvalue_expr
     *
     * assignment_stmt -> lvalue_expr '=' rvalue_expr
     *
     * expr_stmt -> expr
     *
     */

    /**
     *
     * Expression
     *
     * expr -> paren_expr (only in grammar), const_expr, unary_expr, binary_expr, array_expr, var_using_expr, func_call_expr
     *
     * paren_expr -> '(' expr ')'
     *
     * lvalue_expr -> var_using_expr
     *
     * rvalue_expr -> const_expr, unary_expr, binary_expr, array_expr, var_using_expr, func_call_expr
     *
     * const_expr -> num, str
     *
     * unary_expr -> unary_op expr
     *
     * unary_op -> '-'
     *
     * binary_expr -> expr binary_op expr
     *
     * binary_op -> '+', '-', '*', '/'
     *
     * array_expr -> '[' expr (, expr)... ']'
     *
     * var_using_expr -> id
     *
     * func_call_expr -> id '(' (expr...) ')'
     *
     * expr -> unary_expr binary_expr_rhs, array_expr
     *
     * unary_expr -> (unary_op) primary_expr
     *
     * binary_expr_rhs -> binary_op unary_expr
     *
     * primary_expr -> const_expr, var_using_expr, func_call_expr, paren_expr
     *
     */

    /**
     * Class for parsing and creating AST from tokens
     * @todo Add to parser lexer?
     */
    class GS_Parser {
    public:

        /**
         * Constructor for parser
         * @param session Session
         * @param tokenBuffer Token buffer
         */
        GS_Parser(LRef<Driver::GS_Session> session,
                  ConstLRef<Lexer::GS_TokenBuffer> tokenBuffer);

    public:

        /**
         * Creating parser
         * @param session Session
         * @param tokenBuffer Token buffer
         * @return Parser
         */
        static GS_Parser Create(LRef<Driver::GS_Session> session,
                                ConstLRef<Lexer::GS_TokenBuffer> tokenBuffer);

    public:

        /**
         * Creating parser and parsing tokens
         * @param session Session
         * @param tokenBuffer Token buffer
         * @param translationUnitName Translation unit name
         * @return Translation unit declaration
         */
        static AST::GSTranslationUnitDeclarationPtr Run(LRef<Driver::GS_Session> session,
                                                        ConstLRef<Lexer::GS_TokenBuffer> tokenBuffer,
                                                        UString translationUnitName);

    public:

        /**
         * Parsing program
         * @param programName Program name
         * @return Program (translation unit declaration)
         */
        AST::GSTranslationUnitDeclarationPtr ParseProgram(UString programName);

    private:

        /**
         * Parsing translation unit declaration
         * @param translationUnitName Translation unit name
         * @return Translation unit declaration
         */
        AST::GSTranslationUnitDeclarationPtr ParseTranslationUnitDeclaration(UString translationUnitName);

        /**
         * Parsing declaration
         * @return Declaration
         */
        AST::GSDeclarationPtr ParseDeclaration();

        /**
         * Parsing function declaration
         * @return Function declaration
         */
        AST::NodePtr<AST::GS_FunctionDeclaration> ParseFunctionDeclaration();

        /**
         * Parsing statement
         * @return Statement
         */
        AST::GSStatementPtr ParseStatement();

        /**
         * Parsing variable declaration statement
         * @return Variable declaration statement
         */
        AST::NodePtr<AST::GS_VariableDeclarationStatement> ParseVariableDeclarationStatement();

        /**
         * Parsing assignment statement
         * @return Assignment statement
         */
        AST::NodePtr<AST::GS_AssignmentStatement> ParseAssignmentStatement();

        /**
         * Parsing expression statement
         * @return Expression statement
         */
        AST::NodePtr<AST::GS_ExpressionStatement> ParseExpressionStatement();

        /**
         * Parsing expression
         * @return Expression
         */
        AST::GSExpressionPtr ParseExpression();

        /**
         * Parsing left value expression
         * @return Left value expression
         */
        AST::GSExpressionPtr ParseLValueExpression();

        /**
         * Parsing right value expression
         * @return Right value expression
         */
        AST::GSExpressionPtr ParseRValueExpression();

        /**
         * Parsing constant expression
         * @return Constant expression
         */
        AST::GSExpressionPtr ParseConstantExpression();

        /**
         * Parsing unary expression
         * @return Unary expression
         */
        AST::GSExpressionPtr ParseUnaryExpression();

        /**
         * Parsing binary expression
         * @param precedence Expression precedence
         * @param expression Expression
         * @return Binary expression
         */
        AST::GSExpressionPtr ParseBinaryExpression(I32 precedence,
                                                   LRef<AST::GSExpressionPtr> expression);

        /**
         * Parsing array expression
         * @return Array expression
         */
        AST::NodePtr<AST::GS_ArrayExpression> ParseArrayExpression();

        /**
         * Parsing variable using expression
         * @return Variable using expression
         */
        AST::NodePtr<AST::GS_VariableUsingExpression> ParseVariableUsingExpression();

        /**
         * Parsing function calling expression
         * @return Function calling expression
         */
        AST::NodePtr<AST::GS_FunctionCallingExpression> ParseFunctionCallingExpression();

        /**
         * Parsing paren expression
         * @return Paren expression (expression)
         */
        AST::GSExpressionPtr ParseParenExpression();

        /**
         * Parsing primary expression
         * @return Primary expression
         */
        AST::GSExpressionPtr ParsePrimaryExpression();

        /**
         * Parsing value
         * @return Value
         */
        AST::GSValuePtr ParseValue();

        /**
         * Parsing type
         * @return Type
         */
        Semantic::GSTypePtr ParseType();

        /**
         * Helper function for saving parser state, trying parse any node and if failure return to previous parser state or return result if success
         * @tparam ReturnT Return parser method type
         * @param method Parser method
         * @return If success result or null if failure
         */
        template<typename ReturnT>
        inline ReturnT TryParse(ReturnT (GS_Parser::*method)()) {
            auto messages = _messages;

            auto tokenIterator = _tokenIterator;

            auto result = (this->*method)();

            if (!result) {
                _messages = messages;

                _tokenIterator = tokenIterator;

                return nullptr;
            }

            return result;
        }

        /**
         * Getting current token precedence
         * @return Current token precedence
         */
        I32 TokenPrecedence();

        /**
         * Is equal token types in token iterator and input token type
         * @param type Token type for check
         * @return Is equal token types
         */
        Bool IsTokenType(Lexer::TokenType type);

        /**
         * Getting current token
         * @return Current token
         */
        Lexer::GS_Token CurrentToken();

        /**
         * Getting current token type
         * @return Current token type
         */
        Lexer::TokenType TokenType();

        /**
         * Getting current token value
         * @return Current token value
         */
        UString TokenValue();

        /**
         * Getting current token location
         * @return Current token location
         */
        IO::GSByteSourceRange TokenLocation();

        /**
         * Setting token iterator to next token in token buffer
         * @return Void return
         */
        Void NextToken();

        /**
         * Adding new error message to message buffer with input text and current token location
         * @param messageText Message text
         * @return Void return
         * @todo Change new return type?
         */
        Void ErrorMessage(UString messageText);

    private:

        /**
         * Session
         */
        LRef<Driver::GS_Session> _session;

        /**
         * Messages
         * @todo Update message containing and flushing system
         */
        IO::GSMessageArray _messages;

        /**
         * Token buffer
         */
        ConstLRef<Lexer::GS_TokenBuffer> _tokenBuffer;

        /**
         * Token buffer iterator (token cursor)
         * @todo Create token and source cursors?
         */
        Lexer::GS_TokenBuffer::ConstIterator _tokenIterator;

        /**
         * AST builder
         */
        AST::GSASTBuilderPtr _builder;
    };

    /**
     * Parsing program from source
     * @param session Session
     * @param source Source
     * @return Translation unit declaration
     */
    AST::GSTranslationUnitDeclarationPtr ParseProgram(LRef<Driver::GS_Session> session,
                                                      ConstLRef<IO::GS_Source> source);

    /**
     * Parsing program from file
     * @param session Session
     * @param fileName File name
     * @return Translation unit declaration
     */
    AST::GSTranslationUnitDeclarationPtr ParseProgramFromFile(LRef<Driver::GS_Session> session,
                                                              UString fileName);

    /**
     * Parsing program from string
     * @param session Session
     * @param string String
     * @return Translation unit declaration
     */
    AST::GSTranslationUnitDeclarationPtr ParseProgramFromString(LRef<Driver::GS_Session> session,
                                                                UString string);

}

#endif //GSLANGUAGE_GS_PARSER_H
