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
     * decl -> func_decl (, translation_unit_decl (only in AST, not in real programs!))
     *
     * func_decl -> 'func' id '(' ')' '{' stmt... '}'
     *
     */

    /**
     * Statement
     *
     * stmt -> var_decl_stmt, assignment_stmt, expr_stmt
     *
     * var_decl_stmt -> 'var' id (':' id) '=' rvalue_expr (?)
     *
     * assignment_stmt -> lvalue_expr '=' rvalue_expr (?)
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

    class GS_Parser {
    public:

        GS_Parser(Lexer::GSTokenArray tokens, Driver::GSContextPtr context);

    public:

        static GS_Parser Create(Lexer::GSTokenArray tokens, Driver::GSContextPtr context);

        static GS_Parser Create(Driver::GSContextPtr context);

    public:

        AST::GSTranslationUnitDeclarationPtr ParseProgram();

        AST::GSTranslationUnitDeclarationPtr ParseProgram(Lexer::GSTokenArray tokens);

    public:

        AST::GSTranslationUnitDeclarationPtr ParseTranslationUnitDeclaration(UString translationUnitName);

        AST::GSTranslationUnitDeclarationPtr ParseTranslationUnitDeclaration();

        AST::GSDeclarationPtr ParseDeclaration();

        std::shared_ptr<AST::GS_FunctionDeclaration> ParseFunctionDeclaration();

        AST::GSStatementPtr ParseStatement();

        std::shared_ptr<AST::GS_VariableDeclarationStatement> ParseVariableDeclarationStatement();

        std::shared_ptr<AST::GS_AssignmentStatement> ParseAssignmentStatement();

        std::shared_ptr<AST::GS_ExpressionStatement> ParseExpressionStatement();

        AST::GSExpressionPtr ParseExpression();

        AST::GSExpressionPtr ParseLValueExpression();

        AST::GSExpressionPtr ParseRValueExpression();

        AST::GSExpressionPtr ParseConstantExpression();

        AST::GSExpressionPtr ParseUnaryExpression();

        AST::GSExpressionPtr ParseBinaryExpression(I32 precedence, LRef<AST::GSExpressionPtr> expression);

        AST::GSExpressionPtr ParseVariableUsingExpression();

        AST::GSExpressionPtr ParseFunctionCallingExpression();

        AST::GSExpressionPtr ParsePrimaryExpression();

    public:

        AST::GSValuePtr ParseValue();

        Semantic::GSTypePtr ParseType();

    public:

        // check
        template<typename T>
        inline T TryParse(T (GS_Parser::*method)()) {
            // TODO add error recovering

            auto tokensIterator = _tokensIterator;

            auto result = (this->*method)();

            if (!result) {
                _tokensIterator = tokensIterator;

                return nullptr;
            }

            return result;
        }

    public:

        I32 TokenPrecedence();

        Bool IsTokenType(Lexer::TokenType type);

        Lexer::GS_Token CurrentToken();

        Lexer::TokenType TokenType();

        UString TokenValue();

        Void NextToken();

        Void Message(UString message, IO::MessageLevel messageLevel);

    private:

        Driver::GSContextPtr _context;

        Lexer::GSTokenArray _tokens;

        Lexer::GSTokenArrayIterator _tokensIterator;

        AST::GSASTBuilderPtr _builder;
    };

}

#endif //GSLANGUAGE_GS_PARSER_H
