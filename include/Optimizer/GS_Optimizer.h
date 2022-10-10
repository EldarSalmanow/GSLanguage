#ifndef GSLANGUAGE_GS_OPTIMIZER_H
#define GSLANGUAGE_GS_OPTIMIZER_H

#include <Optimizer/Passes/Passes.h>

namespace GSLanguageCompiler::Optimizer {

    /**
     * Class for optimizing AST
     */
    class GS_Optimizer {
    public:

        /**
         * Constructor for optimizer
         * @param context Context
         */
        explicit GS_Optimizer(Driver::GSContextPtr context);

    public:

        /**
         * Creating optimizer
         * @param context Context
         * @return Optimizer ptr
         */
        static std::shared_ptr<GS_Optimizer> Create(Driver::GSContextPtr context);

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
         * Context
         */
        Driver::GSContextPtr _context;
    };

}

#endif //GSLANGUAGE_GS_OPTIMIZER_H
