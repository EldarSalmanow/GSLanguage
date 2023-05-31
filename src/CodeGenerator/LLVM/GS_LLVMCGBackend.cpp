#include <llvm/IR/LegacyPassManager.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>

#include <LLVM/GS_LLVMCGBackend.h>

#include <LLVM/GS_LLVMCGVisitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_LLVMCodeHolder::GS_LLVMCodeHolder()
            : _context(std::make_unique<llvm::LLVMContext>()),
              _module(nullptr) {}

    std::shared_ptr<GS_LLVMCodeHolder> GS_LLVMCodeHolder::Create() {
        return std::make_shared<GS_LLVMCodeHolder>();
    }

    LRef<llvm::Module> GS_LLVMCodeHolder::CreateModule(UString moduleName) {
        auto movedModuleName = std::move(moduleName);

        DestroyModule();

        _module = std::make_unique<llvm::Module>(movedModuleName.AsUTF8(),
                                                 GetContext());

        return GetModule();
    }

    Void GS_LLVMCodeHolder::DestroyModule() {
        _module = nullptr;
    }

    LRef<llvm::LLVMContext> GS_LLVMCodeHolder::GetContext() {
        return *_context;
    }

    LRef<llvm::Module> GS_LLVMCodeHolder::GetModule() {
        return *_module;
    }

    CGBackendType GS_LLVMCodeHolder::GetBackendType() const {
        return CGBackendType::LLVM;
    }

    GS_LLVMCodeGenerator::GS_LLVMCodeGenerator() = default;

    std::shared_ptr<GS_LLVMCodeGenerator> GS_LLVMCodeGenerator::Create() {
        return std::make_shared<GS_LLVMCodeGenerator>();
    }

    GSCodeHolderPtr GS_LLVMCodeGenerator::Generate(LRef<Driver::GS_Session> session,
                                                   AST::GSTranslationUnitDeclarationPtr unit) {
        auto codeHolder = GS_LLVMCodeHolder::Create();

        GS_LLVMCGVisitor visitor(*codeHolder);

        visitor.GenerateTranslationUnitDeclaration(session,
                                                   unit);

        return codeHolder;
    }

    CGBackendType GS_LLVMCodeGenerator::GetBackendType() const {
        return CGBackendType::LLVM;
    }

    GS_LLVMCodeWriter::GS_LLVMCodeWriter() = default;

    std::shared_ptr<GS_LLVMCodeWriter> GS_LLVMCodeWriter::Create() {
        return std::make_shared<GS_LLVMCodeWriter>();
    }

    Void GS_LLVMCodeWriter::Write(LRef<Driver::GS_Session> session,
                                  UString fileName,
                                  GSCodeHolderPtr codeHolder) {
        auto llvmCodeHolder = std::reinterpret_pointer_cast<GS_LLVMCodeHolder>(codeHolder);

        auto &llvmModule = llvmCodeHolder->GetModule();

        llvm::InitializeAllTargetInfos();
        llvm::InitializeAllTargets();
        llvm::InitializeAllTargetMCs();
        llvm::InitializeAllAsmParsers();
        llvm::InitializeAllAsmPrinters();

        auto targetTriple = llvm::sys::getDefaultTargetTriple();
        llvmModule.setTargetTriple(targetTriple);

        std::string error;
        auto target = llvm::TargetRegistry::lookupTarget(targetTriple,
                                                         error);

//        if (!target) {
//            llvm::errs() << error;
//
//            return;
//        }

        auto cpu = "generic";
        auto features = "";

        llvm::TargetOptions targetOptions;
        auto relocModel = std::optional<llvm::Reloc::Model>();
        auto targetMachine = target->createTargetMachine(targetTriple,
                                                         cpu,
                                                         features,
                                                         targetOptions,
                                                         relocModel);

        llvmModule.setDataLayout(targetMachine->createDataLayout());

        std::error_code errorCode;
        llvm::raw_fd_ostream output(fileName.AsUTF8(),
                                    errorCode,
                                    llvm::sys::fs::OF_None);

//        if (errorCode) {
//            llvm::errs() << "Could not open file: " << errorCode.message();
//
//            return;
//        }

        llvm::legacy::PassManager passManager;
        auto fileType = llvm::CGFT_ObjectFile;

        targetMachine->addPassesToEmitFile(passManager,
                                           output,
                                           nullptr,
                                           fileType);

//        if (targetMachine->addPassesToEmitFile(passManager,
//                                               output,
//                                               nullptr,
//                                               fileType)) {
//            llvm::errs() << "TheTargetMachine can't emit a file of this type";
//
//            return;
//        }

        passManager.run(llvmModule);
        output.flush();
    }

    CGBackendType GS_LLVMCodeWriter::GetBackendType() const {
        return CGBackendType::LLVM;
    }

    GS_LLVMCGBackend::GS_LLVMCGBackend() = default;

    std::shared_ptr<GS_LLVMCGBackend> GS_LLVMCGBackend::Create() {
        return std::make_shared<GS_LLVMCGBackend>();
    }

    GSCodeGeneratorPtr GS_LLVMCGBackend::GetCodeGenerator() {
        return GS_LLVMCodeGenerator::Create();
    }

    GSCodeWriterPtr GS_LLVMCGBackend::GetCodeWriter() {
        return GS_LLVMCodeWriter::Create();
    }

    CGBackendType GS_LLVMCGBackend::GetBackendType() const {
        return CGBackendType::LLVM;
    }

}
