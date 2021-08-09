#include <Nodes/GS_VariableNode.h>

namespace GSLanguageCompiler::Parser {

    GS_VariableNode::GS_VariableNode() = default;

    GS_VariableNode::GS_VariableNode(GSString name)
            : _name(std::move(name)) {}

    GS_VariableNode::GS_VariableNode(GSString name, GSString type)
            : _name(std::move(name)), _type(std::move(type)) {}

    GS_VariableNode::GS_VariableNode(GSString name, GSNodePtr node)
            : _name(std::move(name)), _node(std::move(node)) {}

    GS_VariableNode::GS_VariableNode(GSString name, GSString type, GSNodePtr node)
            : _name(std::move(name)), _type(std::move(type)), _node(std::move(node)) {}

    NodeType GS_VariableNode::getNodeType() {
        return NodeType::VARIABLE_NODE;
    }

    CodeGenerator::GSByteCode GS_VariableNode::codegen() {
        throw Exceptions::GS_Exception("Generating for variable nodes not supported!");
    }

    GSValuePtr GS_VariableNode::interpret() {
        Interpreter::tableOfSymbols.addVariable(_name, _node->interpret());
    }

    GSString GS_VariableNode::toString() {
        return "[ "
               + _name
               + ": "
               + _type
               + " = "
               + _node->toString()
               + " ]";
    }

}
