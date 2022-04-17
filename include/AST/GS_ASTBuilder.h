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

    // TODO comment all
    class GS_ASTBuilder {
    public:

        explicit GS_ASTBuilder(GSASTContextPtr context)
                : _context(std::move(context)) {}

    public:

        static SharedPtr<GS_ASTBuilder> Create(GSASTContextPtr context) {
            return std::make_shared<GS_ASTBuilder>(std::move(context));
        }

        static SharedPtr<GS_ASTBuilder> Create() {
            return GS_ASTBuilder::Create(GS_ASTContext::Create());
        }

    public:

        auto CreateType(UString name) {
            return AST::GS_Type::Create(std::move(name));
        }

        auto CreateVoidType() {
            return _context->GetVoidType();
        }

        auto CreateI32Type() {
            return _context->GetI32Type();
        }

        auto CreateStringType() {
            return _context->GetStringType();
        }

    public:

        auto CreateValue(AST::GSTypePtr type) {
            return AST::GS_Value::Create(std::move(type));
        }

        auto CreateI32Value(I32 number) {
            return AST::GS_I32Value::Create(number);
        }

        auto CreateStringValue(UString string) {
            return AST::GS_StringValue::Create(std::move(string));
        }

    public:

        auto CreateTranslationUnitDeclaration(UString name, AST::GSNodePtrArray nodes) {
            return AST::GS_TranslationUnitDeclaration::Create(std::move(name), std::move(nodes));
        }

        auto CreateTranslationUnitDeclaration(UString name) {
            return AST::GS_TranslationUnitDeclaration::Create(std::move(name));
        }

        auto CreateFunctionDeclaration(UString name, AST::GSStatementPtrArray statements) {
            return AST::GS_FunctionDeclaration::Create(std::move(name), std::move(statements));
        }

        auto CreateFunctionDeclaration(UString name) {
            return AST::GS_FunctionDeclaration::Create(std::move(name));
        }

    public:

        auto CreateVariableDeclarationStatement(UString name, AST::GSTypePtr type, AST::GSExpressionPtr expression) {
            return AST::GS_VariableDeclarationStatement::Create(std::move(name), std::move(type), std::move(expression));
        }

        auto CreateVariableDeclarationStatement(UString name, AST::GSTypePtr type) {
            return AST::GS_VariableDeclarationStatement::Create(std::move(name), std::move(type));
        }

        auto CreateVariableDeclarationStatement(UString name, AST::GSExpressionPtr expression) {
            return AST::GS_VariableDeclarationStatement::Create(std::move(name), std::move(expression));
        }

        auto CreateAssignmentStatement(AST::GSExpressionPtr lvalueExpression, AST::GSExpressionPtr rvalueExpression) {
            return AST::GS_AssignmentStatement::Create(std::move(lvalueExpression), std::move(rvalueExpression));
        }

        auto CreateExpressionStatement(AST::GSExpressionPtr expression) {
            return AST::GS_ExpressionStatement::Create(std::move(expression));
        }

    public:

        auto CreateConstantExpression(AST::GSValuePtr value) {
            return AST::GS_ConstantExpression::Create(std::move(value));
        }

        auto CreateConstantExpression(I32 number) {
            return CreateConstantExpression(CreateI32Value(number));
        }

        auto CreateConstantExpression(UString string) {
            return CreateConstantExpression(CreateStringValue(std::move(string)));
        }

        auto CreateUnaryExpression(AST::UnaryOperation operation, AST::GSExpressionPtr expression) {
            return AST::GS_UnaryExpression::Create(operation, std::move(expression));
        }

        auto CreateBinaryExpression(AST::BinaryOperation operation, AST::GSExpressionPtr firstExpression, AST::GSExpressionPtr secondExpression) {
            return AST::GS_BinaryExpression::Create(operation, std::move(firstExpression), std::move(secondExpression));
        }

        auto CreateVariableUsingExpression(UString name) {
            return AST::GS_VariableUsingExpression::Create(std::move(name));
        }

    public:

        GSASTContextPtr GetContext() {
            return _context;
        }

    private:

        GSASTContextPtr _context;
    };

    using GSASTBuilderPtr = SharedPtr<GS_ASTBuilder>;

}

#endif //GSLANGUAGE_GS_ASTBUILDER_H
