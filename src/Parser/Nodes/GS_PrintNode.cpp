#include <Nodes/GS_PrintNode.h>

namespace GSLanguageCompiler::Parser {

    GS_PrintNode::GS_PrintNode(GS_StringValue stringValue)
            : _string(std::move(stringValue)) {}

    NodeType GS_PrintNode::getNodeType() {
        return NodeType::PRINT_NODE;
    }

    CodeGenerator::GSByteCode GS_PrintNode::codegen() {
        throw Exceptions::GS_Exception("Generating code for print node not supported!");
    }

    GSValuePtr GS_PrintNode::interpret() {
        std::cout << _string.getData<GSString>();

        return nullptr;
    }

    GSString GS_PrintNode::toString() {
        return "[ "
               + GSString("print")
               + " ("
               + " \""
               + _string.getData<GSString>()
               + "\""
               + " )"
               + " ]";
    }

}
