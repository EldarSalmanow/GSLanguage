//#include <rapidjson/document.h>

#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/raw_ostream.h>

#include <Reader/Reader.h>
#include <Lexer/Lexer.h>
#include <Parser/Parser.h>
#include <AST/AST.h>
#include <CodeGenerator/CodeGenerator.h>

#include <GS_TranslationUnit.h>

namespace GSLanguageCompiler::Driver {

//    class CFVisitor : public AST::GS_Visitor<AST::GSNodePtr> {
//    public:
//
//        AST::GSNodePtr visitUnaryExpression(SharedPtr<AST::GS_UnaryExpression> unaryExpression) override {
//            unaryExpression = std::reinterpret_pointer_cast<AST::GS_UnaryExpression>(AST::GS_Visitor<AST::GSNodePtr>::visitUnaryExpression(unaryExpression));
//
//            auto expression = unaryExpression->getExpression();
//            auto operation = unaryExpression->getUnaryOperation();
//            auto scope = unaryExpression->getScope();
//
//            if (IsConstantExpression(expression)) {
//                auto value = std::reinterpret_pointer_cast<AST::GS_ConstantExpression>(expression)->getValue();
//
//                auto result = Fold(value, operation);
//
//                if (result != nullptr) {
//                    auto newExpression = AST::GS_ConstantExpression::Create(result, scope);
//
//                    scope->replaceNode(unaryExpression, newExpression);
//
//                    return newExpression;
//                }
//            }
//
//            return unaryExpression;
//        }
//
//        AST::GSNodePtr visitBinaryExpression(SharedPtr<AST::GS_BinaryExpression> binaryExpression) override {
//            binaryExpression = std::reinterpret_pointer_cast<AST::GS_BinaryExpression>(AST::GS_Visitor<AST::GSNodePtr>::visitBinaryExpression(binaryExpression));
//
//            auto firstExpression = binaryExpression->getFirstExpression();
//            auto secondExpression = binaryExpression->getSecondExpression();
//            auto operation = binaryExpression->getBinaryOperation();
//            auto &scope = binaryExpression->getScope();
//
//            if (IsConstantExpression(firstExpression) && IsConstantExpression(secondExpression)) {
//                auto firstValue = std::reinterpret_pointer_cast<AST::GS_ConstantExpression>(firstExpression)->getValue();
//                auto secondValue = std::reinterpret_pointer_cast<AST::GS_ConstantExpression>(secondExpression)->getValue();
//
//                auto result = Fold(firstValue, secondValue, operation);
//
//                if (result != nullptr) {
//                    auto newExpression = AST::GS_ConstantExpression::Create(result, scope);
//
//                    scope->replaceNode(binaryExpression, newExpression);
//
//                    return newExpression;
//                }
//            }
//
//            return binaryExpression;
//        }
//
//    private:
//
//        AST::GSValuePtr Fold(ConstLRef<AST::GSValuePtr> value, AST::UnaryOperation operation) {
//            if (value->getType()->getName() == U"I32") {
//                auto number = value->getValueWithCast<I32>();
//
//                switch (operation) {
//                    case AST::UnaryOperation::Minus:
//                        number = -number;
//
//                        break;
//                    default:
//                        return nullptr;
//                }
//
//                return AST::GS_I32Value::Create(number);
//            }
//
//            return nullptr;
//        }
//
//        AST::GSValuePtr Fold(ConstLRef<AST::GSValuePtr> firstValue, ConstLRef<AST::GSValuePtr> secondValue, AST::BinaryOperation operation) {
//            if (firstValue->getType()->getName() == U"I32" && secondValue->getType()->getName() == U"I32") {
//                auto firstNumber = firstValue->getValueWithCast<I32>();
//                auto secondNumber = secondValue->getValueWithCast<I32>();
//
//                I32 result = 0;
//
//                switch (operation) {
//                    case AST::BinaryOperation::Plus:
//                        result = firstNumber + secondNumber;
//
//                        break;
//                    case AST::BinaryOperation::Minus:
//                        result = firstNumber - secondNumber;
//
//                        break;
//                    case AST::BinaryOperation::Star:
//                        result = firstNumber * secondNumber;
//
//                        break;
//                    case AST::BinaryOperation::Slash:
//                        result = firstNumber / secondNumber;
//
//                        break;
//                    default:
//                        return nullptr;
//                }
//
//                return AST::GS_I32Value::Create(result);
//            }
//
//            return nullptr;
//        }
//
//        Bool IsConstantExpression(ConstLRef<AST::GSNodePtr> node) {
//            if (auto expression = AST::ToExpression(node)) {
//                if (expression->getExpressionType() == AST::ExpressionType::ConstantExpression) {
//                    return true;
//                }
//
//                return false;
//            }
//
//            return false;
//        }
//    };

