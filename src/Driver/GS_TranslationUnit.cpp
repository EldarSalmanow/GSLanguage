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
#include <Debug/Debug.h>

#include <GS_TranslationUnit.h>

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

        Debug::DumpAST(unit);

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
        // TODO update

        auto Optimizer = Optimizer::GS_Optimizer::Create();

        Optimizer->Optimize(translationUnitDeclaration);

        return true;
    }

    Bool GS_TranslationUnit::RunBackEnd(LRef<SharedPtr<AST::GS_TranslationUnitDeclaration>> translationUnitDeclaration) {
        // TODO update

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
