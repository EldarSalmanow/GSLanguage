#include <LLVM/GS_LLVMTranslationModule.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_LLVMTranslationModule::GS_LLVMTranslationModule()
            : _context(std::make_shared<llvm::LLVMContext>()), _module(nullptr) {};

    Void GS_LLVMTranslationModule::createModule(UString name) {
        _module = std::make_shared<llvm::Module>(name.asString(), *_context);
    }

    Bool GS_LLVMTranslationModule::hasModule() {
        return _module != nullptr;
    }

    LRef<llvm::LLVMContext> GS_LLVMTranslationModule::getContext() {
        return *_context;
    }

    LRef<llvm::Module> GS_LLVMTranslationModule::getModule() {
        return *_module;
    }

}
