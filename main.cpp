//#include <rapidjson/document.h>

//#include <Driver/Driver.h>

#include <AST/AST.h>
#include <Optimizer/Optimizer.h>
#include <Semantic/Semantic.h>
#include <CodeGenerator/CodeGenerator.h>

using namespace GSLanguageCompiler;

class PrintVisitor : public AST::GS_Visitor {
public:

    Void VisitTranslationUnitDeclaration(LRef<SharedPtr<AST::GS_TranslationUnitDeclaration>> translationUnitDeclaration) override {
        Print("TranslationUnitDeclaration: {"_us);

        AddTab();

        Print("Name: "_us + translationUnitDeclaration->GetName());

        Print("Nodes: {"_us);

        AddTab();

        for (auto &node : translationUnitDeclaration->GetNodes()) {
            VisitNode(node);
        }

        SubTab();

        Print("}"_us);

        SubTab();

        Print("}"_us);
    }

    Void VisitFunctionDeclaration(LRef<SharedPtr<AST::GS_FunctionDeclaration>> functionDeclaration) override {
        Print("FunctionDeclaration: {"_us);

        AddTab();

        Print("Name: "_us + functionDeclaration->GetName());

        auto signature = functionDeclaration->GetSignature();

        auto paramTypes = signature.GetParamTypes();
        auto returnType = signature.GetReturnType();

        auto signatureMessage = "Signature: ("_us;

        for (auto &paramType : paramTypes) {
            signatureMessage += paramType->GetName() + " "_us;
        }

        signatureMessage += ") -> "_us + returnType->GetName();

        Print(signatureMessage);

        Print("Body: {"_us);

        AddTab();

        for (auto &statement : functionDeclaration->GetBody()) {
            VisitStatement(statement);
        }

        SubTab();

        Print("}"_us);

        SubTab();

        Print("}"_us);
    }

    Void VisitVariableDeclarationStatement(LRef<SharedPtr<AST::GS_VariableDeclarationStatement>> variableDeclarationStatement) override {
        Print("VariableDeclarationStatement: {"_us);

        AddTab();

        Print("Name: "_us + variableDeclarationStatement->GetName());

        Print("Type: "_us + variableDeclarationStatement->GetType()->GetName());

        Print("Expression: {"_us);

        AddTab();

        VisitExpression(variableDeclarationStatement->GetExpression());

        SubTab();

        Print("}"_us);

        SubTab();

        Print("}"_us);
    }

    Void VisitAssignmentStatement(LRef<SharedPtr<AST::GS_AssignmentStatement>> assignmentStatement) override {
        Print("AssignmentStatement: {"_us);

        AddTab();

        Print("LValueExpression: {"_us);

        AddTab();

        VisitExpression(assignmentStatement->GetLValueExpression());

        SubTab();

        Print("}"_us);

        Print("RValueExpression: {"_us);

        AddTab();

        VisitExpression(assignmentStatement->GetRValueExpression());

        SubTab();

        Print("}"_us);

        SubTab();

        Print("}"_us);
    }

    Void VisitExpressionStatement(LRef<SharedPtr<AST::GS_ExpressionStatement>> expressionStatement) override {
        Print("ExpressionStatement: {"_us);

        AddTab();

        VisitExpression(expressionStatement->GetExpression());

        SubTab();

        Print("}"_us);
    }

    Void VisitConstantExpression(LRef<SharedPtr<AST::GS_ConstantExpression>> constantExpression) override {
        Print("ConstantExpression: {"_us);

        AddTab();

        Print("Value: {"_us);

        AddTab();

        auto value = AST::GSValueCast<AST::GS_LiteralValue>(constantExpression->GetValue());
        auto typeName = value->GetType()->GetName();

        Print("Type: " + typeName.AsString());

        if (typeName == "I32"_us) {
            Print("Value: "_us + UString(std::to_string(value->GetValueWithCast<I32>())));
        } else if (typeName == "String"_us) {
            Print("Value: "_us + value->GetValueWithCast<UString>());
        }

        SubTab();

        Print("}"_us);

        SubTab();

        Print("}"_us);
    }

