#include <Driver/Driver.h>

#include <AST/AST.h>

using namespace GSLanguageCompiler;

class GS_TypeContext {
public:

    GS_TypeContext()
            : _voidType(AST::GS_VoidType::Create()),
              _i32Type(AST::GS_I32Type::Create()),
              _stringType(AST::GS_StringType::Create()) {}

public:

    static SharedPtr<GS_TypeContext> Create() {
        return std::make_shared<GS_TypeContext>();
    }

public:

    SharedPtr<AST::GS_VoidType> GetVoidType() const {
        return _voidType;
    }

    SharedPtr<AST::GS_I32Type> GetI32Type() const {
        return _i32Type;
    }

    SharedPtr<AST::GS_StringType> GetStringType() const {
        return _stringType;
    }

private:

    SharedPtr<AST::GS_VoidType>   _voidType;

    SharedPtr<AST::GS_I32Type>    _i32Type;

    SharedPtr<AST::GS_StringType> _stringType;
};

class GS_ASTContext {
public:

    GS_ASTContext()
            : _typeContext(GS_TypeContext::Create()) {}

public:

    static SharedPtr<GS_ASTContext> Create() {
        return std::make_shared<GS_ASTContext>();
    }

public:

    SharedPtr<AST::GS_VoidType> GetVoidType() const {
        return _typeContext->GetVoidType();
    }

    SharedPtr<AST::GS_I32Type> GetI32Type() const {
        return _typeContext->GetI32Type();
    }

    SharedPtr<AST::GS_StringType> GetStringType() const {
        return _typeContext->GetStringType();
    }

private:

    SharedPtr<GS_TypeContext> _typeContext;
};

class GS_ASTBuilder {
public:

    explicit GS_ASTBuilder(SharedPtr<GS_ASTContext> context)
            : _context(std::move(context)) {}

public:

    static SharedPtr<GS_ASTBuilder> Create(SharedPtr<GS_ASTContext> context) {
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

    SharedPtr<GS_ASTContext> GetContext() {
        return _context;
    }

private:

    SharedPtr<GS_ASTContext> _context;

    SharedPtr<AST::GS_TranslationUnitDeclaration> _currentUnit;

    SharedPtr<AST::GS_FunctionDeclaration> _currentFunction;
};

Void Func() {
    auto Builder = GS_ASTBuilder::Create();

    /**
     * main.gs
     *
     * func main() {
     *     var number = 7 + 11
     * }
     *
     */

    /**
     * main.gs
     *
     * Global {
     *
     * func main() {
     *     Local {
     *         var number = 7 + 11
     *
     *         while 1 < 2 {
     *             Local {
     *                 number += 1
     *             }
     *         }
     *
     *     }
     * }
     *
     * }
     *
     */

    auto Unit = Builder->CreateTranslationUnitDeclaration("_GS_U4main");

    auto Function = Builder->CreateFunctionDeclaration("_GS_F4main");

    Unit->AddNode(Function);

    auto Expression1 = Builder->CreateConstantExpression(7);
    auto Expression2 = Builder->CreateConstantExpression(11);

    auto Expression3 = Builder->CreateBinaryExpression(AST::BinaryOperation::Plus, Expression1, Expression2);

    auto Variable = Builder->CreateVariableDeclarationStatement("number", Builder->CreateI32Type(), Expression3);
}

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C8>> argv) {
    return Driver::GS_Compiler::Start(argc, argv);
}
