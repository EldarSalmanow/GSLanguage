#include <LLVM/GS_LLVMCompilerUnit.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_LLVMCompilerUnit::GS_LLVMCompilerUnit()
            : _context(std::make_shared<llvm::LLVMContext>()), _module(nullptr) {};

    Void GS_LLVMCompilerUnit::createModule(UString name) {
        _module = std::make_shared<llvm::Module>(name.asString(), *_context);
    }

    Bool GS_LLVMCompilerUnit::hasModule() {
        return _module != nullptr;
    }

    LRef<llvm::LLVMContext> GS_LLVMCompilerUnit::getContext() {
        return *_context;
    }

    LRef<llvm::Module> GS_LLVMCompilerUnit::getModule() {
        return *_module;
    }

}
