//#include <rapidjson/document.h>

#include <llvm/IR/LegacyPassManager.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#include <Reader/Reader.h>
#include <Lexer/Lexer.h>
//#include <Parser/Parser.h>
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

    GS_TranslationUnit::GS_TranslationUnit(GSTranslationUnitConfigPtr config)
            : _config(std::move(config)) {}

    SharedPtr<GS_TranslationUnit> GS_TranslationUnit::Create(GSTranslationUnitConfigPtr config) {
        return std::make_shared<GS_TranslationUnit>(std::move(config));
    }

    CompilingResult GS_TranslationUnit::Compile() {
        auto unit = RunFrontend(_config->GetInputName());

        auto codeGen = std::make_shared<CodeGenerator::GS_LLVMCodeGenerationVisitor>();

        codeGen->GenerateTranslationUnitDeclaration(unit);

        auto &module = codeGen->GetModule();

        module.print(llvm::errs(), nullptr);

        auto targetTriple = llvm::sys::getDefaultTargetTriple();

        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmParser();
        llvm::InitializeNativeTargetAsmPrinter();

        String error;

        auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);

        if (!target) {
            llvm::errs() << error;

            return CompilingResult::Failure;
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

            return CompilingResult::Failure;
        }

        llvm::legacy::PassManager manager;

        if (machine->addPassesToEmitFile(manager, stream, nullptr, llvm::CodeGenFileType::CGFT_ObjectFile)) {
            return CompilingResult::Failure;
        }

        manager.run(module);

        stream.flush();

        return CompilingResult::Success;
    }

    SharedPtr<AST::GS_TranslationUnitDeclaration> GS_TranslationUnit::RunFrontend(UString inputFile) {
//        auto file = File::Create(inputFile, InMode);
//
//        Reader::GS_Reader reader(file);
//
//        Reader::GS_TextStream textStream(reader);
//
//        Lexer::GS_Lexer lexer(textStream);
//
//        Lexer::GS_TokenStream tokenStream(lexer);
//
//        Parser::GS_Parser parser(tokenStream);
//
//        auto unit = parser.Parse();
//
//        return unit;

        return nullptr;
    }

    GSTranslationUnitConfigPtr GS_TranslationUnit::GetConfig() const {
        return _config;
    }

}
