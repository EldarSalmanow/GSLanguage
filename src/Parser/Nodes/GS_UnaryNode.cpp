#include <Nodes/GS_UnaryNode.h>

namespace GSLanguageCompiler::Parser {

    std::map<UnaryOperation, GSString> unaryOperationToString{
            {UnaryOperation::MINUS, "-"}
    };

    GS_UnaryNode::GS_UnaryNode(UnaryOperation operation, GSNodePtr node)
            : _operation(operation), _node(std::move(node)) {}

    UnaryOperation GS_UnaryNode::getUnaryOperation() {
        return _operation;
    }

    GSNodePtr GS_UnaryNode::getNode() {
        return _node;
    }

    NodeType GS_UnaryNode::getNodeType() {
        return NodeType::UNARY_NODE;
    }

    GSValuePtr GS_UnaryNode::interpret() {
        auto value = dynamic_cast<GS_IntegerValue*>(_node->interpret().get())->getData<GSInt>();

        switch (_operation) {
            case UnaryOperation::MINUS:
                return std::make_shared<GS_IntegerValue>(-value);
        }
    }

    GSString GS_UnaryNode::toString() {
        return "["
               + unaryOperationToString[_operation]
               + " "
               + _node->toString()
               + " ]";
    }

    GSVoid GS_UnaryNode::accept(GS_Visitor *visitor) {
        visitor->visit(this);
    }

}