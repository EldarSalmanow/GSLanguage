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

    AST::GSTypePtr GetVoidType() const {
        return _voidType;
    }

    AST::GSTypePtr GetI32Type() const {
        return _i32Type;
    }

    AST::GSTypePtr GetStringType() const {
        return _stringType;
    }

private:

    AST::GSTypePtr _voidType, _i32Type, _stringType;
};

class GS_ASTContext {
public:

    GS_ASTContext()
            : _typeContext(GS_TypeContext::Create()) {}

public:

    AST::GSTypePtr GetVoidType() {
        return _typeContext->GetVoidType();
    }

    AST::GSTypePtr GetI32Type() {
        return _typeContext->GetI32Type();
    }

    AST::GSTypePtr GetStringType() {
        return _typeContext->GetStringType();
    }

private:

    SharedPtr<GS_TypeContext> _typeContext;
};

class GS_ASTBuilder {
public:

    static SharedPtr<GS_ASTBuilder> Create() {
        return std::make_shared<GS_ASTBuilder>();
    }

public:

    auto CreateValue(AST::GSTypePtr type) {
        return AST::GS_Value::Create(std::move(type));
    }

    template<typename T>
    auto CreateLiteralValue(T value, AST::GSTypePtr type) {
        return AST::GS_LiteralValue::Create(value, std::move(type));
    }

    auto CreateI32Value(I32 number) {
        return AST::GS_I32Value::Create(number);
    }

    auto CreateStringValue(UString name) {
        return AST::GS_StringValue::Create(std::move(name));
    }
};

Void Func() {
    auto builder = GS_ASTBuilder::Create();

    AST::GSValuePtr value = builder->CreateStringValue("a");

    auto string = AST::GSValueCast<AST::GS_StringValue>(value)->GetStringValue();
}

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C8>> argv) {
    return Driver::GS_Compiler::Start(argc, argv);
}
