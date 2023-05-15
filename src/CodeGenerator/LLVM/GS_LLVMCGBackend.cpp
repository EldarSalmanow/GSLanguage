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

    GS_LLVMCGBackend::GS_LLVMCGBackend() = default;

    std::shared_ptr<GS_LLVMCGBackend> GS_LLVMCGBackend::Create() {
        return std::make_shared<GS_LLVMCGBackend>();
    }

    GSCodeHolderPtr GS_LLVMCGBackend::Generate(LRef<Driver::GS_Session> session,
                                               AST::GSTranslationUnitDeclarationPtr unit) {
        auto codeHolder = GS_LLVMCodeHolder::Create();

        GS_LLVMCGVisitor visitor(*codeHolder);

        visitor.GenerateTranslationUnitDeclaration(session,
                                                   unit);

        return codeHolder;
    }

    CGBackendType GS_LLVMCGBackend::GetBackendType() const {
        return CGBackendType::LLVM;
    }

}
