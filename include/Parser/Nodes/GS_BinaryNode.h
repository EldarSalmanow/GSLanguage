#ifndef GSLANGUAGE_GS_BINARYNODE_H
#define GSLANGUAGE_GS_BINARYNODE_H

#include <map>

#include <Parser/Nodes/GS_Node.h>

namespace GSLanguageCompiler::Parser {

    /**
     * Supported binary operations
     */
    enum class BinaryOperation {
        PLUS,
        MINUS,
        STAR,
        SLASH
    };

    /**
     * Map for converting binary operation to string
     */
    extern std::map<BinaryOperation, GSString> binaryOperationToString;

    /**
     * AST node for binary operations
     */
    class GS_BinaryNode : public GS_Node {
    public:

        /**
         * Constructor for binary node
         * @param operation Binary operation
         * @param firstNode First node
         * @param secondNode Second node
         */
        GS_BinaryNode(BinaryOperation operation, GSNodePtr firstNode, GSNodePtr secondNode);

    public:

        /**
         * Getter for binary operation
         * @return Binary operation
         */
        BinaryOperation getBinaryOperation();

        /**
         * Getter for first node
         * @return First node
         */
        GSNodePtr getFirstNode();

        /**
         * Getter for second node
         * @return Second node
         */
        GSNodePtr getSecondNode();

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
         * Binary operation
         */
        BinaryOperation _operation;

        /**
         * First and second nodes
         */
        GSNodePtr _firstNode, _secondNode;
    };

}

#endif //GSLANGUAGE_GS_BINARYNODE_H
