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

    GSVoid GS_ValueNode::codegen(CodeGenerator::GS_BCBuilder &builder) {
        auto type = _value->getType();

        if (type == "Int") {
            builder.createPush(_value->getData<GSInt>());
        } else if (type == "String") {
            builder.createConstant(_value->getData<GSString>(), tableOfConstants.getIdByValue(_value->getData<GSString>()));
        }
    }

    GSValuePtr GS_ValueNode::interpret() {
        return _value;
    }

    GSString GS_ValueNode::toString() {
        GSString string;

        if (_value->getType() == "Int") {
            string = std::to_string(_value->getData<GSInt>());
        } else {
            throw Exceptions::GS_Exception("Unknown type for casting to string!");
        }

        return string;
    }

}