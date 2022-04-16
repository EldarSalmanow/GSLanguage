#include <Driver/Driver.h>

#include <AST/AST.h>

using namespace GSLanguageCompiler;

class Mangler {
public:

    virtual ~Mangler() = default;

public:

    virtual UString MangleUnitName(UString name) = 0;

    virtual UString MangleFunctionName(UString name) = 0;
};

class ABI {
public:

    virtual ~ABI() = default;

public:

    virtual SharedPtr<Mangler> GetMangler() = 0;
};

class GS_Mangler : public Mangler {
public:

    static SharedPtr<GS_Mangler> Create() {
        return std::make_shared<GS_Mangler>();
    }

public:

    /**
     * _GS_U + name size + name
     * ex: main -> _GS_U4main
     */
    UString MangleUnitName(UString name) override {
        return UString("_GS_U" + std::to_string(name.Size()) + name.AsString());
    }

    /**
     * _GS_F + name size + name
     * ex: main -> _GS_F4main
     */
    UString MangleFunctionName(UString name) override {
        return UString("_GS_F" + std::to_string(name.Size()) + name.AsString());
    }
};

class GS_ABI : public ABI {
public:

    static SharedPtr<GS_ABI> Create() {
        return std::make_shared<GS_ABI>();
    }

public:

    SharedPtr<Mangler> GetMangler() override {
        return GS_Mangler::Create();
    }
};

AST::GSTranslationUnitDeclarationPtr CreateProgram(SharedPtr<ABI> abi) {
    auto Mangler = abi->GetMangler();

    auto Builder = AST::GS_ASTBuilder::Create();

    /**
     * main.gs
     *
     * func main() {
     *     var number = -7
     * }
     *
     */

    auto Unit = Builder->CreateTranslationUnitDeclaration(Mangler->MangleUnitName("main"));

    auto Function = Builder->CreateFunctionDeclaration(Mangler->MangleFunctionName("main"));

    Unit->AddNode(Function);

    auto Expression1 = Builder->CreateConstantExpression(7);

    auto Expression2 = Builder->CreateUnaryExpression(AST::UnaryOperation::Minus, Expression1);

    auto Variable = Builder->CreateVariableDeclarationStatement("number", Builder->CreateI32Type(), Expression2);

    Function->AddStatement(Variable);

    return Unit;
}

Void Func() {
    auto program = CreateProgram(GS_ABI::Create());
}

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C8>> argv) {
    return Driver::GS_Compiler::Start(argc, argv);
}
