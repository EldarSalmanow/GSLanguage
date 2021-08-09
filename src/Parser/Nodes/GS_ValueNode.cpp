#include <Nodes/GS_ValueNode.h>

#include <utility>

namespace GSLanguageCompiler::Parser {

    GS_ValueNode::GS_ValueNode(GSValuePtr value)
            : _value(std::move(value)) {}

    GSValuePtr GS_ValueNode::getValue() {
        return _value;
    }

    NodeType GS_ValueNode::getNodeType() {
        return NodeType::VALUE_NODE;
    }

    CodeGenerator::GSByteCode GS_ValueNode::codegen() {
        CodeGenerator::GSByteCode bytecode;

        auto type = _value->getType();

        if (type == "Int") {
            bytecode.emplace_back(CodeGenerator::opcodeToByte[CodeGenerator::Opcode::PUSH]);

            bytecode.emplace_back(_value->getData<GSInt>());
        } else if (type == "String") {
            throw Exceptions::GS_Exception("Generating string constant not supported!");
        }

        return bytecode;
    }

    GSValuePtr GS_ValueNode::interpret() {
        return _value;
    }

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