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
#include <AST/Expressions/GS_VariableUsingExpression.h>
#include <AST/Expressions/GS_FunctionCallingExpression.h>

#include <AST/GS_ASTContext.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for smart creating AST nodes
     */
    class GS_ASTBuilder {
    public:

        /**
         * Constructor for AST builder
         * @param context AST context
         */
        explicit GS_ASTBuilder(GSASTContextPtr context);

    public:

        /**
         * Creating AST builder
         * @param context AST context
         * @return AST builder ptr
         */
        static SharedPtr<GS_ASTBuilder> Create(GSASTContextPtr context);

        /**
         * Creating AST builder
         * @return AST builder ptr
         */
        static SharedPtr<GS_ASTBuilder> Create();

    public:

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
        SharedPtr<Semantic::GS_VoidType> CreateVoidType();

        /**
         * Create I32 type
         * @return I32 type
         */
        SharedPtr<Semantic::GS_I32Type> CreateI32Type();

        /**
         * Create String type
         * @return String type
         */
        SharedPtr<Semantic::GS_StringType> CreateStringType();

    public:

        /**
         * Create any value
         * @param type Type
         * @return Value
         */
        GSValuePtr CreateValue(Semantic::GSTypePtr type);

        /**
         * Create I32 value
         * @param number Number
         * @return I32 value
         */
        SharedPtr<GS_I32Value> CreateI32Value(I32 number);

        /**
         * Create String value
         * @param string String
         * @return String value
         */
        SharedPtr<GS_StringValue> CreateStringValue(UString string);

    public:

        /**
         * Create translation unit declaration
         * @param name Name
         * @param nodes Nodes
         * @return Translation unit declaration
         */
        GSTranslationUnitDeclarationPtr CreateTranslationUnitDeclaration(UString name, GSNodePtrArray nodes);

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
        GS_FunctionSignature CreateFunctionSignature(Semantic::GSTypePtrArray paramTypes, Semantic::GSTypePtr returnType);

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
        SharedPtr<GS_FunctionDeclaration> CreateFunctionDeclaration(UString name, GS_FunctionSignature signature, GSStatementPtrArray body);

        /**
         * Create function declaration
         * @param name Name
         * @param signature Signature
         * @return Function declaration
         */
        SharedPtr<GS_FunctionDeclaration> CreateFunctionDeclaration(UString name, GS_FunctionSignature signature);

        /**
         * Create function declaration
         * @param name Name
         * @param statements Statements
         * @return Function declaration
         */
        SharedPtr<GS_FunctionDeclaration> CreateFunctionDeclaration(UString name, GSStatementPtrArray statements);

        /**
         * Create function declaration
         * @param name Name
         * @return Function declaration
         */
        SharedPtr<GS_FunctionDeclaration> CreateFunctionDeclaration(UString name);

    public:

        /**
         * Create variable declaration statement
         * @param name Name
         * @param type Type
         * @param expression Expression
         * @return Variable declaration statement
         */
        SharedPtr<GS_VariableDeclarationStatement> CreateVariableDeclarationStatement(UString name, Semantic::GSTypePtr type, GSExpressionPtr expression);

        /**
         * Create variable declaration statement
         * @param name Name
         * @param type Type
         * @return Variable declaration statement
         */
        SharedPtr<GS_VariableDeclarationStatement> CreateVariableDeclarationStatement(UString name, Semantic::GSTypePtr type);

        /**
         * Create variable declaration statement
         * @param name Name
         * @param expression Expression
         * @return Variable declaration statement
         */
        SharedPtr<GS_VariableDeclarationStatement> CreateVariableDeclarationStatement(UString name, GSExpressionPtr expression);

        /**
         * Create assignment statement
         * @param lvalueExpression Left value expression
         * @param rvalueExpression Right value expression
         * @return Assignment statement
         */
        SharedPtr<GS_AssignmentStatement> CreateAssignmentStatement(GSExpressionPtr lvalueExpression, GSExpressionPtr rvalueExpression);

        /**
         * Create expression statement
         * @param expression Expression
         * @return Expression statement
         */
        SharedPtr<GS_ExpressionStatement> CreateExpressionStatement(GSExpressionPtr expression);

    public:

        /**
         * Create constant expression
         * @param value Value
         * @return Constant expression
         */
        SharedPtr<GS_ConstantExpression> CreateConstantExpression(GSValuePtr value);

        /**
         * Create constant expression
         * @param number Number
         * @return Constant expression
         */
        SharedPtr<GS_ConstantExpression> CreateConstantExpression(I32 number);

        /**
         * Create constant expression
         * @param string String
         * @return Constant expression
         */
        SharedPtr<GS_ConstantExpression> CreateConstantExpression(UString string);

        /**
         * Create unary expression
         * @param operation Operation
         * @param expression Expression
         * @return Unary expression
         */
        SharedPtr<GS_UnaryExpression> CreateUnaryExpression(UnaryOperation operation, GSExpressionPtr expression);

        /**
         * Create binary expression
         * @param operation Operation
         * @param firstExpression First expression
         * @param secondExpression Second expression
         * @return Binary expression
         */
        SharedPtr<GS_BinaryExpression> CreateBinaryExpression(BinaryOperation operation, GSExpressionPtr firstExpression, GSExpressionPtr secondExpression);

        /**
         * Create variable using expression
         * @param name Name
         * @return Variable using expression
         */
        SharedPtr<GS_VariableUsingExpression> CreateVariableUsingExpression(UString name);

        /**
         * Create function calling expression
         * @param name Name
         * @param params Params
         * @return Function calling expression
         */
        SharedPtr<GS_FunctionCallingExpression> CreateFunctionCallingExpression(UString name, GSExpressionPtrArray params);

    public:

        /**
         * Getter for AST context
         * @return AST context
         */
        GSASTContextPtr GetContext() const;

    private:

        /**
         * AST context
         */
        GSASTContextPtr _context;
    };

    /**
     * AST builder ptr type
     */
    using GSASTBuilderPtr = SharedPtr<GS_ASTBuilder>;

}

#endif //GSLANGUAGE_GS_ASTBUILDER_H
