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
        explicit GS_ASTBuilder(GSASTContextPtr context)
                : _context(std::move(context)) {}

    public:

        /**
         * Creating AST builder
         * @param context AST context
         * @return AST builder ptr
         */
        static SharedPtr<GS_ASTBuilder> Create(GSASTContextPtr context) {
            return std::make_shared<GS_ASTBuilder>(std::move(context));
        }

        /**
         * Creating AST builder
         * @return AST builder ptr
         */
        static SharedPtr<GS_ASTBuilder> Create() {
            return GS_ASTBuilder::Create(GS_ASTContext::Create());
        }

    public:

        /**
         * Create any type
         * @param name Name
         * @return Type
         */
        auto CreateType(UString name) {
            return AST::GS_Type::Create(std::move(name));
        }

        /**
         * Create Void type
         * @return Void type
         */
        auto CreateVoidType() {
            return _context->GetVoidType();
        }

        /**
         * Create I32 type
         * @return I32 type
         */
        auto CreateI32Type() {
            return _context->GetI32Type();
        }

        /**
         * Create String type
         * @return String type
         */
        auto CreateStringType() {
            return _context->GetStringType();
        }

    public:

        /**
         * Create any value
         * @param type Type
         * @return Value
         */
        auto CreateValue(AST::GSTypePtr type) {
            return AST::GS_Value::Create(std::move(type));
        }

        /**
         * Create I32 value
         * @param number Number
         * @return I32 value
         */
        auto CreateI32Value(I32 number) {
            return AST::GS_I32Value::Create(number);
        }

        /**
         * Create String value
         * @param string String
         * @return String value
         */
        auto CreateStringValue(UString string) {
            return AST::GS_StringValue::Create(std::move(string));
        }

    public:

        /**
         * Create translation unit declaration
         * @param name Name
         * @param nodes Nodes
         * @return Translation unit declaration
         */
        auto CreateTranslationUnitDeclaration(UString name, AST::GSNodePtrArray nodes) {
            return AST::GS_TranslationUnitDeclaration::Create(std::move(name), std::move(nodes));
        }

        /**
         * Create translation unit declaration
         * @param name Name
         * @return Translation unit declaration
         */
        auto CreateTranslationUnitDeclaration(UString name) {
            return AST::GS_TranslationUnitDeclaration::Create(std::move(name));
        }

        /**
         * Create function declaration
         * @param name Name
         * @param statements Statements
         * @return Function declaration
         */
        auto CreateFunctionDeclaration(UString name, AST::GSStatementPtrArray statements) {
            return AST::GS_FunctionDeclaration::Create(std::move(name), std::move(statements));
        }

        /**
         * Create function declaration
         * @param name Name
         * @return Function declaration
         */
        auto CreateFunctionDeclaration(UString name) {
            return AST::GS_FunctionDeclaration::Create(std::move(name));
        }

    public:

        /**
         * Create variable declaration statement
         * @param name Name
         * @param type Type
         * @param expression Expression
         * @return Variable declaration statement
         */
        auto CreateVariableDeclarationStatement(UString name, AST::GSTypePtr type, AST::GSExpressionPtr expression) {
            return AST::GS_VariableDeclarationStatement::Create(std::move(name), std::move(type), std::move(expression));
        }

        /**
         * Create variable declaration statement
         * @param name Name
         * @param type Type
         * @return Variable declaration statement
         */
        auto CreateVariableDeclarationStatement(UString name, AST::GSTypePtr type) {
            return AST::GS_VariableDeclarationStatement::Create(std::move(name), std::move(type));
        }

        /**
         * Create variable declaration statement
         * @param name Name
         * @param expression Expression
         * @return Variable declaration statement
         */
        auto CreateVariableDeclarationStatement(UString name, AST::GSExpressionPtr expression) {
            return AST::GS_VariableDeclarationStatement::Create(std::move(name), std::move(expression));
        }

        /**
         * Create assignment statement
         * @param lvalueExpression Left value expression
         * @param rvalueExpression Right value expression
         * @return Assignment statement
         */
        auto CreateAssignmentStatement(AST::GSExpressionPtr lvalueExpression, AST::GSExpressionPtr rvalueExpression) {
            return AST::GS_AssignmentStatement::Create(std::move(lvalueExpression), std::move(rvalueExpression));
        }

        /**
         * Create expression statement
         * @param expression Expression
         * @return Expression statement
         */
        auto CreateExpressionStatement(AST::GSExpressionPtr expression) {
            return AST::GS_ExpressionStatement::Create(std::move(expression));
        }

    public:

        /**
         * Create constant expression
         * @param value Value
         * @return Constant expression
         */
        auto CreateConstantExpression(AST::GSValuePtr value) {
            return AST::GS_ConstantExpression::Create(std::move(value));
        }

        /**
         * Create constant expression
         * @param number Number
         * @return Constant expression
         */
        auto CreateConstantExpression(I32 number) {
            return CreateConstantExpression(CreateI32Value(number));
        }

        /**
         * Create constant expression
         * @param string String
         * @return Constant expression
         */
        auto CreateConstantExpression(UString string) {
            return CreateConstantExpression(CreateStringValue(std::move(string)));
        }

        /**
         * Create unary expression
         * @param operation Operation
         * @param expression Expression
         * @return Unary expression
         */
        auto CreateUnaryExpression(AST::UnaryOperation operation, AST::GSExpressionPtr expression) {
            return AST::GS_UnaryExpression::Create(operation, std::move(expression));
        }

        /**
         * Create binary expression
         * @param operation Operation
         * @param firstExpression First expression
         * @param secondExpression Second expression
         * @return Binary expression
         */
        auto CreateBinaryExpression(AST::BinaryOperation operation, AST::GSExpressionPtr firstExpression, AST::GSExpressionPtr secondExpression) {
            return AST::GS_BinaryExpression::Create(operation, std::move(firstExpression), std::move(secondExpression));
        }

        /**
         * Create variable using expression
         * @param name Name
         * @return Variable using expression
         */
        auto CreateVariableUsingExpression(UString name) {
            return AST::GS_VariableUsingExpression::Create(std::move(name));
        }

    public:

        /**
         * Getter for AST context
         * @return AST context
         */
        GSASTContextPtr GetContext() {
            return _context;
        }

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
