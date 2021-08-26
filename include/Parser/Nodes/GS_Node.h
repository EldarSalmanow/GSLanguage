#ifndef GSLANGUAGE_GS_NODE_H
#define GSLANGUAGE_GS_NODE_H

#include <Parser/Nodes/GS_Visitor.h>

#include <Optimizer/GS_OptimizerPass.h>

#include <Parser/GS_TablesOfSymbols.h>

namespace GSLanguageCompiler::Parser {

    /**
     * For typing parser nodes
     */
    enum class NodeType {
        ROOT_NODE,

        BLOCK_NODE,

        VALUE_NODE,

        UNARY_NODE,
        BINARY_NODE,

        VARIABLE_NODE,

        PRINT_NODE
    };

    /**
     * Base class for all parser nodes
     */
    class GS_Node {
    public:

        /**
         * Getter for node type
         * @return Node type
         */
        virtual NodeType getNodeType() = 0;

        /**
         *
         * @return
         */
        virtual GSValuePtr interpret() = 0;

        /**
         *
         * @param visitor
         * @return
         */
        virtual GSVoid accept(GS_Visitor *visitor) = 0;

        /**
         *
         * @param pass
         * @return
         */
        virtual GSNodePtr accept(Optimizer::GS_OptimizerPass *pass) = 0;
    };

    typedef std::shared_ptr<GS_Node> GSNodePtr;

    typedef std::vector<GSNodePtr> GSNodePtrArray;

}

#endif //GSLANGUAGE_GS_NODE_H
