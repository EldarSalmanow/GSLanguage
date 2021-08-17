#include <Nodes/GS_PrintNode.h>

namespace GSLanguageCompiler::Parser {

    GS_PrintNode::GS_PrintNode(GSValuePtr value)
            : _value(std::move(value)) {}

    NodeType GS_PrintNode::getNodeType() {
        return NodeType::PRINT_NODE;
    }

    GSValuePtr GS_PrintNode::interpret() {
        std::cout << _value->getData<GSString>();

        return nullptr;
    }

    GSString GS_PrintNode::toString() {
        return "[ "
               + GSString("print")
               + " ("
               + " \""
               + _value->getData<GSString>()
               + "\""
               + " )"
               + " ]";
    }

    GSVoid GS_PrintNode::accept(GS_Visitor *visitor) {
        visitor->visit(this);
    }

}
