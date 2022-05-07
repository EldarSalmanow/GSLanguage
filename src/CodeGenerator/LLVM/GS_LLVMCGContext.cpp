#include <LLVM/GS_LLVMCGContext.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_LLVMCGContext::GS_LLVMCGContext()
            : _context(std::make_unique<llvm::LLVMContext>()) {}

    GS_LLVMCGContext::~GS_LLVMCGContext() = default;

    SharedPtr<GS_LLVMCGContext> GS_LLVMCGContext::Create() {
        return std::make_shared<GS_LLVMCGContext>();
    }

    Void GS_LLVMCGContext::CreateModule(UString name) {
        DestroyModule();

        _module = std::make_unique<llvm::Module>(name.AsString(), *_context);
    }

    Void GS_LLVMCGContext::DestroyModule() {
        _module.reset();
    }

    LRef<llvm::LLVMContext> GS_LLVMCGContext::GetContext() {
        return *_context;
    }

    LRef<llvm::Module> GS_LLVMCGContext::GetModule() {
        return *_module;
    }

    CGBackend GS_LLVMCGContext::GetBackend() {
        return CGBackend::LLVM;
    }

}
