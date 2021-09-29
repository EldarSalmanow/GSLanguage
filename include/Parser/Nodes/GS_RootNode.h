#ifndef GSLANGUAGE_GS_ROOTNODE_H
#define GSLANGUAGE_GS_ROOTNODE_H

#include <Parser/Nodes/GS_Node.h>

namespace GSLanguageCompiler::Parser {

    /**
     * Class for root AST node
     */
    class GS_RootNode : public GS_Node {
    public:

        /**
         * Constructor for root node
         * @param node Node ptr
         */
        explicit GS_RootNode(GSNodePtr node);

    public:

        /**
         * Getter for node ptr
         * @return Node ptr
         */
        GSNodePtr getNode();

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
         * Node ptr
         */
        GSNodePtr _node;
    };

}

#endif //GSLANGUAGE_GS_ROOTNODE_H
