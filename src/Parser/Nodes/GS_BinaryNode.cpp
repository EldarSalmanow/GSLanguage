#include <Nodes/GS_BinaryNode.h>

namespace GSLanguageCompiler::Parser {

    std::map<BinaryOperation, GSString> binaryOperationToString = {
            {BinaryOperation::PLUS,  "+"},
            {BinaryOperation::MINUS, "-"},
            {BinaryOperation::STAR,  "*"},
            {BinaryOperation::SLASH, "/"}
    };

    GS_BinaryNode::GS_BinaryNode(BinaryOperation operation, GSNodePtr firstNode, GSNodePtr secondNode)
            : _operation(operation), _firstNode(std::move(firstNode)), _secondNode(std::move(secondNode)) {}

    BinaryOperation GS_BinaryNode::getBinaryOperation() {
        return _operation;
    }

    GSNodePtr GS_BinaryNode::getFirstNode() {
        return _firstNode;
    }

    GSNodePtr GS_BinaryNode::getSecondNode() {
        return _secondNode;
    }

    NodeType GS_BinaryNode::getNodeType() {
        return NodeType::BINARY_NODE;
    }

    llvm::Value *GS_BinaryNode::accept(GS_Visitor<llvm::Value*> *visitor) {
        return visitor->visit(this);
    }

    GSVoid GS_BinaryNode::accept(GS_Visitor<GSVoid> *visitor) {
        return visitor->visit(this);
    }

    GSNodePtr GS_BinaryNode::accept(GS_Visitor<GSNodePtr> *visitor) {
        return visitor->visit(this);
    }

}