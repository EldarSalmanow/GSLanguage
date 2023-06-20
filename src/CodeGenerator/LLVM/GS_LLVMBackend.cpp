#include <llvm/IR/LegacyPassManager.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>

#include <lld/Common/Driver.h>

#include <LLVM/GS_LLVMBackend.h>

#include <LLVM/GS_LLVMVisitor.h>

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

    BackendType GS_LLVMCodeHolder::GetBackendType() const {
        return BackendType::LLVM;
    }

    GS_LLVMBackend::GS_LLVMBackend() = default;

    std::shared_ptr<GS_LLVMBackend> GS_LLVMBackend::Create() {
        return std::make_shared<GS_LLVMBackend>();
    }

    GSCodeHolderPtr GS_LLVMBackend::Generate(LRef<Driver::GS_Session> session,
                                             AST::GSNodePtr node) {
        auto codeHolder = GS_LLVMCodeHolder::Create();

        GS_LLVMVisitor visitor(*codeHolder);

        visitor.GenerateNode(session,
                             node);

        return codeHolder;
    }

    Void GS_LLVMBackend::Write(LRef<Driver::GS_Session> session,
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
        auto relocModel = llvm::Optional<llvm::Reloc::Model>();
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

    Void GS_LLVMBackend::Link(LRef<Driver::GS_Session> session,
                              std::vector<UString> inputFileNames,
                              UString outputFileName) {
        std::vector<std::string> command;

        command.emplace_back("GSLanguage.exe");

        for (auto &inputFile : inputFileNames) {
            command.emplace_back(inputFile.AsUTF8());
        }

        command.emplace_back("/entry:main");
        command.emplace_back("/out:" + outputFileName.AsUTF8());

        std::vector<ConstPtr<C>> stringCommand;

        for (auto &string : command) {
            stringCommand.emplace_back(string.c_str());
        }

        auto linkResult = lld::coff::link(stringCommand,
                                          llvm::outs(),
                                          llvm::errs(),
                                          false,
                                          false);
    }

    BackendType GS_LLVMBackend::GetBackendType() const {
        return BackendType::LLVM;
    }

}
