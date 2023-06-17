#ifndef GSLANGUAGE_GS_ASTBUILDER_H
#define GSLANGUAGE_GS_ASTBUILDER_H

#include <AST/Declarations/GS_TranslationUnitDeclaration.h>
#include <AST/Declarations/GS_FunctionDeclaration.h>

#include <AST/Statements/GS_VariableDeclarationStatement.h>
#include <AST/Statements/GS_AssignmentStatement.h>
#include <AST/Statements/GS_ExpressionStatement.h>

#include <AST/Expressions/GS_ConstantExpression.h>
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
         * Create Char value
         * @param symbol Symbol
         * @return Char value
         */
        ValuePtr<GS_CharValue> CreateCharValue(USymbol symbol);

        /**
         * Create I8 value
         * @param number Number
         * @return I8 value
         */
        ValuePtr<GS_I8Value> CreateI8Value(I8 number);

        /**
         * Create I16 value
         * @param number Number
         * @return I16 value
         */
        ValuePtr<GS_I16Value> CreateI16Value(I16 number);

        /**
         * Create I32 value
         * @param number Number
         * @return I32 value
         */
        ValuePtr<GS_I32Value> CreateI32Value(I32 number);

        /**
         * Create I64 value
         * @param number Number
         * @return I64 value
         */
        ValuePtr<GS_I64Value> CreateI64Value(I64 number);

        /**
         * Create U8 value
         * @param number Number
         * @return U8 value
         */
        ValuePtr<GS_U8Value> CreateU8Value(U8 number);

        /**
         * Create U16 value
         * @param number Number
         * @return U16 value
         */
        ValuePtr<GS_U16Value> CreateU16Value(U16 number);

        /**
         * Create U32 value
         * @param number Number
         * @return U32 value
         */
        ValuePtr<GS_U32Value> CreateU32Value(U32 number);

        /**
         * Create U64 value
         * @param number Number
         * @return U64 value
         */
        ValuePtr<GS_U64Value> CreateU64Value(U64 number);

        /**
         * Create String value
         * @param string String
         * @return String value
         */
        ValuePtr<GS_StringValue> CreateStringValue(UString string);

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
         * Create function signature
         * @param paramTypes Param types
         * @param returnType Return type
         * @return Function signature
         */
        GS_FunctionSignature CreateFunctionSignature(Semantic::GSTypePtrArray paramTypes,
                                                     Semantic::GSTypePtr returnType);

        /**
         * Create function signature
         * @param paramTypes Param types
         * @return Function signature
         */
        GS_FunctionSignature CreateFunctionSignature(Semantic::GSTypePtrArray paramTypes);

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
        NodePtr<GS_ConstantExpression> CreateConstantExpression(GSValuePtr value);

        /**
         * Create constant expression
         * @param symbol Symbol
         * @return Constant expression
         */
        NodePtr<GS_ConstantExpression> CreateConstantExpression(USymbol symbol);

        /**
         * Create constant expression
         * @param number Number
         * @return Constant expression
         */
        NodePtr<GS_ConstantExpression> CreateConstantExpression(I8 number);

        /**
         * Create constant expression
         * @param number Number
         * @return Constant expression
         */
        NodePtr<GS_ConstantExpression> CreateConstantExpression(I16 number);

        /**
         * Create constant expression
         * @param number Number
         * @return Constant expression
         */
        NodePtr<GS_ConstantExpression> CreateConstantExpression(I32 number);

        /**
         * Create constant expression
         * @param number Number
         * @return Constant expression
         */
        NodePtr<GS_ConstantExpression> CreateConstantExpression(I64 number);

        /**
         * Create constant expression
         * @param number Number
         * @return Constant expression
         */
        NodePtr<GS_ConstantExpression> CreateConstantExpression(U8 number);

        /**
         * Create constant expression
         * @param number Number
         * @return Constant expression
         */
        NodePtr<GS_ConstantExpression> CreateConstantExpression(U16 number);

        /**
         * Create constant expression
         * @param number Number
         * @return Constant expression
         */
        NodePtr<GS_ConstantExpression> CreateConstantExpression(U32 number);

        /**
         * Create constant expression
         * @param number Number
         * @return Constant expression
         */
        NodePtr<GS_ConstantExpression> CreateConstantExpression(U64 number);

        /**
         * Create constant expression
         * @param string String
         * @return Constant expression
         */
        NodePtr<GS_ConstantExpression> CreateConstantExpression(UString string);

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
