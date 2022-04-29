#ifndef GSLANGUAGE_GS_OPTIMIZER_H
#define GSLANGUAGE_GS_OPTIMIZER_H

#include <Optimizer/Passes/Passes.h>

namespace GSLanguageCompiler::Optimizer {

    /**
     * Class for optimizing program AST
     */
    class GS_Optimizer {
    public:

        explicit GS_Optimizer(AST::GSPassPtrArray passes);

    public:

        static SharedPtr<GS_Optimizer> Create(AST::GSPassPtrArray passes);

        static SharedPtr<GS_Optimizer> Create();

    public:

        Void Optimize(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration);

    private:

        AST::GSPassPtrArray _passes;
    };

}

#endif //GSLANGUAGE_GS_OPTIMIZER_H
