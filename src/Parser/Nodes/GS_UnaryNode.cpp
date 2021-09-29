#include <Nodes/GS_UnaryNode.h>

namespace GSLanguageCompiler::Parser {

    std::map<UnaryOperation, GSString> unaryOperationToString = {
            {UnaryOperation::MINUS, "-"}
    };

    GS_UnaryNode::GS_UnaryNode(UnaryOperation operation, GSNodePtr node)
            : _operation(operation), _node(std::move(node)) {}

    UnaryOperation GS_UnaryNode::getUnaryOperation() {
        return _operation;
    }

    GSNodePtr GS_UnaryNode::getNode() {
        return _node;
    }

    NodeType GS_UnaryNode::getNodeType() {
        return NodeType::UNARY_NODE;
    }

    llvm::Value *GS_UnaryNode::accept(GS_Visitor<llvm::Value*> *visitor) {
        return visitor->visit(this);
    }

    GSVoid GS_UnaryNode::accept(GS_Visitor<GSVoid> *visitor) {
        return visitor->visit(this);
    }

    GSNodePtr GS_UnaryNode::accept(GS_Visitor<GSNodePtr> *visitor) {
        return visitor->visit(this);
    }

}