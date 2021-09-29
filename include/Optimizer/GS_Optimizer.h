#ifndef GSLANGUAGE_GS_OPTIMIZER_H
#define GSLANGUAGE_GS_OPTIMIZER_H

#include <Starter/GS_Runnable.h>

#include <Optimizer/GS_ConstantFoldingPass.h>

namespace GSLanguageCompiler::Optimizer {

    /**
     * Class for optimizing program AST
     */
    class GS_Optimizer : public Starter::GS_Runnable {
    public:

        GS_Optimizer();

    public:

        GSVoid run(Starter::GSContextPtr &context) override;
    };

}

#endif //GSLANGUAGE_GS_OPTIMIZER_H
