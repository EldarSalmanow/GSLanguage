#ifndef GSLANGUAGE_GS_LLVMCODEGENERATIONVISITORCONTEXT_H
#define GSLANGUAGE_GS_LLVMCODEGENERATIONVISITORCONTEXT_H

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include <CodeGenerator/GS_CodeGenerationVisitorContext.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     *
     */
    class GS_LLVMCodeGenerationVisitorContext : public GS_CodeGenerationVisitorContext {
    public:

        /**
         *
         */
        GS_LLVMCodeGenerationVisitorContext();

    public:

        /**
         *
         * @param name
         * @return
         */
        Void createModule(UString name);

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

#endif //GSLANGUAGE_GS_LLVMCODEGENERATIONVISITORCONTEXT_H
