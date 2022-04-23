#include <LLVM/GS_LLVMCodeHolder.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_LLVMCodeHolder::GS_LLVMCodeHolder()
            : _context(std::make_unique<llvm::LLVMContext>()), _module(nullptr) {}

    Void GS_LLVMCodeHolder::CreateModule(UString name) {
        DestroyModule();

        _module = std::make_unique<llvm::Module>(name.AsString(), *_context);
    }

    Void GS_LLVMCodeHolder::DestroyModule() {
        if (_module == nullptr) {
            _module.reset();
        }
    }

    LRef<llvm::LLVMContext> GS_LLVMCodeHolder::GetContext() {
        return *_context;
    }

    LRef<llvm::Module> GS_LLVMCodeHolder::GetModule() {
        return *_module;
    }

}
