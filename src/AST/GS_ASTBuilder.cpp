#include <GS_ASTBuilder.h>

namespace GSLanguageCompiler::AST {

    GS_ASTBuilder::GS_ASTBuilder(LRef<GS_ASTContext> context)
            : _context(context) {}

    std::unique_ptr<GS_ASTBuilder> GS_ASTBuilder::Create(LRef<GS_ASTContext> context) {
        return std::make_unique<GS_ASTBuilder>(context);
    }

    Semantic::GSTypePtr GS_ASTBuilder::CreateType(UString name) {
        return Semantic::GS_Type::Create(std::move(name));
    }

    Semantic::TypePtr<Semantic::GS_VoidType> GS_ASTBuilder::CreateVoidType() {
        return _context.GetVoidType();
    }

    Semantic::TypePtr<Semantic::GS_BoolType> GS_ASTBuilder::CreateBoolType() {
        return _context.GetBoolType();
    }

    Semantic::TypePtr<Semantic::GS_CharType> GS_ASTBuilder::CreateCharType() {
        return _context.GetCharType();
    }

    Semantic::TypePtr<Semantic::GS_I8Type> GS_ASTBuilder::CreateI8Type() {
        return _context.GetI8Type();
    }

    Semantic::TypePtr<Semantic::GS_I16Type> GS_ASTBuilder::CreateI16Type() {
        return _context.GetI16Type();
    }

    Semantic::TypePtr<Semantic::GS_I32Type> GS_ASTBuilder::CreateI32Type() {
        return _context.GetI32Type();
    }

    Semantic::TypePtr<Semantic::GS_I64Type> GS_ASTBuilder::CreateI64Type() {
        return _context.GetI64Type();
    }

    Semantic::TypePtr<Semantic::GS_U8Type> GS_ASTBuilder::CreateU8Type() {
        return _context.GetU8Type();
    }

    Semantic::TypePtr<Semantic::GS_U16Type> GS_ASTBuilder::CreateU16Type() {
        return _context.GetU16Type();
    }

    Semantic::TypePtr<Semantic::GS_U32Type> GS_ASTBuilder::CreateU32Type() {
        return _context.GetU32Type();
    }

    Semantic::TypePtr<Semantic::GS_U64Type> GS_ASTBuilder::CreateU64Type() {
        return _context.GetU64Type();
    }

    Semantic::TypePtr<Semantic::GS_StringType> GS_ASTBuilder::CreateStringType() {
        return _context.GetStringType();
    }

    Semantic::TypePtr<Semantic::GS_ArrayType> GS_ASTBuilder::CreateArrayType(Semantic::GSTypePtr elementsType,
                                                                             U64 size) {
        return _context.GetArrayType(std::move(elementsType),
                                     size);
    }

    GSValuePtr GS_ASTBuilder::CreateValue(Semantic::GSTypePtr type) {
        return GS_Value::Create(std::move(type));
    }

    ValuePtr<GS_BoolValue> GS_ASTBuilder::CreateBoolValue(Bool value) {
        return GS_BoolValue::Create(value);
    }

    ValuePtr<GS_CharValue> GS_ASTBuilder::CreateCharValue(USymbol value) {
        return GS_CharValue::Create(std::move(value));
    }

    ValuePtr<GS_I8Value> GS_ASTBuilder::CreateI8Value(I8 value) {
        return GS_I8Value::Create(value);
    }

    ValuePtr<GS_I16Value> GS_ASTBuilder::CreateI16Value(I16 value) {
        return GS_I16Value::Create(value);
    }

    ValuePtr<GS_I32Value> GS_ASTBuilder::CreateI32Value(I32 value) {
        return GS_I32Value::Create(value);
    }

    ValuePtr<GS_I64Value> GS_ASTBuilder::CreateI64Value(I64 value) {
        return GS_I64Value::Create(value);
    }

    ValuePtr<GS_U8Value> GS_ASTBuilder::CreateU8Value(U8 value) {
        return GS_U8Value::Create(value);
    }

    ValuePtr<GS_U16Value> GS_ASTBuilder::CreateU16Value(U16 value) {
        return GS_U16Value::Create(value);
    }

    ValuePtr<GS_U32Value> GS_ASTBuilder::CreateU32Value(U32 value) {
        return GS_U32Value::Create(value);
    }

    ValuePtr<GS_U64Value> GS_ASTBuilder::CreateU64Value(U64 value) {
        return GS_U64Value::Create(value);
    }

    ValuePtr<GS_StringValue> GS_ASTBuilder::CreateStringValue(UString value) {
        return GS_StringValue::Create(std::move(value));
    }

    GSTranslationUnitDeclarationPtr GS_ASTBuilder::CreateTranslationUnitDeclaration(UString name,
                                                                                    GSNodePtrArray nodes) {
        return GS_TranslationUnitDeclaration::Create(std::move(name),
                                                     std::move(nodes));
    }

    GSTranslationUnitDeclarationPtr GS_ASTBuilder::CreateTranslationUnitDeclaration(UString name) {
        return GS_TranslationUnitDeclaration::Create(std::move(name));
    }

