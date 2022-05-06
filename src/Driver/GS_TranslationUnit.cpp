#include <llvm/IR/LegacyPassManager.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#include <Reader/Reader.h>
#include <Lexer/Lexer.h>
#include <Parser/Parser.h>
#include <AST/AST.h>
#include <Optimizer/Optimizer.h>
#include <Semantic/Semantic.h>
#include <CodeGenerator/CodeGenerator.h>

#include <GS_TranslationUnit.h>

class PrintVisitor : public GSLanguageCompiler::AST::GS_Visitor {
public:

    Void VisitTranslationUnitDeclaration(LRef<SharedPtr<GSLanguageCompiler::AST::GS_TranslationUnitDeclaration>> translationUnitDeclaration) override {
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

    Void VisitFunctionDeclaration(LRef<SharedPtr<GSLanguageCompiler::AST::GS_FunctionDeclaration>> functionDeclaration) override {
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

    Void VisitVariableDeclarationStatement(LRef<SharedPtr<GSLanguageCompiler::AST::GS_VariableDeclarationStatement>> variableDeclarationStatement) override {
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

    Void VisitAssignmentStatement(LRef<SharedPtr<GSLanguageCompiler::AST::GS_AssignmentStatement>> assignmentStatement) override {
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

    Void VisitExpressionStatement(LRef<SharedPtr<GSLanguageCompiler::AST::GS_ExpressionStatement>> expressionStatement) override {
        Print("ExpressionStatement: {"_us);

        AddTab();

        VisitExpression(expressionStatement->GetExpression());

        SubTab();

        Print("}"_us);
    }

    Void VisitConstantExpression(LRef<SharedPtr<GSLanguageCompiler::AST::GS_ConstantExpression>> constantExpression) override {
        Print("ConstantExpression: {"_us);

        AddTab();

        Print("Value: {"_us);

        AddTab();

        auto value = GSLanguageCompiler::AST::GSValueCast<GSLanguageCompiler::AST::GS_LiteralValue>(constantExpression->GetValue());
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

    Void VisitUnaryExpression(LRef<SharedPtr<GSLanguageCompiler::AST::GS_UnaryExpression>> unaryExpression) override {
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
            case GSLanguageCompiler::AST::UnaryOperation::Minus:
                stringOperation = "Minus (-)"_us;

                break;
        }

        Print("Operation: "_us + stringOperation);

        SubTab();

        Print("}"_us);
    }

    Void VisitBinaryExpression(LRef<SharedPtr<GSLanguageCompiler::AST::GS_BinaryExpression>> binaryExpression) override {
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
            case GSLanguageCompiler::AST::BinaryOperation::Plus:
                stringOperation = "Plus (+)"_us;

                break;
            case GSLanguageCompiler::AST::BinaryOperation::Minus:
                stringOperation = "Minus (-)"_us;

                break;
            case GSLanguageCompiler::AST::BinaryOperation::Star:
                stringOperation = "Star (*)"_us;

                break;
            case GSLanguageCompiler::AST::BinaryOperation::Slash:
                stringOperation = "Slash (/)"_us;

                break;
        }

        Print("Operation: "_us + stringOperation);

        SubTab();

        Print("}"_us);
    }

    Void VisitVariableUsingExpression(LRef<SharedPtr<GSLanguageCompiler::AST::GS_VariableUsingExpression>> variableUsingExpression) override {
        Print("VariableUsingExpression: {"_us);

        AddTab();

        Print("Name: "_us + variableUsingExpression->GetName());

        SubTab();

        Print("}"_us);
    }

    Void VisitFunctionCallingExpression(LRef<SharedPtr<GSLanguageCompiler::AST::GS_FunctionCallingExpression>> functionCallingExpression) override {
        Print("FunctionCallingExpression: {"_us);

        AddTab();

        Print("Name: "_us + functionCallingExpression->GetName());

        Print("Params: {"_us);

        AddTab();

        for (auto &param : functionCallingExpression->GetParams()) {
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

class Dumper {
public:

    virtual ~Dumper() = default;

public:

    virtual Void Dump() = 0;
};

class ASTDumper : public Dumper {
public:

    explicit ASTDumper(GSLanguageCompiler::AST::GSNodePtr node)
            : _node(std::move(node)) {}

public:

    static SharedPtr<ASTDumper> Create(GSLanguageCompiler::AST::GSNodePtr node) {
        return std::make_shared<ASTDumper>(std::move(node));
    }

public:

    Void Dump() override {
        PrintVisitor visitor;

        visitor.VisitNode(_node);
    }

private:

    GSLanguageCompiler::AST::GSNodePtr _node;
};

class TableOfSymbolsDumper : public Dumper {
public:

    explicit TableOfSymbolsDumper(GSLanguageCompiler::Semantic::GSTableOfSymbolsPtr tableOfSymbols)
            : _tableOfSymbols(std::move(tableOfSymbols)) {}

public:

    static SharedPtr<TableOfSymbolsDumper> Create(GSLanguageCompiler::Semantic::GSTableOfSymbolsPtr tableOfSymbols) {
        return std::make_shared<TableOfSymbolsDumper>(std::move(tableOfSymbols));
    }

public:

    Void Dump() override {
        UCOut() << "---------- Table Of Symbols Dump ----------\n"_us;

        auto functions = _tableOfSymbols->GetFunctions();

        if (!functions.empty()) {
            UCOut() << "----------       Functions       ----------\n"_us;

            for (auto index = 0; index < functions.size(); ++index) {
                auto function = functions[index];

                UCOut() << UString(std::to_string(index + 1)) << ": \n  Name -> "_us << function->GetName() << "\n"_us;
            }
        }

        auto variables = _tableOfSymbols->GetVariables();

        if (!variables.empty()) {
            UCOut() << "----------       Variables       ----------\n"_us;

            for (auto index = 0; index < variables.size(); ++index) {
                auto variable = variables[index];

                UCOut() << UString(std::to_string(index + 1)) << ": \n  Name -> "_us << variable->GetName() << "\n  Type -> " << variable->GetType()->GetName() << "\n"_us;
            }
        }

        UCOut() << "-------------------------------------------\n"_us;
    }

private:

    GSLanguageCompiler::Semantic::GSTableOfSymbolsPtr _tableOfSymbols;
};

namespace Debug {

    Void Dump(GSLanguageCompiler::AST::GSNodePtr node) {
        auto dumper = ASTDumper::Create(std::move(node));

        dumper->Dump();
    }

    Void Dump(GSLanguageCompiler::Semantic::GSTableOfSymbolsPtr tableOfSymbols) {
        auto dumper = TableOfSymbolsDumper::Create(std::move(tableOfSymbols));

        dumper->Dump();
    }

}

namespace GSLanguageCompiler::Driver {

    GS_TranslationUnit::GS_TranslationUnit(GSTranslationUnitConfigPtr config)
            : _config(std::move(config)) {}

    SharedPtr<GS_TranslationUnit> GS_TranslationUnit::Create(GSTranslationUnitConfigPtr config) {
        return std::make_shared<GS_TranslationUnit>(std::move(config));
    }

    CompilingResult GS_TranslationUnit::Compile() {
        auto unit = RunFrontEnd(_config->GetInputName());

        if (!unit) {
            return CompilingResult::Failure;
        }

        Debug::Dump(unit);

//        if (!RunMiddleEnd(unit)) {
//            return CompilingResult::Failure;
//        }
//
//        if (!RunBackEnd(unit)) {
//            return CompilingResult::Failure;
//        }

        return CompilingResult::Success;
    }

    SharedPtr<AST::GS_TranslationUnitDeclaration> GS_TranslationUnit::RunFrontEnd(UString inputFile) {
        auto file = File::Create(inputFile, InMode);

        Reader::GS_Reader reader(file);

        Reader::GS_TextStream textStream(reader);

        Lexer::GS_Lexer lexer(textStream);

        Lexer::GS_TokenStream tokenStream(lexer);

        Parser::GS_Parser parser(tokenStream, AST::GS_ASTContext::Create());

        auto unit = parser.Parse();

        return unit;
    }

    Bool GS_TranslationUnit::RunMiddleEnd(LRef<SharedPtr<AST::GS_TranslationUnitDeclaration>> translationUnitDeclaration) {
        auto Optimizer = Optimizer::GS_Optimizer::Create();

        Optimizer->Optimize(translationUnitDeclaration);

        return true;
    }

    Bool GS_TranslationUnit::RunBackEnd(LRef<SharedPtr<AST::GS_TranslationUnitDeclaration>> translationUnitDeclaration) {
        auto codeGenerator = CodeGenerator::GS_CodeGenerator::CreateLLVMCG();

        codeGenerator->Generate(translationUnitDeclaration);

        auto codeGenerationContext = codeGenerator->GetContext();

        auto llvmCodeGenerationContext = std::reinterpret_pointer_cast<CodeGenerator::GS_LLVMCGContext>(codeGenerationContext);

        auto &module = llvmCodeGenerationContext->GetModule();

        module.print(llvm::errs(), nullptr);

        auto targetTriple = llvm::sys::getDefaultTargetTriple();

        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmParser();
        llvm::InitializeNativeTargetAsmPrinter();

        String error;

        auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);

        if (!target) {
            llvm::errs() << error;

            return false;
        }

        auto cpu = "generic";
        auto features = "";

        llvm::TargetOptions options;

        auto model = llvm::Optional<llvm::Reloc::Model>();

        auto machine = target->createTargetMachine(targetTriple, cpu, features, options, model);

        module.setDataLayout(machine->createDataLayout());
        module.setTargetTriple(targetTriple);

        std::error_code errorCode;

        llvm::raw_fd_ostream stream(_config->GetInputName().AsString() + ".o", errorCode);

        if (errorCode) {
            llvm::errs() << errorCode.message();

            return false;
        }

        llvm::legacy::PassManager manager;

        if (machine->addPassesToEmitFile(manager, stream, nullptr, llvm::CodeGenFileType::CGFT_ObjectFile)) {
            return false;
        }

        manager.run(module);

        stream.flush();

        return true;
    }

    GSTranslationUnitConfigPtr GS_TranslationUnit::GetConfig() const {
        return _config;
    }

}
