#ifndef GSLANGUAGE_GS_PARSER_H
#define GSLANGUAGE_GS_PARSER_H

#include <Lexer/Lexer.h>

#include <AST/AST.h>

namespace GSLanguageCompiler::Parser {

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
     * expr -> const_expr, unary_expr, binary_expr, var_using_expr, func_call_expr
     *
     * lvalue_expr -> var_using_expr
     *
     * rvalue_expr -> const_expr, unary_expr, binary_expr, var_using_expr, func_call_expr
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
     * var_using_expr -> id
     *
     * func_call_expr -> id '(' (expr...) ')'
     *
     */

    /**
     * Class for parsing and creating AST from tokens
     */
    class GS_Parser {
    public:

        /**
         * Constructor for parser
         * @param session Session
         * @param tokensBuffer Tokens buffer
         */
        GS_Parser(LRef<Driver::GS_Session> session,
                  ConstLRef<Lexer::GS_TokensBuffer> tokensBuffer);

    public:

        /**
         * Creating parser
         * @param session Session
         * @param tokensBuffer Tokens buffer
         * @return Parser
         */
        static GS_Parser Create(LRef<Driver::GS_Session> session,
                                ConstLRef<Lexer::GS_TokensBuffer> tokensBuffer);

    public:

        /**
         * Creating parser and parsing tokens
         * @param session Session
         * @param tokensBuffer Tokens buffer
         * @param translationUnitName Translation unit name
         * @return Translation unit declaration
         */
        static AST::GSTranslationUnitDeclarationPtr Run(LRef<Driver::GS_Session> session,
                                                        ConstLRef<Lexer::GS_TokensBuffer> tokensBuffer,
                                                        UString translationUnitName);

    public:

        AST::GSTranslationUnitDeclarationPtr ParseProgram(UString translationUnitName);

    private:

        AST::GSTranslationUnitDeclarationPtr ParseTranslationUnitDeclaration(UString translationUnitName);

        AST::GSDeclarationPtr ParseDeclaration();

        AST::NodePtr<AST::GS_FunctionDeclaration> ParseFunctionDeclaration();

        AST::GSStatementPtr ParseStatement();

        AST::NodePtr<AST::GS_VariableDeclarationStatement> ParseVariableDeclarationStatement();

        AST::NodePtr<AST::GS_AssignmentStatement> ParseAssignmentStatement();

        AST::NodePtr<AST::GS_ExpressionStatement> ParseExpressionStatement();

        AST::GSExpressionPtr ParseExpression();

        AST::GSExpressionPtr ParseLValueExpression();

        AST::GSExpressionPtr ParseRValueExpression();

        AST::GSExpressionPtr ParseConstantExpression();

        AST::GSExpressionPtr ParseUnaryExpression();

        AST::GSExpressionPtr ParseBinaryExpression(I32 precedence, LRef<AST::GSExpressionPtr> expression);

        AST::NodePtr<AST::GS_ArrayExpression> ParseArrayExpression();

        AST::GSExpressionPtr ParseVariableUsingExpression();

        AST::GSExpressionPtr ParseFunctionCallingExpression();

        AST::GSExpressionPtr ParsePrimaryExpression();

    private:

        AST::GSValuePtr ParseValue();

        Semantic::GSTypePtr ParseType();

    private:

        template<typename T>
        inline T TryParse(T (GS_Parser::*method)()) {
//            auto messages = _messages;

            auto tokensIterator = _tokensIterator;

            auto result = (this->*method)();

            if (!result) {
//                _messages = messages;

                _tokensIterator = tokensIterator;

                return nullptr;
            }

            return result;
        }

    private:

        I32 TokenPrecedence();

        Bool IsTokenType(Lexer::TokenType type);

        Lexer::GS_Token CurrentToken();

        Lexer::TokenType TokenType();

        UString TokenValue();

        IO::GS_SourceLocation TokenLocation();

        Void NextToken();

        Void Message(UString message, IO::MessageLevel messageLevel);

        Void LocatedMessage(UString message, IO::MessageLevel messageLevel, IO::GS_SourceLocation messageLocation);

    private:

        LRef<Driver::GS_Session> _session;

//        IO::GSMessagePtrArray _messages;

        ConstLRef<Lexer::GS_TokensBuffer> _tokensBuffer;

        Lexer::GS_TokensBuffer::ConstIterator _tokensIterator;

        AST::GSASTBuilderPtr _builder;
    };

    /**
     * Parsing program from source
     * @param session Session
     * @param source Source
     * @return Translation unit declaration
     */
    AST::GSTranslationUnitDeclarationPtr ParseProgram(LRef<Driver::GS_Session> session, ConstLRef<IO::GS_Source> source);

    /**
     * Parsing program from file
     * @param session Session
     * @param fileName File name
     * @return Translation unit declaration
     */
    AST::GSTranslationUnitDeclarationPtr ParseProgramFromFile(LRef<Driver::GS_Session> session, UString fileName);

    /**
     * Parsing program from string
     * @param session Session
     * @param string String
     * @return Translation unit declaration
     */
    AST::GSTranslationUnitDeclarationPtr ParseProgramFromString(LRef<Driver::GS_Session> session, UString string);

}

#endif //GSLANGUAGE_GS_PARSER_H
