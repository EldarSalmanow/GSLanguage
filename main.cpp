//#include <rapidjson/document.h>

//#include <Driver/Driver.h>

#include <AST/AST.h>
#include <Optimizer/Optimizer.h>
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

    AST::GSTypePtr CalculateType(LRef<AST::GSExpressionPtr> expression) {
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

    AST::GSTypePtr CalculateType(SharedPtr<AST::GS_ConstantExpression> constantExpression) {
        auto value = constantExpression->GetValue();

        auto valueType = value->GetType();

        return valueType;
    }

    AST::GSTypePtr CalculateType(SharedPtr<AST::GS_UnaryExpression> unaryExpression) {
        auto expression = unaryExpression->GetExpression();

        return CalculateType(expression);
    }

    AST::GSTypePtr CalculateType(SharedPtr<AST::GS_BinaryExpression> binaryExpression) {
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
     *     var number = -3
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

class Symbol {
public:

    virtual ~Symbol() = default;

public:

    virtual Bool IsStructure() const {
        return false;
    }

    virtual Bool IsFunction() const {
        return false;
    }

    virtual Bool IsVariable() const {
        return false;
    }
};

using SymbolPtr = SharedPtr<Symbol>;

using SymbolPtrArray = Vector<SymbolPtr>;

class StructureMethod {
public:

    StructureMethod(UString name, AST::GSStatementPtrArray body)
            : _name(std::move(name)), _body(std::move(body)) {}

public:

    static StructureMethod Create(UString name, AST::GSStatementPtrArray body) {
        return StructureMethod(std::move(name), std::move(body));
    }

public:

    UString GetName() const {
        return _name;
    }

    AST::GSStatementPtrArray GetBody() const {
        return _body;
    }

private:

    UString _name;

    AST::GSStatementPtrArray _body;
};

class StructureField {
public:

    StructureField(UString name, AST::GSTypePtr type)
            : _name(std::move(name)), _type(std::move(type)) {}

public:

    static StructureField Create(UString name, AST::GSTypePtr type) {
        return StructureField(std::move(name), std::move(type));
    }

public:

    UString GetName() const {
        return _name;
    }

    AST::GSTypePtr GetType() const {
        return _type;
    }

private:

    UString _name;

    AST::GSTypePtr _type;
};

#include <optional>

class StructureSymbol : public Symbol {
public:

    StructureSymbol(UString name, Vector<StructureMethod> methods, Vector<StructureField> fields)
            : _name(std::move(name)), _methods(std::move(methods)), _fields(std::move(fields)) {}

public:

    static SharedPtr<StructureSymbol> Create(UString name, Vector<StructureMethod> methods, Vector<StructureField> fields) {
        return std::make_shared<StructureSymbol>(std::move(name), std::move(methods), std::move(fields));
    }

public:

    std::optional<StructureMethod> FindMethod(UString name) {
        for (auto &method : _methods) {
            if (method.GetName() == name) {
                return std::make_optional(method);
            }
        }

        return std::nullopt;
    }

public:

    UString GetName() const {
        return _name;
    }

    Vector<StructureMethod> GetMethods() const {
        return _methods;
    }

    Vector<StructureField> GetFields() const {
        return _fields;
    }

public:

    Bool IsStructure() const override {
        return true;
    }

private:

    UString _name;

    Vector<StructureMethod> _methods;

    Vector<StructureField> _fields;
};

class FunctionSymbol : public Symbol {
public:

    FunctionSymbol(UString name, AST::GSStatementPtrArray body)
            : _name(std::move(name)), _body(std::move(body)) {}

public:

    static SharedPtr<FunctionSymbol> Create(UString name, AST::GSStatementPtrArray body) {
        return std::make_shared<FunctionSymbol>(std::move(name), std::move(body));
    }

public:

    UString GetName() const {
        return _name;
    }

    LRef<AST::GSStatementPtrArray> GetBody() {
        return _body;
    }

public:

    Bool IsFunction() const override {
        return true;
    }

private:

    UString _name;

    AST::GSStatementPtrArray _body;
};

class VariableSymbol : public Symbol {
public:

    VariableSymbol(UString name, AST::GSTypePtr type, AST::GSExpressionPtr expression)
            : _name(std::move(name)), _type(std::move(type)), _expression(std::move(expression)) {}

public:

    static SharedPtr<VariableSymbol> Create(UString name, AST::GSTypePtr type, AST::GSExpressionPtr expression) {
        return std::make_shared<VariableSymbol>(std::move(name), std::move(type), std::move(expression));
    }

public:

    UString GetName() const {
        return _name;
    }

    LRef<AST::GSTypePtr> GetType() {
        return _type;
    }

    LRef<AST::GSExpressionPtr> GetExpression() {
        return _expression;
    }

public:

    Bool IsVariable() const override {
        return true;
    }

private:

    UString _name;

    AST::GSTypePtr _type;

    AST::GSExpressionPtr _expression;
};

class TableOfSymbols {
public:

    explicit TableOfSymbols(SymbolPtrArray symbols)
            : _symbols(std::move(symbols)) {}

public:

    static SharedPtr<TableOfSymbols> Create(SymbolPtrArray symbols) {
        return std::make_shared<TableOfSymbols>(std::move(symbols));
    }

    static SharedPtr<TableOfSymbols> Create() {
        return TableOfSymbols::Create(SymbolPtrArray());
    }

public:

    Void AddSymbol(SymbolPtr symbol) {
        _symbols.emplace_back(std::move(symbol));
    }

    Void AddFunction(UString name, AST::GSStatementPtrArray body) {
        AddSymbol(FunctionSymbol::Create(std::move(name), std::move(body)));
    }

    Void AddVariable(UString name, AST::GSTypePtr type, AST::GSExpressionPtr expression) {
        AddSymbol(VariableSymbol::Create(std::move(name), std::move(type), std::move(expression)));
    }

    Void AddStructure(UString name, Vector<StructureMethod> methods, Vector<StructureField> fields) {
        AddSymbol(StructureSymbol::Create(std::move(name), std::move(methods), std::move(fields)));
    }

    SharedPtr<FunctionSymbol> GetFunction(UString name) {
        for (auto &symbol : _symbols) {
            if (symbol->IsFunction()) {
                auto functionSymbol = std::reinterpret_pointer_cast<FunctionSymbol>(symbol);

                if (functionSymbol->GetName() == name) {
                    return functionSymbol;
                }
            }
        }

        return nullptr;
    }

    SharedPtr<VariableSymbol> GetVariable(UString name) {
        for (auto &symbol : _symbols) {
            if (symbol->IsVariable()) {
                auto variableSymbol = std::reinterpret_pointer_cast<VariableSymbol>(symbol);

                if (variableSymbol->GetName() == name) {
                    return variableSymbol;
                }
            }
        }

        return nullptr;
    }

    SharedPtr<StructureSymbol> GetStructure(UString name) {
        for (auto &symbol : _symbols) {
            if (symbol->IsStructure()) {
                auto structureSymbol = std::reinterpret_pointer_cast<StructureSymbol>(symbol);

                if (structureSymbol->GetName() == name) {
                    return structureSymbol;
                }
            }
        }

        return nullptr;
    }

private:

    SymbolPtrArray _symbols;
};

using TableOfSymbolsPtr = SharedPtr<TableOfSymbols>;

class SymbolsPlaceholderVisitor : public AST::GS_Visitor {
public:

    explicit SymbolsPlaceholderVisitor(LRef<TableOfSymbolsPtr> tableOfSymbols)
            : _tableOfSymbols(tableOfSymbols) {}

public:

    Void VisitFunctionDeclaration(LRef<SharedPtr<AST::GS_FunctionDeclaration>> functionDeclaration) override {
        AST::GS_Visitor::VisitFunctionDeclaration(functionDeclaration);

        auto name = functionDeclaration->GetName();
        auto body = functionDeclaration->GetBody();

        _tableOfSymbols->AddFunction(name, body);
    }

    Void VisitVariableDeclarationStatement(LRef<SharedPtr<AST::GS_VariableDeclarationStatement>> variableDeclarationStatement) override {
        AST::GS_Visitor::VisitVariableDeclarationStatement(variableDeclarationStatement);

        auto name = variableDeclarationStatement->GetName();
        auto type = variableDeclarationStatement->GetType();
        auto expression = variableDeclarationStatement->GetExpression();

        _tableOfSymbols->AddVariable(name, type, expression);
    }

private:

    LRef<TableOfSymbolsPtr> _tableOfSymbols;
};

Void Func() {
    auto Builder = AST::GS_ASTBuilder::Create();

    auto TOS = TableOfSymbols::Create();

    auto Console = StructureSymbol::Create(
            "Console",
            {
                StructureMethod::Create("Print", {
                    AST::ToStatement(Builder->CreateConstantExpression(0))
                }),

                StructureMethod::Create("Input", {
                    AST::ToStatement(Builder->CreateConstantExpression(1))
                })
            },
            {

            });

    auto program = CreateProgram();

    auto PM = AST::GS_PassManager::Create();

    PM->AddPass(CreatePrintPass());

    PM->AddPass(CreateTypeCheckPass());

    PM->AddPass(CreatePrintPass());

    PM->AddPass(CreateManglePass(GS_ABI::Create()->GetMangler()));

    PM->AddPass(CreatePrintPass());

    PM->Run(program);

    auto Optimizer = Optimizer::GS_Optimizer::Create();

    Optimizer->Optimize(program);

    auto CG = CodeGenerator::GS_CodeGenerator::CreateLLVMCG();

    CG->Generate(program);

    auto context = CG->GetContext();

    PrintModule(context);
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
