#include <GS_Optimizer.h>

namespace GSLanguageCompiler::Optimizer {

    GS_Optimizer::GS_Optimizer(Parser::GSNodePtrArray nodes)
            : _nodes(std::move(nodes)) {}

    Parser::GSNodePtrArray GS_Optimizer::optimize() {
        for (auto &node : _nodes) {
            node = optimizeNode(node);
        }

        return _nodes;
    }

    Parser::GSNodePtr GS_Optimizer::optimizeNode(Parser::GSNodePtr &node) {
        switch (node->getNodeType()) {
            case Parser::NodeType::VALUE_NODE:
                return node;
            case Parser::NodeType::UNARY_NODE:
                return optimizeUnaryNode(node);
            case Parser::NodeType::BINARY_NODE:
                return optimizeBinaryNode(node);
            case Parser::NodeType::VARIABLE_NODE:
                return node;
            case Parser::NodeType::PRINT_NODE:
                return node;
            default:
                throw Exceptions::GS_Exception("Unknown node type for optimization!");
        }
    }

    Parser::GSNodePtr GS_Optimizer::optimizeUnaryNode(Parser::GSNodePtr &node) {
        auto unaryNode = dynamic_cast<Parser::GS_UnaryNode *>(node.get());

        auto nodeFromUnaryNode = unaryNode->getNode();

        nodeFromUnaryNode = optimizeNode(nodeFromUnaryNode);

        if (nodeFromUnaryNode->getNodeType() == Parser::NodeType::VALUE_NODE) {
            auto valueNode = dynamic_cast<Parser::GS_ValueNode *>(nodeFromUnaryNode.get());

            // TODO remake this optimization for another value types
            Parser::GS_IntegerValue value;

            switch (unaryNode->getUnaryOperation()) {
                case Parser::UnaryOperation::MINUS:
                    value = -valueNode->getValue()->getData<int>();
                    break;
            }

            return std::make_shared<Parser::GS_ValueNode>(std::make_shared<Parser::GS_IntegerValue>(value));
        } else {
            return std::make_shared<Parser::GS_UnaryNode>(unaryNode->getUnaryOperation(), nodeFromUnaryNode);
        }
    }

    Parser::GSNodePtr GS_Optimizer::optimizeBinaryNode(Parser::GSNodePtr &node) {
        auto binaryNode = dynamic_cast<Parser::GS_BinaryNode *>(node.get());

        auto firstNodeFromBinaryNode = binaryNode->getFirstNode();
        auto secondNodeFromBinaryNode = binaryNode->getSecondNode();

        firstNodeFromBinaryNode = optimizeNode(firstNodeFromBinaryNode);
        secondNodeFromBinaryNode = optimizeNode(secondNodeFromBinaryNode);

        if (firstNodeFromBinaryNode->getNodeType() == Parser::NodeType::VALUE_NODE &&
            secondNodeFromBinaryNode->getNodeType() == Parser::NodeType::VALUE_NODE) {
            auto firstValueNode = dynamic_cast<Parser::GS_ValueNode *>(firstNodeFromBinaryNode.get());
            auto secondValueNode = dynamic_cast<Parser::GS_ValueNode *>(secondNodeFromBinaryNode.get());

            // TODO remake this optimization for another value types
            Parser::GS_IntegerValue value;

            switch (binaryNode->getBinaryOperation()) {
                case Parser::BinaryOperation::PLUS:
                    value = firstValueNode->getValue()->getData<int>() + secondValueNode->getValue()->getData<int>();
                    break;
                case Parser::BinaryOperation::MINUS:
                    value = firstValueNode->getValue()->getData<int>() - secondValueNode->getValue()->getData<int>();
                    break;
                case Parser::BinaryOperation::STAR:
                    value = firstValueNode->getValue()->getData<int>() * secondValueNode->getValue()->getData<int>();
                    break;
                case Parser::BinaryOperation::SLASH:
                    value = firstValueNode->getValue()->getData<int>() / secondValueNode->getValue()->getData<int>();
                    break;
            }

            return std::make_shared<Parser::GS_ValueNode>(std::make_shared<Parser::GS_IntegerValue>(value));
        } else {
            return std::make_shared<Parser::GS_BinaryNode>(binaryNode->getBinaryOperation(), firstNodeFromBinaryNode, secondNodeFromBinaryNode);
        }
    }

}