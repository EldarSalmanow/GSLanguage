#ifndef GSLANGUAGE_GS_OPTIMIZER_H
#define GSLANGUAGE_GS_OPTIMIZER_H

#include <Optimizer/Passes/OptimizingPasses.h>

namespace GSLanguageCompiler::Optimizer {

    /**
     * Class for optimizing AST
     */
    class GS_Optimizer {
    public:

        /*
         *
         * GS_Optimizer PUBLiC CONSTRUCTORS
         *
         */

        /**
         * Constructor for optimizer
         * @param session Session
         * @param optimizingPasses Optimizing passes
         */
        GS_Optimizer(LRef<Driver::GS_Session> session,
                     AST::GSPassPtrArray optimizingPasses);

    public:

        /*
         *
         * GS_Optimizer PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating optimizer
         * @param session Session
         * @param optimizingPasses Optimizing passes
         * @return Optimizer ptr
         */
        static std::unique_ptr<GS_Optimizer> Create(LRef<Driver::GS_Session> session,
                                                    AST::GSPassPtrArray optimizingPasses);

        /**
         * Creating optimizer with default optimizing passes
         * @param session Session
         * @return Optimizer ptr
         */
        static std::unique_ptr<GS_Optimizer> Create(LRef<Driver::GS_Session> session);

    public:

        /*
         *
         * GS_Optimizer PUBLIC METHODS
         *
         */

        /**
         * Run optimizing passes for optimize node
         * @param node Node
         * @return Void return
         */
        Void Optimize(LRef<AST::GSNodePtr> node);

    private:

        /*
         *
         * GS_Optimizer PRIVATE FIELDS
         *
         */

        /**
         * Session
         */
        LRef<Driver::GS_Session> _session;

        /**
         * Optimizing passes
         */
        AST::GSPassPtrArray _optimizingPasses;
    };

    /**
     * Optimizer ptr type
     */
    using GSOptimizerPtr = std::unique_ptr<GS_Optimizer>;

}

#endif //GSLANGUAGE_GS_OPTIMIZER_H
