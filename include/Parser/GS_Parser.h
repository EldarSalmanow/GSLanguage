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

        GS_Parser(LRef<Lexer::GS_TokenStream> tokenStream, AST::GSASTContextPtr context, IO::GSMessageHandlerPtr messageHandler);

    public:

        static GS_Parser Create(LRef<Lexer::GS_TokenStream> tokenStream, AST::GSASTContextPtr context, IO::GSMessageHandlerPtr messageHandler);

        static GS_Parser Create(LRef<Lexer::GS_TokenStream> tokenStream, IO::GSMessageHandlerPtr messageHandler);

        static GS_Parser Create(LRef<Lexer::GS_TokenStream> tokenStream);

    public:

        AST::GSTranslationUnitDeclarationPtr Parse();

    public:

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
        inline T TryParse(T (GS_Parser:: *method) ()) {
            auto stream = _stream;
            auto context = _context;
            auto builder = _builder;
            auto errorHandler = _messageHandler;

            auto result = (this->*method)();

            if (!result) {
                _stream = stream;
                _context = context;
                _builder = builder;
                _messageHandler = errorHandler;

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

        Lexer::GS_TokenLocation TokenLocation();

        Void NextToken();

        // TODO update
        Void AddError(UString error);

    private:

        Lexer::GS_TokenStream _stream;

        AST::GSASTContextPtr _context;

        AST::GSASTBuilderPtr _builder;

        IO::GSMessageHandlerPtr _messageHandler;
    };

}

#endif //GSLANGUAGE_GS_PARSER_H
