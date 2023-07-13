#ifndef GSLANGUAGE_GS_ASTBUILDER_H
#define GSLANGUAGE_GS_ASTBUILDER_H

#include <AST/Declarations/GS_TranslationUnitDeclaration.h>
#include <AST/Declarations/GS_FunctionDeclaration.h>

#include <AST/Statements/GS_VariableDeclarationStatement.h>
#include <AST/Statements/GS_AssignmentStatement.h>
#include <AST/Statements/GS_IfStatement.h>
#include <AST/Statements/GS_ForStatement.h>
#include <AST/Statements/GS_WhileStatement.h>
#include <AST/Statements/GS_ExpressionStatement.h>

#include <AST/Expressions/GS_LiteralExpression.h>
#include <AST/Expressions/GS_UnaryExpression.h>
#include <AST/Expressions/GS_BinaryExpression.h>
#include <AST/Expressions/GS_ArrayExpression.h>
#include <AST/Expressions/GS_VariableUsingExpression.h>
#include <AST/Expressions/GS_FunctionCallingExpression.h>

#include <AST/GS_ASTContext.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for smart creating AST nodes
     */
    class GS_ASTBuilder {
    public:

        /*
         *
         * GS_ASTBuilder PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for AST builder
         * @param context AST context
         */
        explicit GS_ASTBuilder(LRef<GS_ASTContext> context);

    public:

        /*
         *
         * GS_ASTBuilder PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating AST builder
         * @param context AST context
         * @return AST builder ptr
         */
        static std::unique_ptr<GS_ASTBuilder> Create(LRef<GS_ASTContext> context);

    public:

        /*
         *
         * GS_ASTBuilder PUBLIC METHODS
         *
         */

        /**
         * Create any type
         * @param name Name
         * @return Type
         */
        Semantic::GSTypePtr CreateType(UString name);

        /**
         * Create Void type
         * @return Void type
         */
        Semantic::TypePtr<Semantic::GS_VoidType> CreateVoidType();

        /**
         * Create Bool type
         * @return Bool type
         */
        Semantic::TypePtr<Semantic::GS_BoolType> CreateBoolType();

        /**
         * Create Char type
         * @return Char type
         */
        Semantic::TypePtr<Semantic::GS_CharType> CreateCharType();

        /**
         * Create I8 type
         * @return I8 type
         */
        Semantic::TypePtr<Semantic::GS_I8Type> CreateI8Type();

        /**
         * Create I16 type
         * @return I16 type
         */
        Semantic::TypePtr<Semantic::GS_I16Type> CreateI16Type();

        /**
         * Create I32 type
         * @return I32 type
         */
        Semantic::TypePtr<Semantic::GS_I32Type> CreateI32Type();

        /**
         * Create I64 type
         * @return I64 type
         */
        Semantic::TypePtr<Semantic::GS_I64Type> CreateI64Type();

        /**
         * Create U8 type
         * @return U8 type
         */
        Semantic::TypePtr<Semantic::GS_U8Type> CreateU8Type();

        /**
         * Create U16 type
         * @return U16 type
         */
        Semantic::TypePtr<Semantic::GS_U16Type> CreateU16Type();

        /**
         * Create U32 type
         * @return U32 type
         */
        Semantic::TypePtr<Semantic::GS_U32Type> CreateU32Type();

        /**
         * Create U64 type
         * @return U64 type
         */
        Semantic::TypePtr<Semantic::GS_U64Type> CreateU64Type();

        /**
         * Create String type
         * @return String type
         */
        Semantic::TypePtr<Semantic::GS_StringType> CreateStringType();

        /**
         * Create Array type
         * @param elementsType Type of array elements
         * @param size Size of array
         * @return Array type
         */
        Semantic::TypePtr<Semantic::GS_ArrayType> CreateArrayType(Semantic::GSTypePtr elementsType,
                                                                  U64 size);

        /**
         * Create any value
         * @param type Type
         * @return Value
         */
        GSValuePtr CreateValue(Semantic::GSTypePtr type);

        /**
         * Create Bool value
         * @param value Bool value
         * @return Bool value
         */
        ValuePtr<GS_BoolValue> CreateBoolValue(Bool value);

        /**
         * Create Char value
         * @param value Char value
         * @return Char value
         */
        ValuePtr<GS_CharValue> CreateCharValue(USymbol value);

        /**
         * Create I8 value
         * @param value I8 value
         * @return I8 value
         */
        ValuePtr<GS_I8Value> CreateI8Value(I8 value);

        /**
         * Create I16 value
         * @param value I16 value
         * @return I16 value
         */
        ValuePtr<GS_I16Value> CreateI16Value(I16 value);

        /**
         * Create I32 value
         * @param value I32 value
         * @return I32 value
         */
        ValuePtr<GS_I32Value> CreateI32Value(I32 value);

        /**
         * Create I64 value
         * @param value I64 value
         * @return I64 value
         */
        ValuePtr<GS_I64Value> CreateI64Value(I64 value);

        /**
         * Create U8 value
         * @param value U8 value
         * @return U8 value
         */
        ValuePtr<GS_U8Value> CreateU8Value(U8 value);

        /**
         * Create U16 value
         * @param value U16 value
         * @return U16 value
         */
        ValuePtr<GS_U16Value> CreateU16Value(U16 value);

        /**
         * Create U32 value
         * @param value U32 value
         * @return U32 value
         */
        ValuePtr<GS_U32Value> CreateU32Value(U32 value);

        /**
         * Create U64 value
         * @param value U64 value
         * @return U64 value
         */
        ValuePtr<GS_U64Value> CreateU64Value(U64 value);

        /**
         * Create String value
         * @param value String value
         * @return String value
         */
        ValuePtr<GS_StringValue> CreateStringValue(UString value);

        /**
         * Create translation unit declaration
         * @param name Name
         * @param nodes Nodes
         * @return Translation unit declaration
         */
        GSTranslationUnitDeclarationPtr CreateTranslationUnitDeclaration(UString name,
                                                                         GSNodePtrArray nodes);

        /**
         * Create translation unit declaration
         * @param name Name
         * @return Translation unit declaration
         */
        GSTranslationUnitDeclarationPtr CreateTranslationUnitDeclaration(UString name);

        /**
         * Create function qualifiers
         * @param externType Extern type
         * @return Function qualifiers
         */
        GS_FunctionQualifiers CreateFunctionQualifiers(ExternType externType);

        /**
         * Create function qualifiers
         * @return Function qualifiers
         */
        GS_FunctionQualifiers CreateFunctionQualifiers();

        /**
         * Create function param
         * @param name Name
         * @param type Type
         * @return Function param
         */
        GS_FunctionParam CreateFunctionParam(UString name,
                                             Semantic::GSTypePtr type);

        /**
         * Create function signature
         * @param params Params
         * @param returnType Return type
         * @param qualifiers Qualifiers
         * @return Function signature
         */
        GS_FunctionSignature CreateFunctionSignature(GSFunctionParamArray params,
                                                     Semantic::GSTypePtr returnType,
                                                     GS_FunctionQualifiers qualifiers);

        /**
         * Create function signature
         * @param params Params
         * @param returnType Return type
         * @return Function signature
         */
        GS_FunctionSignature CreateFunctionSignature(GSFunctionParamArray params,
                                                     Semantic::GSTypePtr returnType);

        /**
         * Create function signature
         * @param params Params
         * @return Function signature
         */
        GS_FunctionSignature CreateFunctionSignature(GSFunctionParamArray params);

        /**
         * Create function signature
         * @param returnType Return type
         * @return Function signature
         */
        GS_FunctionSignature CreateFunctionSignature(Semantic::GSTypePtr returnType);

        /**
         * Create function signature
         * @return Function signature
         */
        GS_FunctionSignature CreateFunctionSignature();

        /**
         * Create function declaration
         * @param name Name
         * @param signature Signature
         * @param body Body
         * @return Function declaration
         */
        NodePtr<GS_FunctionDeclaration> CreateFunctionDeclaration(UString name,
                                                                  GS_FunctionSignature signature,
                                                                  GSStatementPtrArray body);

        /**
         * Create function declaration
         * @param name Name
         * @param signature Signature
         * @return Function declaration
         */
        NodePtr<GS_FunctionDeclaration> CreateFunctionDeclaration(UString name,
                                                                  GS_FunctionSignature signature);

        /**
         * Create function declaration
         * @param name Name
         * @param statements Statements
         * @return Function declaration
         */
        NodePtr<GS_FunctionDeclaration> CreateFunctionDeclaration(UString name,
                                                                  GSStatementPtrArray statements);

        /**
         * Create function declaration
         * @param name Name
         * @return Function declaration
         */
        NodePtr<GS_FunctionDeclaration> CreateFunctionDeclaration(UString name);

        /**
         * Create variable declaration statement
         * @param name Name
         * @param type Type
         * @param expression Expression
         * @return Variable declaration statement
         */
        NodePtr<GS_VariableDeclarationStatement> CreateVariableDeclarationStatement(UString name,
                                                                                    Semantic::GSTypePtr type,
                                                                                    GSExpressionPtr expression);

        /**
         * Create variable declaration statement
         * @param name Name
         * @param type Type
         * @return Variable declaration statement
         */
        NodePtr<GS_VariableDeclarationStatement> CreateVariableDeclarationStatement(UString name,
                                                                                    Semantic::GSTypePtr type);

        /**
         * Create variable declaration statement
         * @param name Name
         * @param expression Expression
         * @return Variable declaration statement
         */
        NodePtr<GS_VariableDeclarationStatement> CreateVariableDeclarationStatement(UString name,
                                                                                    GSExpressionPtr expression);

        /**
         * Create assignment statement
         * @param lvalueExpression Left value expression
         * @param rvalueExpression Right value expression
         * @return Assignment statement
         */
        NodePtr<GS_AssignmentStatement> CreateAssignmentStatement(GSExpressionPtr lvalueExpression,
                                                                  GSExpressionPtr rvalueExpression);

        /**
         * Create if statement
         * @param condition Condition
         * @param ifBody If body
         * @param elseBody Else body
         * @return If statement
         */
        NodePtr<GS_IfStatement> CreateIfStatement(GSExpressionPtr condition,
                                                  GSStatementPtrArray ifBody,
                                                  GSStatementPtrArray elseBody);

        /**
         * Create if statement
         * @param condition Condition
         * @param ifBody If body
         * @return If statement
         */
        NodePtr<GS_IfStatement> CreateIfStatement(GSExpressionPtr condition,
                                                  GSStatementPtrArray ifBody);

        /**
         * Create if statement
         * @param condition Condition
         * @return If statement
         */
        NodePtr<GS_IfStatement> CreateIfStatement(GSExpressionPtr condition);

        /**
         * Create for statement
         * @param name Name
         * @param expression Expression
         * @param body Body
         * @return For statement
         */
        NodePtr<GS_ForStatement> CreateForStatement(UString name,
                                                    GSExpressionPtr expression,
                                                    GSStatementPtrArray body);

        /**
         * Create for statement
         * @param name Name
         * @param expression Expression
         * @return For statement
         */
        NodePtr<GS_ForStatement> CreateForStatement(UString name,
                                                    GSExpressionPtr expression);

        /**
         * Create while statement
         * @param condition Condition
         * @param body Body
         * @return While statement
         */
        NodePtr<GS_WhileStatement> CreateWhileStatement(GSExpressionPtr condition,
                                                        GSStatementPtrArray body);

        /**
         * Create while statement
         * @param condition Condition
         * @return While statement
         */
        NodePtr<GS_WhileStatement> CreateWhileStatement(GSExpressionPtr condition);

        /**
         * Create expression statement
         * @param expression Expression
         * @return Expression statement
         */
        NodePtr<GS_ExpressionStatement> CreateExpressionStatement(GSExpressionPtr expression);

        /**
         * Create constant expression
         * @param value Value
         * @return Constant expression
         */
        NodePtr<GS_LiteralExpression> CreateConstantExpression(GSValuePtr value);

        /**
         * Create constant expression
         * @param value Bool value
         * @return Constant expression
         */
        NodePtr<GS_LiteralExpression> CreateConstantExpression(Bool value);

        /**
         * Create constant expression
         * @param value Char value
         * @return Constant expression
         */
        NodePtr<GS_LiteralExpression> CreateConstantExpression(USymbol value);

        /**
         * Create constant expression
         * @param value I8 value
         * @return Constant expression
         */
        NodePtr<GS_LiteralExpression> CreateConstantExpression(I8 value);

        /**
         * Create constant expression
         * @param value I16 value
         * @return Constant expression
         */
        NodePtr<GS_LiteralExpression> CreateConstantExpression(I16 value);

        /**
         * Create constant expression
         * @param value I32 value
         * @return Constant expression
         */
        NodePtr<GS_LiteralExpression> CreateConstantExpression(I32 value);

        /**
         * Create constant expression
         * @param value I64 value
         * @return Constant expression
         */
        NodePtr<GS_LiteralExpression> CreateConstantExpression(I64 value);

        /**
         * Create constant expression
         * @param value U8 value
         * @return Constant expression
         */
        NodePtr<GS_LiteralExpression> CreateConstantExpression(U8 value);

        /**
         * Create constant expression
         * @param value U16 value
         * @return Constant expression
         */
        NodePtr<GS_LiteralExpression> CreateConstantExpression(U16 value);

        /**
         * Create constant expression
         * @param value U32 value
         * @return Constant expression
         */
        NodePtr<GS_LiteralExpression> CreateConstantExpression(U32 value);

        /**
         * Create constant expression
         * @param value U64 value
         * @return Constant expression
         */
        NodePtr<GS_LiteralExpression> CreateConstantExpression(U64 value);

        /**
         * Create constant expression
         * @param value String value
         * @return Constant expression
         */
        NodePtr<GS_LiteralExpression> CreateConstantExpression(UString value);

        /**
         * Create unary expression
         * @param operation Operation
         * @param expression Expression
         * @return Unary expression
         */
        NodePtr<GS_UnaryExpression> CreateUnaryExpression(UnaryOperation operation,
                                                          GSExpressionPtr expression);

        /**
         * Create binary expression
         * @param operation Operation
         * @param firstExpression First expression
         * @param secondExpression Second expression
         * @return Binary expression
         */
        NodePtr<GS_BinaryExpression> CreateBinaryExpression(BinaryOperation operation,
                                                            GSExpressionPtr firstExpression,
                                                            GSExpressionPtr secondExpression);

        /**
         * Create array expression
         * @param expressions Expressions
         * @return Array expression
         */
        NodePtr<GS_ArrayExpression> CreateArrayExpression(GSExpressionPtrArray expressions);

        /**
         * Create variable using expression
         * @param name Name
         * @param nameLocation Name source location range
         * @return Variable using expression
         */
        NodePtr<GS_VariableUsingExpression> CreateVariableUsingExpression(UString name,
                                                                          IO::GS_SourceRange nameLocationRange);

        /**
         * Create variable using expression
         * @param name Name
         * @return Variable using expression
         */
        NodePtr<GS_VariableUsingExpression> CreateVariableUsingExpression(UString name);

        /**
         * Create function calling expression
         * @param name Name
         * @param params Params
         * @return Function calling expression
         */
        NodePtr<GS_FunctionCallingExpression> CreateFunctionCallingExpression(UString name,
                                                                              GSExpressionPtrArray params);

    public:

        /*
         *
         * GS_ASTBuilder PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for AST context
         * @return AST context
         */
        LRef<GS_ASTContext> GetContext();

    private:

        /*
         *
         * GS_ASTBuilder PRIVATE FIELDS
         *
         */

        /**
         * AST context
         */
        LRef<GS_ASTContext> _context;
    };

    /**
     * AST builder ptr type
     */
    using GSASTBuilderPtr = std::unique_ptr<GS_ASTBuilder>;

}

#endif //GSLANGUAGE_GS_ASTBUILDER_H