    Void VisitUnaryExpression(LRef<SharedPtr<AST::GS_UnaryExpression>> unaryExpression) override {
        Print("UnaryExpression: {"_us);

        AddTab();

        Print("Expression: {"_us);

        AddTab();

        VisitExpression(unaryExpression->GetExpression());

        SubTab();

        Print("}"_us);

        auto operation = unaryExpression->GetUnaryOperation();

        UString stringOperation;

        switch (operation) {
            case AST::UnaryOperation::Minus:
                stringOperation = "Minus (-)"_us;

                break;
        }

        Print("Operation: "_us + stringOperation);

        SubTab();

        Print("}"_us);
    }

    Void VisitBinaryExpression(LRef<SharedPtr<AST::GS_BinaryExpression>> binaryExpression) override {
        Print("BinaryExpression: {"_us);

        AddTab();

        Print("FirstExpression: {"_us);

        AddTab();

        VisitExpression(binaryExpression->GetFirstExpression());

        SubTab();

        Print("}"_us);

        Print("SecondExpression: {"_us);

        AddTab();

        VisitExpression(binaryExpression->GetSecondExpression());

        SubTab();

        Print("}"_us);

        auto operation = binaryExpression->GetBinaryOperation();

        UString stringOperation;

        switch (operation) {
            case AST::BinaryOperation::Plus:
                stringOperation = "Plus (+)"_us;

                break;
            case AST::BinaryOperation::Minus:
                stringOperation = "Minus (-)"_us;

                break;
            case AST::BinaryOperation::Star:
                stringOperation = "Star (*)"_us;

                break;
            case AST::BinaryOperation::Slash:
                stringOperation = "Slash (/)"_us;

                break;
        }

        Print("Operation: "_us + stringOperation);

        SubTab();

        Print("}"_us);
    }

    Void VisitVariableUsingExpression(LRef<SharedPtr<AST::GS_VariableUsingExpression>> variableUsingExpression) override {
        Print("VariableUsingExpression: {"_us);

        AddTab();

        Print("Name: "_us + variableUsingExpression->GetName());

        SubTab();

        Print("}"_us);
    }

    Void VisitFunctionCallingExpression(LRef<SharedPtr<AST::GS_FunctionCallingExpression>> functionCallingExpression) override {
        Print("FunctionCallingExpression: {"_us);

        AddTab();

        Print("Name: "_us + functionCallingExpression->GetName());

        Print("Params: {"_us);

        AddTab();

        for (auto &param: functionCallingExpression->GetParams()) {
            VisitExpression(param);
        }

        SubTab();

        Print("}"_us);

        SubTab();

        Print("}"_us);
    }

private:

    Void Print(UString message) {
        PrintTabs();

        UCOut() << message << "\n"_us;
    }

    Void PrintTabs() {
        for (auto i = 0; i < tabsNumber; ++i) {
            UCOut() << "  "_us;
        }
    }

    Void AddTab() {
        ++tabsNumber;
    }

    Void SubTab() {
        --tabsNumber;
    }

private:

    I32 tabsNumber = 0;
};

class PrintPass : public AST::GS_VisitPass<PrintVisitor> {};

AST::GSPassPtr CreatePrintPass() {
    return std::make_shared<PrintPass>();
}

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

inline Void PrintModule(LRef<CodeGenerator::GSCGContextPtr> context) {
    std::reinterpret_pointer_cast<CodeGenerator::GS_LLVMCGContext>(context)->GetModule().print(llvm::errs(), nullptr);
}

#include <Parser/Parser.h>

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

AST::GSTranslationUnitDeclarationPtr BuildMain() {
    auto Builder = AST::GS_ASTBuilder::Create();

    auto Unit = Builder->CreateTranslationUnitDeclaration("main");

    auto FunctionSignature = Builder->CreateFunctionSignature(Builder->CreateI32Type());

    auto Function = Builder->CreateFunctionDeclaration("main", FunctionSignature);

    Unit->AddNode(Function);

    return Unit;
}

Void Func() {
    auto program = BuildMain();

    auto PM = AST::GS_PassManager::Create();

    PM->AddPass(CreatePrintPass());

//    PM->AddPass(CreateTypeCheckPass());

//    PM->AddPass(CreatePrintPass());

//    PM->AddPass(CreateManglePass(GS_ABI::Create()->GetMangler()));

//    PM->AddPass(CreatePrintPass());

    PM->Run(program);

//    auto Optimizer = Optimizer::GS_Optimizer::Create();
//
//    Optimizer->Optimize(program);
//
//    auto CG = CodeGenerator::GS_CodeGenerator::CreateLLVMCG();
//
//    CG->Generate(program);
//
//    auto context = CG->GetContext();
//
//    PrintModule(context);
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