    GS_FunctionQualifiers GS_ASTBuilder::CreateFunctionQualifiers(ExternType externType) {
        return GS_FunctionQualifiers::Create(externType);
    }

    GS_FunctionQualifiers GS_ASTBuilder::CreateFunctionQualifiers() {
        return GS_FunctionQualifiers::Create();
    }

    GS_FunctionParam GS_ASTBuilder::CreateFunctionParam(UString name,
                                                        Semantic::GSTypePtr type) {
        return GS_FunctionParam::Create(std::move(name),
                                        std::move(type));
    }

    GS_FunctionSignature GS_ASTBuilder::CreateFunctionSignature(GSFunctionParamArray params,
                                                                Semantic::GSTypePtr returnType,
                                                                GS_FunctionQualifiers qualifiers) {
        return GS_FunctionSignature::Create(std::move(params),
                                            std::move(returnType),
                                            qualifiers);
    }

    GS_FunctionSignature GS_ASTBuilder::CreateFunctionSignature(GSFunctionParamArray params,
                                                                Semantic::GSTypePtr returnType) {
        return GS_FunctionSignature::Create(std::move(params),
                                            std::move(returnType));
    }

    GS_FunctionSignature GS_ASTBuilder::CreateFunctionSignature(GSFunctionParamArray params) {
        return GS_FunctionSignature::Create(std::move(params));
    }

    GS_FunctionSignature GS_ASTBuilder::CreateFunctionSignature(Semantic::GSTypePtr returnType) {
        return GS_FunctionSignature::Create(std::move(returnType));
    }

    GS_FunctionSignature GS_ASTBuilder::CreateFunctionSignature() {
        return GS_FunctionSignature::Create();
    }

    NodePtr<GS_FunctionDeclaration> GS_ASTBuilder::CreateFunctionDeclaration(UString name,
                                                                             GS_FunctionSignature signature,
                                                                             GSStatementPtrArray body) {
        return GS_FunctionDeclaration::Create(std::move(name),
                                              std::move(signature),
                                              std::move(body));
    }

    NodePtr<GS_FunctionDeclaration> GS_ASTBuilder::CreateFunctionDeclaration(UString name,
                                                                             GS_FunctionSignature signature) {
        return GS_FunctionDeclaration::Create(std::move(name),
                                              std::move(signature));
    }

    NodePtr<GS_FunctionDeclaration> GS_ASTBuilder::CreateFunctionDeclaration(UString name,
                                                                             GSStatementPtrArray statements) {
        return GS_FunctionDeclaration::Create(std::move(name),
                                              std::move(statements));
    }

    NodePtr<GS_FunctionDeclaration> GS_ASTBuilder::CreateFunctionDeclaration(UString name) {
        return GS_FunctionDeclaration::Create(std::move(name));
    }

    NodePtr<GS_VariableDeclarationStatement> GS_ASTBuilder::CreateVariableDeclarationStatement(UString name,
                                                                                               Semantic::GSTypePtr type,
                                                                                               GSExpressionPtr expression) {
        return GS_VariableDeclarationStatement::Create(std::move(name),
                                                       std::move(type),
                                                       std::move(expression));
    }

    NodePtr<GS_VariableDeclarationStatement> GS_ASTBuilder::CreateVariableDeclarationStatement(UString name,
                                                                                               Semantic::GSTypePtr type) {
        return GS_VariableDeclarationStatement::Create(std::move(name),
                                                       std::move(type));
    }

    NodePtr<GS_VariableDeclarationStatement> GS_ASTBuilder::CreateVariableDeclarationStatement(UString name,
                                                                                               GSExpressionPtr expression) {
        return GS_VariableDeclarationStatement::Create(std::move(name),
                                                       std::move(expression));
    }

    NodePtr<GS_AssignmentStatement> GS_ASTBuilder::CreateAssignmentStatement(GSExpressionPtr lvalueExpression,
                                                                             GSExpressionPtr rvalueExpression) {
        return GS_AssignmentStatement::Create(std::move(lvalueExpression),
                                              std::move(rvalueExpression));
    }

    NodePtr<GS_IfStatement> GS_ASTBuilder::CreateIfStatement(GSExpressionPtr condition,
                                                             GSStatementPtrArray ifBody,
                                                             GSStatementPtrArray elseBody) {
        return GS_IfStatement::Create(std::move(condition),
                                      std::move(ifBody),
                                      std::move(elseBody));
    }

    NodePtr<GS_IfStatement> GS_ASTBuilder::CreateIfStatement(GSExpressionPtr condition,
                                                             GSStatementPtrArray ifBody) {
        return GS_IfStatement::Create(std::move(condition),
                                      std::move(ifBody));
    }

    NodePtr<GS_IfStatement> GS_ASTBuilder::CreateIfStatement(GSExpressionPtr condition) {
        return GS_IfStatement::Create(std::move(condition));
    }

