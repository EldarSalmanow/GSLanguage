#ifndef GSLANGUAGE_GS_ASSIGNMENTNODE_H
#define GSLANGUAGE_GS_ASSIGNMENTNODE_H

#include <Parser/Nodes/GS_Node.h>

namespace GSLanguageCompiler::Parser {

    /**
     * AST node for assignment
     */
    class GS_AssignmentNode : public GS_Node {
    public:

        /**
         * Constructor for assignment node
         * @param node Declaration or using node
         * @param expression Expression for assign
         */
        GS_AssignmentNode(GSNodePtr node, GSNodePtr expression);

    public:

        /**
         * Getter for declaration or using
         * @return Node ptr
         */
        GSNodePtr getNode();

        /**
         * Getter for expression for assign
         * @return Node ptr
         */
        GSNodePtr getExpression();

    public:

        /**
         * Getter for node type
         * @return Node type
         */
        NodeType getNodeType() override;

        /**
         * Acceptor for codegen visitor
         * @param visitor Codegen visitor
         * @return LLVM IR instructions
         */
        llvm::Value *accept(GS_Visitor<llvm::Value*> *visitor) override;

        /**
         * Acceptor for semantic analyzer
         * @param visitor Semantic pass
         * @return
         */
        GSVoid accept(GS_Visitor<GSVoid> *visitor) override;

        /**
         * Acceptor for optimizer analyzer
         * @param visitor Optimizer pass
         * @return Optimized node
         */
        GSNodePtr accept(GS_Visitor<GSNodePtr> *visitor) override;

    private:

        /**
         * Declaration or using and expression nodes
         */
        GSNodePtr _node, _expression;
    };

}

#endif //GSLANGUAGE_GS_ASSIGNMENTNODE_H
