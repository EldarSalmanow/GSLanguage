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

        GS_Parser(LRef<Lexer::GS_TokenStream> tokenStream, AST::GSASTContextPtr context);

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

        I32 TokenPrecedence();

        Bool IsTokenType(Lexer::TokenType type);

        Lexer::GS_TokenLocation TokenLocation();

        UString TokenValue();

        Lexer::TokenType TokenType();

        Lexer::GS_Token CurrentToken();

        Void NextToken();

    private:

        Lexer::GS_TokenStream _stream;

        AST::GSASTContextPtr _context;

        AST::GSASTBuilderPtr _builder;
    };

}

#endif //GSLANGUAGE_GS_PARSER_H
