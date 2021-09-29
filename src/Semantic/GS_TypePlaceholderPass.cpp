#include <GS_TypePlaceholderPass.h>

#include <Parser/GS_IncludeNodes.h>

namespace GSLanguageCompiler::Semantic {

    GS_TypePlaceholderPass::GS_TypePlaceholderPass() = default;

    GSVoid GS_TypePlaceholderPass::visit(Parser::GS_AssignmentNode *assignmentNode) {
        auto node = assignmentNode->getNode();

        if (node->getNodeType() != Parser::NodeType::VARIABLE_DECLARATION_NODE) {
            return;
        }

        auto declaration = std::reinterpret_pointer_cast<Parser::GS_VariableDeclarationNode>(node);
        auto expression = assignmentNode->getExpression();

        if (declaration->getType() == Parser::ValueType::VOID) {
            declaration->setType(_evaluateTypeInExpression(expression));
        }
    }

}
