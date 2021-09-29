#ifndef GSLANGUAGE_GS_NODE_H
#define GSLANGUAGE_GS_NODE_H

#include <Parser/Visitors/GS_Visitor.h>

#include <CrossPlatform/GS_PlatformTypes.h>

namespace llvm {

    class Value;

}

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

        ASSIGNMENT_NODE,

        VARIABLE_DECLARATION_NODE,

        VARIABLE_USING_NODE
    };

    class GS_Node;

    typedef std::shared_ptr<GS_Node> GSNodePtr;

    typedef std::vector<GSNodePtr> GSNodePtrArray;

    /**
     * Base class for all AST nodes
     */
    class GS_Node {
    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Node();

    public:

        /**
         * Getter for node type
         * @return Node type
         */
        virtual NodeType getNodeType() = 0;

        /**
         * Acceptor for code generation visitors
         * @param visitor Codegen visitor
         * @return LLVM IR instructions
         */
        virtual llvm::Value *accept(GS_Visitor<llvm::Value*> *visitor) = 0;

        /**
         * Acceptor for semantic visitors
         * @param visitor Semantic visitor
         * @return
         */
        virtual GSVoid accept(GS_Visitor<GSVoid> *visitor) = 0;

        /**
         * Acceptor for optimizer visitors
         * @param visitor Optimizing visitor
         * @return Optimized node
         */
        virtual GSNodePtr accept(GS_Visitor<GSNodePtr> *visitor) = 0;
    };

}

#endif //GSLANGUAGE_GS_NODE_H