    class PrintVisitor : public AST::GS_Visitor<Void> {
    public:

        Void visitTranslationUnitDeclaration(
                SharedPtr<AST::GS_TranslationUnitDeclaration> translationUnitDeclaration) override {
            Print("TranslationUnitDeclaration: {");

            AddTab();

            Print("Nodes: {");

            AddTab();

            for (auto &node: translationUnitDeclaration->getNodes()) {
                visitNode(node);
            }

            SubTab();

            Print("}");

            SubTab();

            Print("}");
        }

        Void visitFunctionDeclaration(SharedPtr<AST::GS_FunctionDeclaration> functionDeclaration) override {
            Print("FunctionDeclaration: {");

            AddTab();

            Print("Name: " + functionDeclaration->getName().AsString());

            Print("Body: {");

            AddTab();

            for (auto &statement: functionDeclaration->getBody()) {
                visitStatement(statement);
            }

            SubTab();

            Print("}");

            SubTab();

            Print("}");
        }

        Void visitVariableDeclarationStatement(
                SharedPtr<AST::GS_VariableDeclarationStatement> variableDeclarationStatement) override {
            Print("VariableDeclarationStatement: {");

            AddTab();

            Print("Name: " + variableDeclarationStatement->getName().AsString());

            Print("Type: " + variableDeclarationStatement->getType()->getName().AsString());

            Print("Expression: {");

            AddTab();

            visitExpression(variableDeclarationStatement->getExpression());

            SubTab();

            Print("}");

            SubTab();

            Print("}");
        }

        Void visitAssignmentStatement(SharedPtr<AST::GS_AssignmentStatement> assignmentStatement) override {
            Print("AssignmentStatement: {");

            AddTab();

            Print("LValueExpression: {");

            AddTab();

            visitExpression(assignmentStatement->getLValueExpression());

            SubTab();

            Print("}");

            Print("RValueExpression: {");

            AddTab();

            visitExpression(assignmentStatement->getRValueExpression());

            SubTab();

            Print("}");

            SubTab();

            Print("}");
        }

        Void visitExpressionStatement(SharedPtr<AST::GS_ExpressionStatement> expressionStatement) override {
            Print("ExpressionStatement: {");

            AddTab();

            visitExpression(expressionStatement->getExpression());

            SubTab();

            Print("}");
        }

        Void visitConstantExpression(SharedPtr<AST::GS_ConstantExpression> constantExpression) override {
            Print("ConstantExpression: {");

            AddTab();

            Print("Value: {");

            AddTab();

            auto value = constantExpression->getValue();
            auto typeName = value->getType()->getName();

            Print("Type: " + typeName.AsString());

            if (typeName == U"I32") {
                Print("Value: " + std::to_string(value->getValueWithCast<I32>()));
            } else if (typeName == U"String") {
                Print("Value: " + value->getValueWithCast<UString>().AsString());
            }

            SubTab();

            Print("}");

            SubTab();

            Print("}");
        }

