#include <GS_OptimizerPass.h>

#include <AST/GS_IncludeNodes.h>

namespace GSLanguageCompiler::Optimizer {

    GSVoid GS_OptimizerPass::setup(Starter::GSContextPtr &context) {
        _context = context;
    }

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

    Parser::GSNodePtr GS_OptimizerPass::visit(Parser::GS_AssignmentNode *assignmentNode) {
        return std::make_shared<Parser::GS_AssignmentNode>(*assignmentNode);
    }

    Parser::GSNodePtr GS_OptimizerPass::visit(Parser::GS_VariableDeclarationNode *variableDeclarationNode) {
        return std::make_shared<Parser::GS_VariableDeclarationNode>(*variableDeclarationNode);
    }

    Parser::GSNodePtr GS_OptimizerPass::visit(Parser::GS_VariableUsingNode *variableUsingNode) {
        return std::make_shared<Parser::GS_VariableUsingNode>(*variableUsingNode);
    }

}
