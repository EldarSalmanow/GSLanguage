#include <GS_SemanticPass.h>

#include <AST/GS_IncludeNodes.h>

#include <Semantic/GS_TableOfVariables.h>

namespace GSLanguageCompiler::Semantic {

    std::vector<Parser::NodeType> expressionTypes = {
            Parser::NodeType::VALUE_NODE,
            Parser::NodeType::UNARY_NODE,
            Parser::NodeType::BINARY_NODE,
            Parser::NodeType::VARIABLE_USING_NODE
    };

    GSBool GS_SemanticPass::_isExpression(const Parser::GSNodePtr &node) {
        return std::find(expressionTypes.begin(), expressionTypes.end(), node->getNodeType()) != expressionTypes.end();
    }

    Parser::ValueType GS_SemanticPass::_evaluateTypeInExpression(const Parser::GSNodePtr &node) {
        if (!_isExpression(node)) {
            Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                           "Can`t evaluate type in not expression node!");

            Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                           "Please, report this error to GSLanguageCompiler repository!");

            Exceptions::errorHandler.throw_();
        }

        switch (node->getNodeType()) {
            case Parser::NodeType::VALUE_NODE: {
                auto valueExpression = std::reinterpret_pointer_cast<Parser::GS_ValueNode>(node);

                return valueExpression->getValue()->getType();
            }
            case Parser::NodeType::UNARY_NODE: {
                auto unaryExpression = std::reinterpret_pointer_cast<Parser::GS_UnaryNode>(node);

                auto unaryExpressionNode = unaryExpression->getNode();

                if (!_isExpression(unaryExpressionNode)) {
                    Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                                   "Can`t evaluate type in unary expression!");

                    Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                                   "Node in unary node not expression!");

                    Exceptions::errorHandler.throw_();
                }

                return _evaluateTypeInExpression(unaryExpressionNode);
            }
            case Parser::NodeType::BINARY_NODE: {
                auto binaryExpression = std::reinterpret_pointer_cast<Parser::GS_BinaryNode>(node);

                auto firstNode = binaryExpression->getFirstNode();
                auto secondNode = binaryExpression->getSecondNode();

                if (!_isExpression(firstNode) || !_isExpression(secondNode)) {
                    Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                                   "Can`t evaluate type in binary expression!");

                    Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                                   "Node in binary node not expression!");

                    Exceptions::errorHandler.throw_();
                }

                auto firstType = _evaluateTypeInExpression(binaryExpression->getFirstNode());
                auto secondType = _evaluateTypeInExpression(binaryExpression->getSecondNode());

                if (firstType != secondType) {
                    Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                                   "Types in binary expression different!");

                    Exceptions::errorHandler.throw_();
                }

                return firstType;
            }
            case Parser::NodeType::VARIABLE_USING_NODE: {
                auto variableUsingExpression = std::reinterpret_pointer_cast<Parser::GS_VariableUsingNode>(node);

                return _context->getTableOfVariables()->getValueTypeByName(variableUsingExpression->getName());
            }
            default: {
                return Parser::ValueType::VOID;
            }
        }
    }

    GSVoid GS_SemanticPass::setup(Starter::GSContextPtr &context) {
        _context = context;
    }

    GSVoid GS_SemanticPass::visit(Parser::GS_RootNode *rootNode) {
        rootNode->getNode()->accept(this);
    }

    GSVoid GS_SemanticPass::visit(Parser::GS_BlockNode *blockNode) {
        auto nodes = blockNode->getNodes();

        for (auto &node : nodes) {
            node->accept(this);
        }
    }

    GSVoid GS_SemanticPass::visit(Parser::GS_ValueNode *valueNode) {}

    GSVoid GS_SemanticPass::visit(Parser::GS_UnaryNode *unaryNode) {}

    GSVoid GS_SemanticPass::visit(Parser::GS_BinaryNode *binaryNode) {}

    GSVoid GS_SemanticPass::visit(Parser::GS_AssignmentNode *assignmentNode) {}

    GSVoid GS_SemanticPass::visit(Parser::GS_VariableDeclarationNode *variableDeclarationNode) {}

    GSVoid GS_SemanticPass::visit(Parser::GS_VariableUsingNode *variableUsingNode) {}

}
