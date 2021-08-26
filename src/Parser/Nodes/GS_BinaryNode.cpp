#include <Nodes/GS_BinaryNode.h>

namespace GSLanguageCompiler::Parser {

    std::map<BinaryOperation, GSString> binaryOperationToString{
            {BinaryOperation::PLUS,  "+"},
            {BinaryOperation::MINUS, "-"},
            {BinaryOperation::STAR,  "*"},
            {BinaryOperation::SLASH, "/"}
    };

    GS_BinaryNode::GS_BinaryNode(BinaryOperation operation, GSNodePtr firstNode, GSNodePtr secondNode)
            : _operation(operation), _firstNode(std::move(firstNode)), _secondNode(std::move(secondNode)) {}

    BinaryOperation GS_BinaryNode::getBinaryOperation() {
        return _operation;
    }

    GSNodePtr GS_BinaryNode::getFirstNode() {
        return _firstNode;
    }

    GSNodePtr GS_BinaryNode::getSecondNode() {
        return _secondNode;
    }

    NodeType GS_BinaryNode::getNodeType() {
        return NodeType::BINARY_NODE;
    }

    GSValuePtr GS_BinaryNode::interpret() {
        auto firstValue = dynamic_cast<GS_IntegerValue*>(_firstNode->interpret().get())->getData<GSInt>();
        auto secondValue = dynamic_cast<GS_IntegerValue*>(_secondNode->interpret().get())->getData<GSInt>();

        switch (_operation) {
            case BinaryOperation::PLUS:
                return std::make_shared<GS_IntegerValue>(firstValue + secondValue);
            case BinaryOperation::MINUS:
                return std::make_shared<GS_IntegerValue>(firstValue - secondValue);
            case BinaryOperation::STAR:
                return std::make_shared<GS_IntegerValue>(firstValue * secondValue);
            case BinaryOperation::SLASH:
                if (secondValue == 0) {
                    Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                                   "Division by zero!");

                    Exceptions::errorHandler.throw_();
                }

                return std::make_shared<GS_IntegerValue>(firstValue / secondValue);
        }
    }

    GSVoid GS_BinaryNode::accept(GS_Visitor *visitor) {
        visitor->visit(this);
    }

}