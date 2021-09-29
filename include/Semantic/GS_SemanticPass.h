#ifndef GSLANGUAGE_GS_SEMANTICPASS_H
#define GSLANGUAGE_GS_SEMANTICPASS_H

#include <Parser/Visitors/GS_Visitor.h>

#include <Exceptions/GS_ErrorHandler.h>

namespace GSLanguageCompiler::Parser {

    enum class NodeType;

    class GS_Node;

    typedef std::shared_ptr<GS_Node> GSNodePtr;

    enum class ValueType;

}

namespace GSLanguageCompiler::Semantic {

    extern std::vector<Parser::NodeType> expressionTypes;

    GSBool isExpression(const Parser::GSNodePtr &node);

    Parser::ValueType evaluateTypeInExpression(const Parser::GSNodePtr &node);

    class GS_SemanticPass : public Parser::GS_Visitor<GSVoid> {
    public:

        GSBool _isExpression(const Parser::GSNodePtr &node);

        Parser::ValueType _evaluateTypeInExpression(const Parser::GSNodePtr &node);

    public:

        GSVoid setup(Starter::GSContextPtr &context) override;

        GSVoid visit(Parser::GS_RootNode *rootNode) override;

        GSVoid visit(Parser::GS_BlockNode *blockNode) override;

        GSVoid visit(Parser::GS_ValueNode *valueNode) override;

        GSVoid visit(Parser::GS_UnaryNode *unaryNode) override;

        GSVoid visit(Parser::GS_BinaryNode *binaryNode) override;

        GSVoid visit(Parser::GS_AssignmentNode *assignmentNode) override;

        GSVoid visit(Parser::GS_VariableDeclarationNode *variableDeclarationNode) override;

        GSVoid visit(Parser::GS_VariableUsingNode *variableUsingNode) override;
    };

    typedef std::shared_ptr<GS_SemanticPass> GSSemanticPassPtr;

    typedef std::vector<GSSemanticPassPtr> GSSemanticPassPtrArray;

}

#endif //GSLANGUAGE_GS_SEMANTICPASS_H
