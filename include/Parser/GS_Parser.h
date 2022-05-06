#ifndef GSLANGUAGE_GS_PARSER_H
#define GSLANGUAGE_GS_PARSER_H

#include <Lexer/Lexer.h>

#include <AST/AST.h>

namespace GSLanguageCompiler::Parser {

    // TODO update error handler

    class GS_Error {
    public:

        explicit GS_Error(UString message)
                : _message(std::move(message)) {}

    public:

        static GS_Error Create(UString message) {
            return GS_Error(std::move(message));
        }

    public:

        UString GetMessage() const {
            return _message;
        }

    private:

        UString _message;
    };

    class GS_ErrorHandler {
    public:

        GS_ErrorHandler() = default;

    public:

        static SharedPtr<GS_ErrorHandler> Create() {
            return std::make_shared<GS_ErrorHandler>();
        }

    public:

        Void AddError(UString message) {
            _errors.emplace_back(GS_Error::Create(std::move(message)));
        }

    public:

        Vector<GS_Error> GetErrors() const {
            return _errors;
        }

    private:

        Vector<GS_Error> _errors;
    };

    using GSErrorHandlerPtr = SharedPtr<GS_ErrorHandler>;

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
     * rvalue_expr -> const_expr, unary_expr, binary_expr, func_call_expr
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
     * func_call_expr -> id '(' (expr...) ')'
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

        AST::GSExpressionPtr ParseFunctionCallingExpression();

    public:

        AST::GSValuePtr ParseValue();

        Semantic::GSTypePtr ParseType();

    public:

        template<typename T>
        inline T TryParse(T (GS_Parser:: *method) ()) {
            auto stream = _stream;
            auto context = _context;
            auto builder = _builder;
            auto errorHandler = _errorHandler;

            auto result = (this->*method)();

            if (!result) {
                _stream = stream;
                _context = context;
                _builder = builder;
                _errorHandler = errorHandler;

                return nullptr;
            }

            return result;
        }

    public:

        I32 TokenPrecedence();

        Bool IsTokenType(Lexer::TokenType type);

        Lexer::GS_TokenLocation TokenLocation();

        UString TokenValue();

        Lexer::TokenType TokenType();

        Lexer::GS_Token CurrentToken();

        Void NextToken();

        Void AddError(UString error);

    private:

        Lexer::GS_TokenStream _stream;

        AST::GSASTContextPtr _context;

        AST::GSASTBuilderPtr _builder;

        GSErrorHandlerPtr _errorHandler;
    };

}

#endif //GSLANGUAGE_GS_PARSER_H
