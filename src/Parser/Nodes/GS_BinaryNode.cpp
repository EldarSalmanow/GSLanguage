#include <Nodes/GS_BinaryNode.h>

namespace GSLanguageCompiler::Parser {

    std::map<BinaryOperation, GSString> binaryOperationToString{
            {BinaryOperation::PLUS,  "+"},
            {BinaryOperation::MINUS, "-"},
            {BinaryOperation::STAR,  "*"},
            {BinaryOperation::SLASH, "/"}
    };

    GS_BinaryNode::GS_BinaryNode(BinaryOperation operation, GSNodePtr firstNode, GSNodePtr secondNode)
            : _operation(operation), _firstNode(firstNode), _secondNode(secondNode) {}

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

//    GSString GS_BinaryNode::codegen() {
//        GSString code = _firstNode->codegen() + _secondNode->codegen();
//
//        switch (_operation) {
//            case BinaryOperation::PLUS:
//                code += "add\n";
//                break;
//            case BinaryOperation::MINUS:
//                code += "sub\n";
//                break;
//            case BinaryOperation::STAR:
//                code += "mul\n";
//                break;
//            case BinaryOperation::SLASH:
//                code += "div\n";
//                break;
//        }
//
//        return code;
//    }

    GSString GS_BinaryNode::toString() {
        return "[ "
               + _firstNode->toString()
               + " "
               + binaryOperationToString[_operation]
               + " "
               + _secondNode->toString()
               + " ]";
    }

}