#include <GS_OptimizerPass.h>

#include <Parser/GS_IncludeNodes.h>

namespace GSLanguageCompiler::Optimizer {

    Parser::GSNodePtr GS_OptimizerPass::visit(Parser::GS_RootNode *rootNode) {
        auto node = rootNode->getNode()->accept(this);

        return std::make_shared<Parser::GS_RootNode>(node);
    }

    Parser::GSNodePtr GS_OptimizerPass::visit(Parser::GS_BlockNode *blockNode) {
        Parser::GSNodePtrArray nodes;

        for (auto &node : blockNode->getNodes()) {
            nodes.emplace_back(node->accept(this));
        }

        return std::make_shared<Parser::GS_BlockNode>(nodes);
    }

    Parser::GSNodePtr GS_OptimizerPass::visit(Parser::GS_ValueNode *valueNode) {
        return std::make_shared<Parser::GS_ValueNode>(*valueNode);
    }

    Parser::GSNodePtr GS_OptimizerPass::visit(Parser::GS_UnaryNode *unaryNode) {
        return std::make_shared<Parser::GS_UnaryNode>(*unaryNode);
    }

    Parser::GSNodePtr GS_OptimizerPass::visit(Parser::GS_BinaryNode *binaryNode) {
        return std::make_shared<Parser::GS_BinaryNode>(*binaryNode);
    }

    Parser::GSNodePtr GS_OptimizerPass::visit(Parser::GS_VariableNode *variableNode) {
        return std::make_shared<Parser::GS_VariableNode>(*variableNode);
    }

    Parser::GSNodePtr GS_OptimizerPass::visit(Parser::GS_PrintNode *printNode) {
        return std::make_shared<Parser::GS_PrintNode>(*printNode);
    }

}