    NodePtr<GS_ForStatement> GS_ASTBuilder::CreateForStatement(UString name,
                                                               GSExpressionPtr expression,
                                                               GSStatementPtrArray body) {
        return GS_ForStatement::Create(std::move(name),
                                       std::move(expression),
                                       std::move(body));
    }

    NodePtr<GS_ForStatement> GS_ASTBuilder::CreateForStatement(UString name,
                                                               GSExpressionPtr expression) {
        return GS_ForStatement::Create(std::move(name),
                                       std::move(expression));
    }

    NodePtr<GS_WhileStatement> GS_ASTBuilder::CreateWhileStatement(GSExpressionPtr condition,
                                                                   GSStatementPtrArray body) {
        return GS_WhileStatement::Create(std::move(condition),
                                         std::move(body));
    }

    NodePtr<GS_WhileStatement> GS_ASTBuilder::CreateWhileStatement(GSExpressionPtr condition) {
        return GS_WhileStatement::Create(std::move(condition));
    }

    NodePtr<GS_ExpressionStatement> GS_ASTBuilder::CreateExpressionStatement(GSExpressionPtr expression) {
        return GS_ExpressionStatement::Create(std::move(expression));
    }

    NodePtr<GS_LiteralExpression> GS_ASTBuilder::CreateConstantExpression(GSValuePtr value) {
        return GS_LiteralExpression::Create(std::move(value));
    }

    NodePtr<GS_LiteralExpression> GS_ASTBuilder::CreateConstantExpression(Bool value) {
        return CreateConstantExpression(CreateBoolValue(value));
    }

    NodePtr<GS_LiteralExpression> GS_ASTBuilder::CreateConstantExpression(USymbol value) {
        return CreateConstantExpression(CreateCharValue(std::move(value)));
    }

    NodePtr<GS_LiteralExpression> GS_ASTBuilder::CreateConstantExpression(I8 value) {
        return CreateConstantExpression(CreateI8Value(value));
    }

    NodePtr<GS_LiteralExpression> GS_ASTBuilder::CreateConstantExpression(I16 value) {
        return CreateConstantExpression(CreateI16Value(value));
    }

    NodePtr<GS_LiteralExpression> GS_ASTBuilder::CreateConstantExpression(I32 value) {
        return CreateConstantExpression(CreateI32Value(value));
    }

    NodePtr<GS_LiteralExpression> GS_ASTBuilder::CreateConstantExpression(I64 value) {
        return CreateConstantExpression(CreateI64Value(value));
    }

    NodePtr<GS_LiteralExpression> GS_ASTBuilder::CreateConstantExpression(U8 value) {
        return CreateConstantExpression(CreateU8Value(value));
    }

    NodePtr<GS_LiteralExpression> GS_ASTBuilder::CreateConstantExpression(U16 value) {
        return CreateConstantExpression(CreateU16Value(value));
    }

    NodePtr<GS_LiteralExpression> GS_ASTBuilder::CreateConstantExpression(U32 value) {
        return CreateConstantExpression(CreateU32Value(value));
    }

    NodePtr<GS_LiteralExpression> GS_ASTBuilder::CreateConstantExpression(U64 value) {
        return CreateConstantExpression(CreateU64Value(value));
    }

    NodePtr<GS_LiteralExpression> GS_ASTBuilder::CreateConstantExpression(UString value) {
        return CreateConstantExpression(CreateStringValue(std::move(value)));
    }

    NodePtr<GS_UnaryExpression> GS_ASTBuilder::CreateUnaryExpression(UnaryOperation operation,
                                                                     GSExpressionPtr expression) {
        return GS_UnaryExpression::Create(operation,
                                          std::move(expression));
    }

    NodePtr<GS_BinaryExpression> GS_ASTBuilder::CreateBinaryExpression(BinaryOperation operation,
                                                                       GSExpressionPtr firstExpression,
                                                                       GSExpressionPtr secondExpression) {
        return GS_BinaryExpression::Create(operation,
                                           std::move(firstExpression),
                                           std::move(secondExpression));
    }

    NodePtr<GS_ArrayExpression> GS_ASTBuilder::CreateArrayExpression(GSExpressionPtrArray expressions) {
        return GS_ArrayExpression::Create(std::move(expressions));
    }

    NodePtr<GS_VariableUsingExpression> GS_ASTBuilder::CreateVariableUsingExpression(UString name) {
        return GS_VariableUsingExpression::Create(std::move(name));
    }

    NodePtr<GS_VariableUsingExpression> GS_ASTBuilder::CreateVariableUsingExpression(UString name,
                                                                                     IO::GS_SourceRange nameLocationRange) {
        return GS_VariableUsingExpression::Create(std::move(name),
                                                  nameLocationRange);
    }

    NodePtr<GS_FunctionCallingExpression> GS_ASTBuilder::CreateFunctionCallingExpression(UString name,
                                                                                         GSExpressionPtrArray params) {
        return GS_FunctionCallingExpression::Create(std::move(name),
                                                    std::move(params));
    }

    LRef<GS_ASTContext> GS_ASTBuilder::GetContext() {
        return _context;
    }

}
