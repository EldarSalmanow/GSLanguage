#ifndef GSLANGUAGE_GS_LLVMCOMPILERUNIT_H
#define GSLANGUAGE_GS_LLVMCOMPILERUNIT_H

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include <CodeGenerator/GS_CompilerUnit.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     *
     */
    class GS_LLVMCompilerUnit : public GS_CompilerUnit {
    public:

        /**
         *
         */
        GS_LLVMCompilerUnit();

    public:

        /**
         *
         * @param name
         * @return
         */
        Void createModule(UString name);

        /**
         *
         * @return
         */
        Bool hasModule();

    public:

        /**
         *
         */
        LRef<llvm::LLVMContext> getContext();

        /**
         *
         * @return
         */
        LRef<llvm::Module> getModule();

    private:

        /**
         *
         */
        SharedPtr<llvm::LLVMContext> _context;

        /**
         *
         */
        SharedPtr<llvm::Module> _module;
    };

}

#endif //GSLANGUAGE_GS_LLVMCOMPILERUNIT_H
