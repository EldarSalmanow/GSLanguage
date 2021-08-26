#include <Nodes/GS_ValueNode.h>

namespace GSLanguageCompiler::Parser {

    GS_ValueNode::GS_ValueNode(GSValuePtr value)
            : _value(std::move(value)) {}

    GSValuePtr GS_ValueNode::getValue() {
        return _value;
    }

    NodeType GS_ValueNode::getNodeType() {
        return NodeType::VALUE_NODE;
    }

    GSValuePtr GS_ValueNode::interpret() {
        return _value;
    }

    GSVoid GS_ValueNode::accept(GS_Visitor *visitor) {
        visitor->visit(this);
    }

}