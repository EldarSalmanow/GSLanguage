#ifndef GSLANGUAGE_GS_BLOCKNODE_H
#define GSLANGUAGE_GS_BLOCKNODE_H

#include <Parser/Nodes/GS_Node.h>

namespace GSLanguageCompiler::Parser {

    /**
     * Class for block AST node
     */
    class GS_BlockNode : public GS_Node {
    public:

        /**
         * Constructor for block node
         * @param nodes Node ptr array
         */
        explicit GS_BlockNode(GSNodePtrArray nodes);

    public:

        /**
         * Getter for node ptr array
         * @return Node ptr array
         */
        GSNodePtrArray getNodes();

    public:

        /**
         * Getter for node type
         * @return Node type
         */
        NodeType getNodeType() override;

        /**
         * Acceptor for code generation visitors
         * @param visitor Codegen visitor
         * @return LLVM IR instructions
         */
        llvm::Value *accept(GS_Visitor<llvm::Value*> *visitor) override;

        /**
         * Acceptor for semantic visitors
         * @param visitor Semantic visitor
         * @return
         */
        GSVoid accept(GS_Visitor<GSVoid> *visitor) override;

        /**
         * Acceptor for optimizer visitors
         * @param visitor Optimizing visitor
         * @return Optimized node
         */
        GSNodePtr accept(GS_Visitor<GSNodePtr> *visitor) override;

    private:

        /**
         * Node ptr array
         */
        GSNodePtrArray _nodes;
    };

}

#endif //GSLANGUAGE_GS_BLOCKNODE_H
