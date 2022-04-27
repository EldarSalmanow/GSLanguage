#ifndef GSLANGUAGE_GS_LLVMCGPASS_H
#define GSLANGUAGE_GS_LLVMCGPASS_H

#include <CodeGenerator/GS_CGPass.h>

#include <CodeGenerator/LLVM/GS_LLVMCGContext.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     * LLVM code generation pass
     */
    class GS_LLVMCGPass : public GS_CGPass {
    public:

        /**
         * Constructor for LLVM code generation pass
         * @param context LLVM code generation context
         */
        explicit GS_LLVMCGPass(LRef<GSLLVMCGContextPtr> context);

    public:

        /**
         * Run LLVM code generation pass
         * @param translationUnitDeclaration Translation unit declaration
         * @return
         */
        Void Run(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration) override;

    private:

        /**
         * LLVM code generation context
         */
        LRef<GSLLVMCGContextPtr> _context;
    };

    /**
     * Creating LLVM code generation pass
     * @param context LLVM code generation context
     * @return LLVM code generation pass
     */
    AST::GSPassPtr CreateLLVMCGPass(LRef<GSLLVMCGContextPtr> context);

}

#endif //GSLANGUAGE_GS_LLVMCGPASS_H
