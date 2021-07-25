#include <Nodes/GS_PrintNode.h>

namespace GSLanguageCompiler::Parser {

    GS_PrintNode::GS_PrintNode(GS_StringValue &stringValue)
            : _string(stringValue) {}

    NodeType GS_PrintNode::getNodeType() {
        return NodeType::PRINT_NODE;
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
