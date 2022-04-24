#ifndef GSLANGUAGE_GS_CGPASS_H
#define GSLANGUAGE_GS_CGPASS_H

#include <AST/GS_Pass.h>

#include <CodeGenerator/GS_CGContext.h>

#include <CodeGenerator/LLVM/GS_LLVMCGContext.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     * Code generation backend
     */
    enum class CGBackend {
        LLVM
    };

    /**
     * Code generation pass
     */
    class GS_CGPass : public AST::GS_Pass {
    public:

        /**
         * Constructor for code generation pass
         * @param backend Code generation backend
         * @param context Code generation context
         */
        GS_CGPass(CGBackend backend, LRef<GSCGContextPtr> context);

    public:

        /**
         * Run code generation pass
         * @param translationUnitDeclaration Translation unit declaration
         * @return
         */
        Void Run(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration) override;

    private:

        /**
         * Code generation backend
         */
        CGBackend _backend;

        /**
         * Code generation context
         */
        LRef<GSCGContextPtr> _context;
    };

    /**
     * Create code generation pass
     * @param backend Code generation backend
     * @param context Code generation context
     * @return AST pass ptr
     */
    AST::GSPassPtr CreateCGPass(CGBackend backend, LRef<GSCGContextPtr> context);

}

#endif //GSLANGUAGE_GS_CGPASS_H
