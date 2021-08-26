#include <GS_ConstantFoldingPass.h>

#include <Parser/GS_IncludeNodes.h>

namespace GSLanguageCompiler::Optimizer {

    GS_ConstantFoldingPass::GS_ConstantFoldingPass() = default;

    Parser::GSNodePtr GS_ConstantFoldingPass::visit(Parser::GS_UnaryNode *unaryNode) {
        auto optimizedNode = unaryNode->getNode()->accept(this);

        if (optimizedNode->getNodeType() == Parser::NodeType::VALUE_NODE) {
            auto valueNode = dynamic_cast<Parser::GS_ValueNode *>(optimizedNode.get());

            Parser::GSValuePtr value;

            switch (unaryNode->getUnaryOperation()) {
                case Parser::UnaryOperation::MINUS:
                    value = std::make_shared<Parser::GS_IntegerValue>(-valueNode->getValue()->getData<GSInt>());

                    break;
            }

            return std::make_shared<Parser::GS_ValueNode>(value);
        }

        return std::make_shared<Parser::GS_UnaryNode>(unaryNode->getUnaryOperation(), optimizedNode);
    }

    Parser::GSNodePtr GS_ConstantFoldingPass::visit(Parser::GS_BinaryNode *binaryNode) {
        auto firstOptimizedNode = binaryNode->getFirstNode()->accept(this);
        auto secondOptimizedNode = binaryNode->getSecondNode()->accept(this);

        if (firstOptimizedNode->getNodeType() == Parser::NodeType::VALUE_NODE &&
            secondOptimizedNode->getNodeType() == Parser::NodeType::VALUE_NODE) {
            auto firstValue = dynamic_cast<Parser::GS_ValueNode*>(firstOptimizedNode.get())->getValue();
            auto secondValue = dynamic_cast<Parser::GS_ValueNode*>(secondOptimizedNode.get())->getValue();

            Parser::GSValuePtr value;

            switch (binaryNode->getBinaryOperation()) {
                case Parser::BinaryOperation::PLUS:
                    value = std::make_shared<Parser::GS_IntegerValue>(firstValue->getData<GSInt>()
                            + secondValue->getData<GSInt>());

                    break;
                case Parser::BinaryOperation::MINUS:
                    value = std::make_shared<Parser::GS_IntegerValue>(firstValue->getData<GSInt>()
                            - secondValue->getData<GSInt>());

                    break;
                case Parser::BinaryOperation::STAR:
                    value = std::make_shared<Parser::GS_IntegerValue>(firstValue->getData<GSInt>()
                            * secondValue->getData<GSInt>());

                    break;
                case Parser::BinaryOperation::SLASH:
                    value = std::make_shared<Parser::GS_IntegerValue>(firstValue->getData<GSInt>()
                            / secondValue->getData<GSInt>());

                    break;
            }

            return std::make_shared<Parser::GS_ValueNode>(value);
        }

        return std::make_shared<Parser::GS_BinaryNode>(binaryNode->getBinaryOperation(), firstOptimizedNode, secondOptimizedNode);
    }

    Parser::GSNodePtr GS_ConstantFoldingPass::visit(Parser::GS_VariableNode *variableNode) {
        auto optimizedNode = variableNode->getNode()->accept(this);

        return std::make_shared<Parser::GS_VariableNode>(variableNode->getName(), variableNode->getType(), optimizedNode);
    }

}
