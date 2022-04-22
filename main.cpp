//#include <Driver/Driver.h>

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

class PrintVisitor : public AST::GS_Visitor {
public:

    Void VisitTranslationUnitDeclaration(LRef<SharedPtr<AST::GS_TranslationUnitDeclaration>> translationUnitDeclaration) override {
        Print("TranslationUnitDeclaration: {");

        AddTab();

        Print("Name: " + translationUnitDeclaration->GetName().AsString());

        Print("Nodes: {");

        AddTab();

        for (auto &node : translationUnitDeclaration->GetNodes()) {
            VisitNode(node);
        }

        SubTab();

        Print("}");

        SubTab();

        Print("}");
    }

    Void VisitFunctionDeclaration(LRef<SharedPtr<AST::GS_FunctionDeclaration>> functionDeclaration) override {
        Print("FunctionDeclaration: {");

        AddTab();

        Print("Name: " + functionDeclaration->GetName().AsString());

        Print("Body: {");

        AddTab();

        for (auto &statement : functionDeclaration->GetBody()) {
            VisitStatement(statement);
        }

        SubTab();

        Print("}");

        SubTab();

        Print("}");
    }

    Void VisitVariableDeclarationStatement(LRef<SharedPtr<AST::GS_VariableDeclarationStatement>> variableDeclarationStatement) override {
        Print("VariableDeclarationStatement: {");

        AddTab();

        Print("Name: " + variableDeclarationStatement->GetName().AsString());

        Print("Type: " + variableDeclarationStatement->GetType()->GetName().AsString());

        Print("Expression: {");

        AddTab();

        VisitExpression(variableDeclarationStatement->GetExpression());

        SubTab();

        Print("}");

        SubTab();

        Print("}");
    }

    Void VisitAssignmentStatement(LRef<SharedPtr<AST::GS_AssignmentStatement>> assignmentStatement) override {
        Print("AssignmentStatement: {");

        AddTab();

        Print("LValueExpression: {");

        AddTab();

        VisitExpression(assignmentStatement->GetLValueExpression());

        SubTab();

        Print("}");

        Print("RValueExpression: {");

        AddTab();

        VisitExpression(assignmentStatement->GetRValueExpression());

        SubTab();

        Print("}");

        SubTab();

        Print("}");
    }

    Void VisitExpressionStatement(LRef<SharedPtr<AST::GS_ExpressionStatement>> expressionStatement) override {
        Print("ExpressionStatement: {");

        AddTab();

        VisitExpression(expressionStatement->GetExpression());

        SubTab();

        Print("}");
    }

    Void VisitConstantExpression(LRef<SharedPtr<AST::GS_ConstantExpression>> constantExpression) override {
        Print("ConstantExpression: {");

        AddTab();

        Print("Value: {");

        AddTab();

        auto value = AST::GSValueCast<AST::GS_LiteralValue>(constantExpression->GetValue());
        auto typeName = value->GetType()->GetName();

        Print("Type: " + typeName.AsString());

        if (typeName == "I32"_us) {
            Print("Value: " + std::to_string(value->GetValueWithCast<I32>()));
        } else if (typeName == "String"_us) {
            Print("Value: " + value->GetValueWithCast<UString>().AsString());
        }

        SubTab();

        Print("}");

        SubTab();

        Print("}");
    }

    Void VisitUnaryExpression(LRef<SharedPtr<AST::GS_UnaryExpression>> unaryExpression) override {
        Print("UnaryExpression: {");

        AddTab();

        Print("Expression: {");

        AddTab();

        VisitExpression(unaryExpression->GetExpression());

        SubTab();

        Print("}");

        auto operation = unaryExpression->GetUnaryOperation();

        String stringOperation;

        switch (operation) {
            case AST::UnaryOperation::Minus:
                stringOperation = "Minus (-)";

                break;
        }

        Print("Operation: " + stringOperation);

        SubTab();

        Print("}");
    }

    Void VisitBinaryExpression(LRef<SharedPtr<AST::GS_BinaryExpression>> binaryExpression) override {
        Print("BinaryExpression: {");

        AddTab();

        Print("FirstExpression: {");

        AddTab();

        VisitExpression(binaryExpression->GetFirstExpression());

        SubTab();

        Print("}");

        Print("SecondExpression: {");

        AddTab();

        VisitExpression(binaryExpression->GetSecondExpression());

        SubTab();

        Print("}");

        auto operation = binaryExpression->GetBinaryOperation();

        String stringOperation;

        switch (operation) {
            case AST::BinaryOperation::Plus:
                stringOperation = "Plus (+)";

                break;
            case AST::BinaryOperation::Minus:
                stringOperation = "Minus (-)";

                break;
            case AST::BinaryOperation::Star:
                stringOperation = "Star (*)";

                break;
            case AST::BinaryOperation::Slash:
                stringOperation = "Slash (/)";

                break;
        }

        Print("Operation: " + stringOperation);

        SubTab();

        Print("}");
    }

    Void VisitVariableUsingExpression(LRef<SharedPtr<AST::GS_VariableUsingExpression>> variableUsingExpression) override {
        Print("VariableUsingExpression: {");

        AddTab();

        Print("Name: " + variableUsingExpression->GetName().AsString());

        SubTab();

        Print("}");
    }

    Void VisitFunctionCallingExpression(LRef<SharedPtr<AST::GS_FunctionCallingExpression>> functionCallingExpression) override {
        Print("FunctionCallingExpression: {");

        AddTab();

        Print("Name: " + functionCallingExpression->GetName().AsString());

        Print("Params: {");

        AddTab();

        for (auto &param: functionCallingExpression->GetParams()) {
            VisitExpression(param);
        }

        SubTab();

        Print("}");

        SubTab();

        Print("}");
    }

private:

    Void Print(String message) {
        PrintTabs();

        std::cout << message << std::endl;
    }

    Void PrintTabs() {
        for (auto i = 0; i < tabsNumber; ++i) {
            std::cout << "  ";
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

inline AST::GSPassPtr CreatePrintPass() {
    return std::make_shared<PrintPass>();
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

inline SharedPtr<ABI> GetABI() {
    return GS_ABI::Create();
};

class MangleVisitor : public AST::GS_Visitor {
public:

    explicit MangleVisitor()
            : _mangler(GetABI()->GetMangler()) {}

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

class ManglePass : public AST::GS_VisitPass<MangleVisitor> {};

inline AST::GSPassPtr CreateManglePass() {
    return std::make_shared<ManglePass>();
}

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

    PM->AddPass(CreatePrintPass());

    PM->AddPass(CreateManglePass());

    PM->AddPass(CreatePrintPass());

    PM->AddPass(CreateConstantFoldingPass());

    PM->AddPass(CreatePrintPass());

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
