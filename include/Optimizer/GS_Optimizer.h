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
         * @param passes Optimizing passes
         * @param context Context
         */
//        GS_Optimizer(AST::GSPassPtrArray passes, Driver::GSContextPtr context);


        /**
         * Constructor for optimizer
         * @param context Context
         */
        explicit GS_Optimizer(Driver::GSContextPtr context);

    public:

        /**
         * Creating optimizer
         * @param passes Optimizing passes
         * @param context Context
         * @return Optimizer ptr
         */
//        static std::shared_ptr<GS_Optimizer> Create(AST::GSPassPtrArray passes, Driver::GSContextPtr context);

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
         * @return Optimized node
         */
        AST::GSNodePtr Optimize(AST::GSNodePtr node, AST::GSPassPtrArray passes);

    public:

        /**
         * Add pass to passes list
         * @param pass Pass
         * @return
         */
//        Void AddPass(AST::GSPassPtr pass);

    private:

        /**
         * Passes
         */
//        AST::GSPassPtrArray _passes;

        /**
         * Context
         */
        Driver::GSContextPtr _context;
    };

}

#endif //GSLANGUAGE_GS_OPTIMIZER_H
