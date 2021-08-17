#ifndef GSLANGUAGE_GS_NODE_H
#define GSLANGUAGE_GS_NODE_H

#include <vector>

#include <Parser/Nodes/GS_Visitor.h>

#include <Parser/GS_TablesOfSymbols.h>

namespace GSLanguageCompiler::Parser {

    /**
     * For typing parser nodes
     */
    enum class NodeType {
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
         * Method for convert parser node to string
         * @return String node data
         */
        virtual GSString toString() = 0;

        /**
         *
         * @param visitor
         * @return
         */
        virtual GSVoid accept(GS_Visitor *visitor) = 0;
    };

    typedef std::shared_ptr<GS_Node> GSNodePtr;

    typedef std::vector<GSNodePtr> GSNodePtrArray;

}

#endif //GSLANGUAGE_GS_NODE_H