        Void visitUnaryExpression(SharedPtr<AST::GS_UnaryExpression> unaryExpression) override {
            Print("UnaryExpression: {");

            AddTab();

            Print("Expression: {");

            AddTab();

            visitExpression(unaryExpression->getExpression());

            SubTab();

            Print("}");

            auto operation = unaryExpression->getUnaryOperation();

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

        Void visitBinaryExpression(SharedPtr<AST::GS_BinaryExpression> binaryExpression) override {
            Print("BinaryExpression: {");

            AddTab();

            Print("FirstExpression: {");

            AddTab();

            visitExpression(binaryExpression->getFirstExpression());

            SubTab();

            Print("}");

            Print("SecondExpression: {");

            AddTab();

            visitExpression(binaryExpression->getSecondExpression());

            SubTab();

            Print("}");

            auto operation = binaryExpression->getBinaryOperation();

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

        Void visitVariableUsingExpression(SharedPtr<AST::GS_VariableUsingExpression> variableUsingExpression) override {
            Print("VariableUsingExpression: {");

            AddTab();

            Print("Name: " + variableUsingExpression->getName().AsString());

            SubTab();

            Print("}");
        }

        Void visitFunctionCallingExpression(
                SharedPtr<AST::GS_FunctionCallingExpression> functionCallingExpression) override {
            Print("FunctionCallingExpression: {");

            AddTab();

            Print("Name: " + functionCallingExpression->getName().AsString());

            Print("Params: {");

            AddTab();

            for (auto &param: functionCallingExpression->getParams()) {
                visitExpression(param);
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

    GS_TranslationUnit::GS_TranslationUnit(UString inputName, UString outputName)
            : _inputName(std::move(inputName)), _outputName(std::move(outputName)) {}

    SharedPtr<GS_TranslationUnit> GS_TranslationUnit::Create(UString inputName, UString outputName) {
        return std::make_shared<GS_TranslationUnit>(std::move(inputName), std::move(outputName));
    }

    I32 GS_TranslationUnit::Compile() {
        auto file = File::Create(_inputName, InMode);

        Reader::GS_Reader reader(file);

        Reader::GS_TextStream textStream(reader);

        Lexer::GS_Lexer lexer(textStream);

        Lexer::GS_TokenStream tokenStream(lexer);

        Parser::GS_Parser parser(tokenStream);

        auto unit = parser.Parse();

        auto printer = std::make_shared<PrintVisitor>();

        printer->visitNode(unit);

        auto codeGen = std::make_shared<CodeGenerator::GS_LLVMCodeGenerationVisitor>();

        codeGen->visitTranslationUnitDeclaration(unit);

        auto &module = std::reinterpret_pointer_cast<CodeGenerator::GS_LLVMCodeGenerationVisitorContext>(
                codeGen->getContext())->getModule();

        module.print(llvm::errs(), nullptr);

        auto targetTriple = llvm::sys::getDefaultTargetTriple();

        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmParser();
        llvm::InitializeNativeTargetAsmPrinter();

        String error;

        auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);

        if (!target) {
            llvm::errs() << error;

            return 1;
        }

        auto cpu = "generic";
        auto features = "";

        llvm::TargetOptions options;

        auto model = llvm::Optional<llvm::Reloc::Model>();

        auto machine = target->createTargetMachine(targetTriple, cpu, features, options, model);

        module.setDataLayout(machine->createDataLayout());
        module.setTargetTriple(targetTriple);

        std::error_code errorCode;

        llvm::raw_fd_ostream stream(_outputName.AsString(), errorCode);

        if (errorCode) {
            llvm::errs() << errorCode.message();

            return 1;
        }

        llvm::legacy::PassManager manager;

        if (machine->addPassesToEmitFile(manager, stream, nullptr, llvm::CodeGenFileType::CGFT_ObjectFile)) {
            return 1;
        }

        manager.run(module);

        stream.flush();

        return 0;
    }

    UString GS_TranslationUnit::GetInputName() const {
        return _inputName;
    }

    UString GS_TranslationUnit::GetOutputName() const {
        return _outputName;
    }

}
