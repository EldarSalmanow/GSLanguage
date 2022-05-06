//#include <rapidjson/document.h>

#include <Driver/Driver.h>

#include <AST/AST.h>
#include <Semantic/Semantic.h>

using namespace GSLanguageCompiler;

class TypeCheckVisitor : public AST::GS_Visitor {
public:

    Void VisitVariableDeclarationStatement(LRef<SharedPtr<AST::GS_VariableDeclarationStatement>> variableDeclarationStatement) override {
        auto type = variableDeclarationStatement->GetType();
        auto expression = variableDeclarationStatement->GetExpression();

        auto calculatedExpressionType = CalculateType(expression);

        auto typeName = type->GetName();
        auto calculatedExpressionTypeName = calculatedExpressionType->GetName();

        if (typeName != calculatedExpressionTypeName) {
            UCOut() << typeName << " != "_us << calculatedExpressionTypeName << "\n"_us;
        }
    }

public:

    Semantic::GSTypePtr CalculateType(LRef<AST::GSExpressionPtr> expression) {
        if (auto constantExpression = AST::ToExpression<AST::GS_ConstantExpression>(expression)) {
            return CalculateType(constantExpression);
        }

        if (auto unaryExpression = AST::ToExpression<AST::GS_UnaryExpression>(expression)) {
            return CalculateType(unaryExpression);
        }

        if (auto binaryExpression = AST::ToExpression<AST::GS_BinaryExpression>(expression)) {
            return CalculateType(binaryExpression);
        }

        return nullptr;
    }

    Semantic::GSTypePtr CalculateType(SharedPtr<AST::GS_ConstantExpression> constantExpression) {
        auto value = constantExpression->GetValue();

        auto valueType = value->GetType();

        return valueType;
    }

    Semantic::GSTypePtr CalculateType(SharedPtr<AST::GS_UnaryExpression> unaryExpression) {
        auto expression = unaryExpression->GetExpression();

        return CalculateType(expression);
    }

    Semantic::GSTypePtr CalculateType(SharedPtr<AST::GS_BinaryExpression> binaryExpression) {
        auto firstExpression = binaryExpression->GetFirstExpression();
        auto secondExpression = binaryExpression->GetSecondExpression();

        auto firstExpressionType = CalculateType(firstExpression);
        auto secondExpressionType = CalculateType(secondExpression);

        if (firstExpressionType->GetName() == secondExpressionType->GetName()) {
            return firstExpressionType;
        }

        return nullptr;
    }
};

class TypeCheckPass : public AST::GS_VisitPass<TypeCheckVisitor> {};

AST::GSPassPtr CreateTypeCheckPass() {
    return std::make_shared<TypeCheckPass>();
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

class MangleVisitor : public AST::GS_Visitor {
public:

    explicit MangleVisitor(SharedPtr<Mangler> mangler)
            : _mangler(std::move(mangler)) {}

public:

    Void VisitTranslationUnitDeclaration(LRef<SharedPtr<AST::GS_TranslationUnitDeclaration>> translationUnitDeclaration) override {
        AST::GS_Visitor::VisitTranslationUnitDeclaration(translationUnitDeclaration);

        auto &name = translationUnitDeclaration->GetName();

        name = _mangler->MangleUnitName(name);
    }

    Void VisitFunctionDeclaration(LRef<SharedPtr<AST::GS_FunctionDeclaration>> functionDeclaration) override {
        AST::GS_Visitor::VisitFunctionDeclaration(functionDeclaration);

        auto &name = functionDeclaration->GetName();

        name = _mangler->MangleFunctionName(name);
    }

private:

    SharedPtr<Mangler> _mangler;
};

class ManglePass : public AST::GS_Pass {
public:

    explicit ManglePass(SharedPtr<Mangler> mangler)
            : _mangler(std::move(mangler)) {}

public:

    Void Run(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration) override {
        MangleVisitor visitor(_mangler);

        visitor.VisitTranslationUnitDeclaration(translationUnitDeclaration);
    }

private:

    SharedPtr<Mangler> _mangler;
};

AST::GSPassPtr CreateManglePass(SharedPtr<Mangler> mangler) {
    return std::make_shared<ManglePass>(mangler);
}

AST::GSTranslationUnitDeclarationPtr CreateProgram() {
    /**
     * main.gs
     *
     * func main() {
     *     var number = 3 + 10
     * }
     *
     */

    auto Builder = AST::GS_ASTBuilder::Create();

    auto Unit = Builder->CreateTranslationUnitDeclaration("main");

    auto Function = Builder->CreateFunctionDeclaration("main");

    Unit->AddNode(Function);

    auto Expression = Builder->CreateBinaryExpression(AST::BinaryOperation::Plus, Builder->CreateConstantExpression(3), Builder->CreateConstantExpression(10));

    auto Variable = Builder->CreateVariableDeclarationStatement("number", Builder->CreateI32Type(), Expression);

    Function->AddStatement(Variable);

    return Unit;
}

// TODO add Writer module for writing output code

AST::GSTranslationUnitDeclarationPtr CreateUnit() {
    auto Builder = AST::GS_ASTBuilder::Create();

    auto Unit = Builder->CreateTranslationUnitDeclaration("main");

    auto FunctionSignature = Builder->CreateFunctionSignature(Builder->CreateI32Type());

    auto Function = Builder->CreateFunctionDeclaration("main", FunctionSignature);

    Unit->AddNode(Function);

    return Unit;
}

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C8>> argv) {
    return Driver::GS_Compiler::Start(argc, argv);
}
