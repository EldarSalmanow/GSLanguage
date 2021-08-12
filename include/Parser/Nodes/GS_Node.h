#ifndef GSLANGUAGE_GS_NODE_H
#define GSLANGUAGE_GS_NODE_H

#include <memory>
#include <vector>

#include <Parser/GS_TablesOfSymbols.h>

#include <CodeGenerator/GS_BCBuilder.h>

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
         * Virtual function for generating code
         * @param builder
         */
        virtual GSVoid codegen(CodeGenerator::GS_BCBuilder &builder) = 0;

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
    };

    typedef std::shared_ptr<GS_Node> GSNodePtr;

    typedef std::vector<GSNodePtr> GSNodePtrArray;

}

#endif //GSLANGUAGE_GS_NODE_H
