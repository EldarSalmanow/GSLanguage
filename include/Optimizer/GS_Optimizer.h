#ifndef GSLANGUAGE_GS_OPTIMIZER_H
#define GSLANGUAGE_GS_OPTIMIZER_H

#include <Parser/GS_Parser.h>

#include <Optimizer/GS_ConstantFoldingPass.h>

namespace GSLanguageCompiler::Optimizer {

    /**
     *
     */
    class GS_Optimizer {
    public:

        /**
         *
         * @param nodes
         * @param passes
         */
        explicit GS_Optimizer(Parser::GSNodePtr nodes, GSOptimizerPassPtrArray passes);

    public:

        /**
         *
         * @return
         */
        Parser::GSNodePtr optimize();

    private:

        /**
         *
         */
        Parser::GSNodePtr _nodes;

        /**
         *
         */
        GSOptimizerPassPtrArray _passes;
    };

}

#endif //GSLANGUAGE_GS_OPTIMIZER_H
