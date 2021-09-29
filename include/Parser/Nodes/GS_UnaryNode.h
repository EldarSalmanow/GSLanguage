#ifndef GSLANGUAGE_GS_UNARYNODE_H
#define GSLANGUAGE_GS_UNARYNODE_H

#include <map>

#include <Parser/Nodes/GS_Node.h>

namespace GSLanguageCompiler::Parser {

    /**
     * Supported unary operations
     */
    enum class UnaryOperation {
        MINUS
    };

    /**
     * Unary operation to string converter
     */
    extern std::map<UnaryOperation, GSString> unaryOperationToString;

    /**
     * Class for AST unary node
     */
    class GS_UnaryNode : public GS_Node {
    public:

        /**
         * Constructor for unary node
         * @param operation Unary operation
         * @param node Node ptr
         */
        GS_UnaryNode(UnaryOperation operation, GSNodePtr node);

    public:

        /**
         * Getter for unary operation
         * @return Unary operation
         */
        UnaryOperation getUnaryOperation();

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
         * Unary operation
         */
        UnaryOperation _operation;

        /**
         * Node ptr
         */
        GSNodePtr _node;
    };

}

#endif //GSLANGUAGE_GS_UNARYNODE_H
