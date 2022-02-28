#ifndef GSLANGUAGE_GS_LLVMTRANSLATIONMODULE_H
#define GSLANGUAGE_GS_LLVMTRANSLATIONMODULE_H

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include <CodeGenerator/GS_TranslationModule.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     *
     */
    class GS_LLVMTranslationModule : public GS_TranslationModule {
    public:

        /**
         *
         */
        GS_LLVMTranslationModule();

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

#endif //GSLANGUAGE_GS_LLVMTRANSLATIONMODULE_H
