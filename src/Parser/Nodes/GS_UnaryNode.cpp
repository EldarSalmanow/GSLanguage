#include <Nodes/GS_UnaryNode.h>

namespace GSLanguageCompiler::Parser {

    std::map<UnaryOperation, GSString> unaryOperationToString{
            {UnaryOperation::MINUS, "-"}
    };

    GS_UnaryNode::GS_UnaryNode(UnaryOperation operation, GSNodePtr node)
            : _operation(operation), _node(node) {}

    UnaryOperation GS_UnaryNode::getUnaryOperation() {
        return _operation;
    }

    GSNodePtr GS_UnaryNode::getNode() {
        return _node;
    }

    NodeType GS_UnaryNode::getNodeType() {
        return NodeType::UNARY_NODE;
    }

//    GSString GS_UnaryNode::codegen() {
//        throw std::runtime_error("Generating code for unary nodes not supported!");
//    }

    GSString GS_UnaryNode::toString() {
        return "["
               + unaryOperationToString[_operation]
               + " "
               + _node->toString()
               + " ]";
    }

}