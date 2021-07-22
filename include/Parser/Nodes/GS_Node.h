#ifndef GSLANGUAGE_GS_NODE_H
#define GSLANGUAGE_GS_NODE_H

#include <memory>
#include <vector>

#include <CrossPlatform/GS_PlatformTypes.h>

namespace GSLanguageCompiler::Parser {

    /**
     * For typing parser nodes
     */
    enum class NodeType {
        VALUE_NODE,
        UNARY_NODE,
        BINARY_NODE
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
         * Virtual function for generating code
         * @return Generated code
         */
//        virtual GSString codegen() = 0;

        /**
         * Method for convert parser node to string
         * @return String node data
         */
        virtual GSString toString() = 0;
    };

    typedef std::shared_ptr<GS_Node> GSNodePtr;

    typedef std::vector<GSNodePtr> GSNodePtrArray;

}

#endif //GSLANGUAGE_GS_NODE_H
