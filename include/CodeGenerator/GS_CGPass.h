#ifndef GSLANGUAGE_GS_CGPASS_H
#define GSLANGUAGE_GS_CGPASS_H

#include <AST/GS_Pass.h>

#include <CodeGenerator/GS_CodeHolder.h>

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

        explicit GS_CGPass(CGBackend backend, LRef<GSCodeHolderPtr> codeHolder);

    public:

        Void Run(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration) override;

    private:

        CGBackend _backend;

        LRef<GSCodeHolderPtr> _codeHolder;
    };

    inline AST::GSPassPtr CreateCGPass(CGBackend backend, LRef<GSCodeHolderPtr> codeHolder) {
        return std::make_shared<GS_CGPass>(backend, codeHolder);
    }

}

#endif //GSLANGUAGE_GS_CGPASS_H
