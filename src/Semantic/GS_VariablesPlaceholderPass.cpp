#include <GS_VariablesPlaceholderPass.h>

#include <AST/GS_IncludeNodes.h>

#include <Semantic/GS_TableOfVariables.h>

namespace GSLanguageCompiler::Semantic {

    GS_VariablesPlaceholderPass::GS_VariablesPlaceholderPass() = default;

    GSVoid GS_VariablesPlaceholderPass::visit(Parser::GS_AssignmentNode *assignmentNode) {
        auto declaration = assignmentNode->getNode();
        auto expression = assignmentNode->getExpression();

        if (declaration->getNodeType() != Parser::NodeType::VARIABLE_DECLARATION_NODE) {
            return;
        }

        auto variableDeclaration = std::reinterpret_pointer_cast<Parser::GS_VariableDeclarationNode>(declaration);

        _context->getTableOfVariables()->addVariable(variableDeclaration.get(), expression);
    }

}
