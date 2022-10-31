#ifndef GSLANGUAGE_GS_OPTIMIZER_H
#define GSLANGUAGE_GS_OPTIMIZER_H

#include <Optimizer/Passes/OptimizingPasses.h>

namespace GSLanguageCompiler::Optimizer {

    /**
     * Class for optimizing AST
     */
    class GS_Optimizer {
    public:

        /**
         * Constructor for optimizer
         * @param session Session
         */
        explicit GS_Optimizer(LRef<Driver::GS_Session> session);

    public:

        /**
         * Creating optimizer
         * @param session Session
         * @return Optimizer ptr
         */
        static std::shared_ptr<GS_Optimizer> Create(LRef<Driver::GS_Session> session);

    public:

        /**
         * Run optimizing passes for optimize node
         * @param node Node
         * @param passes Optimizing passes
         * @return
         */
        Void Optimize(LRef<AST::GSNodePtr> node, AST::GSPassPtrArray passes);

    private:

        /**
         * Session
         */
        LRef<Driver::GS_Session> _session;
    };

}

#endif //GSLANGUAGE_GS_OPTIMIZER_H
