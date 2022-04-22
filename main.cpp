#include <Driver/Driver.h>

#include <AST/AST.h>

using namespace GSLanguageCompiler;

class ConstantFoldingTransformer : public AST::GS_Transformer {
public:

    AST::GSNodePtr TransformUnaryExpression(LRef<SharedPtr<AST::GS_UnaryExpression>> unaryExpression) override {
        unaryExpression = AST::ToExpression<AST::GS_UnaryExpression>(GS_Transformer::TransformUnaryExpression(unaryExpression));

        auto expression = unaryExpression->GetExpression();
        auto operation = unaryExpression->GetUnaryOperation();

        if (auto constantExpression = AST::ToExpression<AST::GS_ConstantExpression>(expression)) {
            auto value = constantExpression->GetValue();

            if (auto i32Value = AST::GSValueCast<AST::GS_I32Value>(value)) {
                auto number = i32Value->GetI32Value();

                switch (operation) {
                    case AST::UnaryOperation::Minus:
                        number = -number;

                        break;
                }

                return AST::GS_ConstantExpression::Create(AST::GS_I32Value::Create(number));
            }
        }

        return unaryExpression;
    }
};

class ConstantFoldingPass : public AST::GS_TransformPass<ConstantFoldingTransformer> {};

inline AST::GSPassPtr CreateConstantFoldingPass() {
    return std::make_shared<ConstantFoldingPass>();
}

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
    /**
     * main.gs
     *
     * func main() {
     *     var number = -3
     * }
     *
     */

    auto Builder = AST::GS_ASTBuilder::Create();

    auto Unit = Builder->CreateTranslationUnitDeclaration("main");

    auto Function = Builder->CreateFunctionDeclaration("main");

    Unit->AddNode(Function);

    auto Expression = Builder->CreateUnaryExpression(AST::UnaryOperation::Minus, Builder->CreateConstantExpression(3));

    auto Variable = Builder->CreateVariableDeclarationStatement("number", Builder->CreateI32Type(), Expression);

    Function->AddStatement(Variable);

    return Unit;
}

Void Func() {
    auto program = CreateProgram(GS_ABI::Create());

    auto PM = AST::GS_PassManager::Create();

    PM->AddPass(CreateConstantFoldingPass());

    PM->Run(program);
}

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C8>> argv) {
    Func();

    return 0;
//    return Driver::GS_Compiler::Start(argc, argv);
}
