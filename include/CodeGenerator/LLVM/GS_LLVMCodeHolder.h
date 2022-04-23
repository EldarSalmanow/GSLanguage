#ifndef GSLANGUAGE_GS_LLVMCODEHOLDER_H
#define GSLANGUAGE_GS_LLVMCODEHOLDER_H

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include <CodeGenerator/GS_CodeHolder.h>

namespace GSLanguageCompiler::CodeGenerator {

    class GS_LLVMCodeHolder : public GS_CodeHolder {
    public:

        GS_LLVMCodeHolder();

    public:

        Void CreateModule(UString name);

        Void DestroyModule();

    public:

        LRef<llvm::LLVMContext> GetContext();

        LRef<llvm::Module> GetModule();

    private:

        UniquePtr<llvm::LLVMContext> _context;

        UniquePtr<llvm::Module> _module;
    };

}

#endif //GSLANGUAGE_GS_LLVMCODEHOLDER_H
