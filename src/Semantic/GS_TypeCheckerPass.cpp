#include <GS_TypeCheckerPass.h>

#include <Parser/GS_IncludeNodes.h>

namespace GSLanguageCompiler::Semantic {

    GS_TypeCheckerPass::GS_TypeCheckerPass() = default;

    GSVoid GS_TypeCheckerPass::visit(Parser::GS_AssignmentNode *assignmentNode) {
        auto declaration = assignmentNode->getNode();
        auto expression = assignmentNode->getExpression();

        if (declaration->getNodeType() != Parser::NodeType::VARIABLE_DECLARATION_NODE) {
            return;
        }

        auto variableDeclaration = std::reinterpret_pointer_cast<Parser::GS_VariableDeclarationNode>(declaration);

        if (variableDeclaration->getType() != _evaluateTypeInExpression(expression)) {
            Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                           "Types in variable declaration and expression is different!");

            Exceptions::errorHandler.throw_();
        }
    }

}
