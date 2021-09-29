#include <Nodes/GS_AssignmentNode.h>

namespace GSLanguageCompiler::Parser {

    GS_AssignmentNode::GS_AssignmentNode(GSNodePtr node, GSNodePtr expression)
            : _node(std::move(node)), _expression(std::move(expression)) {}

    GSNodePtr GS_AssignmentNode::getNode() {
        return _node;
    }

    GSNodePtr GS_AssignmentNode::getExpression() {
        return _expression;
    }

    NodeType GS_AssignmentNode::getNodeType() {
        return NodeType::ASSIGNMENT_NODE;
    }

    llvm::Value *GS_AssignmentNode::accept(GS_Visitor<llvm::Value*> *visitor) {
        return visitor->visit(this);
    }

    GSVoid GS_AssignmentNode::accept(GS_Visitor<GSVoid> *visitor) {
        return visitor->visit(this);
    }

    GSNodePtr GS_AssignmentNode::accept(GS_Visitor<GSNodePtr> *visitor) {
        return visitor->visit(this);
    }

}
