#include <GS_ASTBuilder.h>

namespace GSLanguageCompiler::AST {

    GS_ASTBuilder::GS_ASTBuilder(GSASTContextPtr context)
            : _context(std::move(context)) {}

    SharedPtr<GS_ASTBuilder> GS_ASTBuilder::Create(GSASTContextPtr context) {
        return std::make_shared<GS_ASTBuilder>(std::move(context));
    }

    SharedPtr<GS_ASTBuilder> GS_ASTBuilder::Create() {
        return GS_ASTBuilder::Create(GS_ASTContext::Create());
    }

    GSTypePtr GS_ASTBuilder::CreateType(UString name) {
        return GS_Type::Create(std::move(name));
    }

    SharedPtr<GS_VoidType> GS_ASTBuilder::CreateVoidType() {
        return _context->GetVoidType();
    }

    SharedPtr<GS_I32Type> GS_ASTBuilder::CreateI32Type() {
        return _context->GetI32Type();
    }

    SharedPtr<GS_StringType> GS_ASTBuilder::CreateStringType() {
        return _context->GetStringType();
    }

    GSValuePtr GS_ASTBuilder::CreateValue(GSTypePtr type) {
        return GS_Value::Create(std::move(type));
    }

    SharedPtr<GS_I32Value> GS_ASTBuilder::CreateI32Value(I32 number) {
        return GS_I32Value::Create(number);
    }

    SharedPtr<GS_StringValue> GS_ASTBuilder::CreateStringValue(UString string) {
        return GS_StringValue::Create(std::move(string));
    }

    GSTranslationUnitDeclarationPtr GS_ASTBuilder::CreateTranslationUnitDeclaration(UString name, GSNodePtrArray nodes) {
        return GS_TranslationUnitDeclaration::Create(std::move(name), std::move(nodes));
    }

    SharedPtr<GS_TranslationUnitDeclaration> GS_ASTBuilder::CreateTranslationUnitDeclaration(UString name) {
        return GS_TranslationUnitDeclaration::Create(std::move(name));
    }

    SharedPtr<GS_FunctionDeclaration> GS_ASTBuilder::CreateFunctionDeclaration(UString name, GSStatementPtrArray statements) {
        return GS_FunctionDeclaration::Create(std::move(name), std::move(statements));
    }

    SharedPtr<GS_FunctionDeclaration> GS_ASTBuilder::CreateFunctionDeclaration(UString name) {
        return GS_FunctionDeclaration::Create(std::move(name));
    }

    SharedPtr<GS_VariableDeclarationStatement> GS_ASTBuilder::CreateVariableDeclarationStatement(UString name, GSTypePtr type, GSExpressionPtr expression) {
        return GS_VariableDeclarationStatement::Create(std::move(name), std::move(type), std::move(expression));
    }

    SharedPtr<GS_VariableDeclarationStatement> GS_ASTBuilder::CreateVariableDeclarationStatement(UString name, GSTypePtr type) {
        return GS_VariableDeclarationStatement::Create(std::move(name), std::move(type));
    }

    SharedPtr<GS_VariableDeclarationStatement> GS_ASTBuilder::CreateVariableDeclarationStatement(UString name, GSExpressionPtr expression) {
        return GS_VariableDeclarationStatement::Create(std::move(name), std::move(expression));
    }

    SharedPtr<GS_AssignmentStatement> GS_ASTBuilder::CreateAssignmentStatement(GSExpressionPtr lvalueExpression, GSExpressionPtr rvalueExpression) {
        return GS_AssignmentStatement::Create(std::move(lvalueExpression), std::move(rvalueExpression));
    }

    SharedPtr<GS_ExpressionStatement> GS_ASTBuilder::CreateExpressionStatement(GSExpressionPtr expression) {
        return GS_ExpressionStatement::Create(std::move(expression));
    }

    SharedPtr<GS_ConstantExpression> GS_ASTBuilder::CreateConstantExpression(GSValuePtr value) {
        return GS_ConstantExpression::Create(std::move(value));
    }

    SharedPtr<GS_ConstantExpression> GS_ASTBuilder::CreateConstantExpression(I32 number) {
        return CreateConstantExpression(CreateI32Value(number));
    }

    SharedPtr<GS_ConstantExpression> GS_ASTBuilder::CreateConstantExpression(UString string) {
        return CreateConstantExpression(CreateStringValue(std::move(string)));
    }

    SharedPtr<GS_UnaryExpression> GS_ASTBuilder::CreateUnaryExpression(UnaryOperation operation, GSExpressionPtr expression) {
        return GS_UnaryExpression::Create(operation, std::move(expression));
    }

    SharedPtr<GS_BinaryExpression> GS_ASTBuilder::CreateBinaryExpression(BinaryOperation operation, GSExpressionPtr firstExpression, GSExpressionPtr secondExpression) {
        return GS_BinaryExpression::Create(operation, std::move(firstExpression), std::move(secondExpression));
    }

    SharedPtr<GS_VariableUsingExpression> GS_ASTBuilder::CreateVariableUsingExpression(UString name) {
        return GS_VariableUsingExpression::Create(std::move(name));
    }

    SharedPtr<GS_FunctionCallingExpression> GS_ASTBuilder::CreateFunctionCallingExpression(UString name, GSExpressionPtrArray params) {
        return GS_FunctionCallingExpression::Create(std::move(name), std::move(params));
    }

    GSASTContextPtr GS_ASTBuilder::GetContext() const {
        return _context;
    }

}
