#ifndef GSLANGUAGE_GS_PARSER_H
#define GSLANGUAGE_GS_PARSER_H

#include <Lexer/Lexer.h>

#include <AST/AST.h>

namespace GSLanguageCompiler::Parser {

    /**
     *
     * Parser Grammar
     *
     * translation_unit_decl -> decl...
     *
     * decl -> func_decl (, translation_unit_decl)
     *
     * func_decl -> 'func' id '(' ')' '{' stmt... '}'
     *
     * stmt -> var_decl_stmt, assignment_stmt, expr_stmt
     *
     * var_decl_stmt -> 'var' id (':' id) '=' rvalue_expr
     *
     * assignment_stmt -> lvalue_expr '=' rvalue_expr
     *
     * expr_stmt -> expr
     *
     * expr -> lvalue_expr, rvalue_expr
     *
     * lvalue_expr -> var_using_expr
     *
     * var_using_expr -> id
     *
     * rvalue_expr -> const_expr, unary_expr, binary_expr
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
     * Lexer Grammar
     *
     * id -> [A-z]([A-z] | [0-9])*
     *
     * num -> [1-9]([0-9])*
     *
     * str -> '"' * '"'
     *
     */

    // TODO reorganise parsing process
    // UPD: in progress
    class GS_Parser {
    public:

        explicit GS_Parser(LRef<Lexer::GS_TokenStream> tokenStream);

    public:

        AST::GSTranslationUnitDeclarationPtr Parse();

    public:

        AST::GSTranslationUnitDeclarationPtr ParseTranslationUnitDeclaration();

        AST::GSDeclarationPtr ParseDeclaration();

        SharedPtr<AST::GS_FunctionDeclaration> ParseFunctionDeclaration();

        AST::GSStatementPtr ParseStatement();

        SharedPtr<AST::GS_VariableDeclarationStatement> ParseVariableDeclarationStatement();

        SharedPtr<AST::GS_AssignmentStatement> ParseAssignmentStatement();

        SharedPtr<AST::GS_ExpressionStatement> ParseExpressionStatement();

        AST::GSExpressionPtr ParseExpression();

        AST::GSExpressionPtr ParseLValueExpression();

        AST::GSExpressionPtr ParseVariableUsingExpression();

        AST::GSExpressionPtr ParseRValueExpression();

        AST::GSExpressionPtr ParseConstantExpression();

        AST::GSExpressionPtr ParseUnaryExpression();

        AST::GSExpressionPtr ParseBinaryExpression(I32 precedence, LRef<AST::GSExpressionPtr> expression);

        AST::GSExpressionPtr ParsePrimaryExpression();

    public:

        AST::GSValuePtr ParseValue();

        AST::GSTypePtr ParseType();

    public:

        template<typename Ret, typename... Args>
        Ret TryParse(Ret (GS_Parser::* function)(Args...)) {
            auto stream = _stream;

            auto result = function();

            if (!result) {
                _stream = stream;

                return nullptr;
            }

            return result;
        }

    public:

        I32 TokenPrecedence();

        Bool IsTokenType(Lexer::TokenType type);

        UString TokenValue();

        Lexer::TokenType TokenType();

        Lexer::GS_Token CurrentToken();

        Void NextToken();

    private:

        Lexer::GS_TokenStream _stream;

        AST::GSASTBuilderPtr _builder;
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
