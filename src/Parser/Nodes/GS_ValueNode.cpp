#include <Nodes/GS_ValueNode.h>

namespace GSLanguageCompiler::Parser {

    GS_ValueNode::GS_ValueNode(GSValuePtr value)
            : _value(value) {}

    GSValuePtr GS_ValueNode::getValue() {
        return _value;
    }

    NodeType GS_ValueNode::getNodeType() {
        return NodeType::VALUE_NODE;
    }

//    GSString GS_ValueNode::codegen() {
//        return "push " + std::to_string(_value->getData<int>()) + "\n";
//    }

    GSString GS_ValueNode::toString() {
        GSString string;

        if (_value->getType() == "Int") {
            string = std::to_string(_value->getData<int>());
        } else {
            throw Exceptions::GS_Exception("Unknown type for casting to string!");
        }

        return string;
    }

}