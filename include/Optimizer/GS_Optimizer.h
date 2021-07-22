#ifndef GSLANGUAGE_GS_OPTIMIZER_H
#define GSLANGUAGE_GS_OPTIMIZER_H

#include <Parser/GS_Parser.h>

namespace GSLanguageCompiler::Optimizer {

    /**
     *
     */
    class GS_Optimizer {
    public:

        /**
         *
         * @param nodes
         */
        explicit GS_Optimizer(Parser::GSNodePtrArray nodes);

    public:

        /**
         *
         * @return
         */
        Parser::GSNodePtrArray optimize();

    private:

        /**
         *
         * @param node
         * @return
         */
        Parser::GSNodePtr optimizeNode(Parser::GSNodePtr &node);

        /**
         *
         * @param node
         * @return
         */
        Parser::GSNodePtr optimizeUnaryNode(Parser::GSNodePtr &node);

        /**
         *
         * @param node
         * @return
         */
        Parser::GSNodePtr optimizeBinaryNode(Parser::GSNodePtr &node);

    private:

        /**
         *
         */
        Parser::GSNodePtrArray _nodes;
    };

    typedef std::shared_ptr<GS_Optimizer> GSOptimizerPointer;

}

#endif //GSLANGUAGE_GS_OPTIMIZER_H
