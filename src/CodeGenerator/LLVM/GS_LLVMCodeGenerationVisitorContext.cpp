#include <LLVM/GS_LLVMCodeGenerationVisitorContext.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_LLVMCodeGenerationVisitorContext::GS_LLVMCodeGenerationVisitorContext()
            : _context(std::make_shared<llvm::LLVMContext>()), _module(nullptr) {};

    Void GS_LLVMCodeGenerationVisitorContext::createModule(UString name) {
        _module = std::make_shared<llvm::Module>(name.AsString(), getContext());
    }

    LRef<llvm::LLVMContext> GS_LLVMCodeGenerationVisitorContext::getContext() {
        return *_context;
    }

    LRef<llvm::Module> GS_LLVMCodeGenerationVisitorContext::getModule() {
        return *_module;
    }

}
