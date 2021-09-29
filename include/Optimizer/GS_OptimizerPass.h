#ifndef GSLANGUAGE_GS_OPTIMIZERPASS_H
#define GSLANGUAGE_GS_OPTIMIZERPASS_H

#include <memory>
#include <vector>

#include <Parser/Visitors/GS_Visitor.h>

namespace GSLanguageCompiler::Parser {

    class GS_Node;

    typedef std::shared_ptr<GS_Node> GSNodePtr;

}

namespace GSLanguageCompiler::Optimizer {

    class GS_OptimizerPass : public Parser::GS_Visitor<Parser::GSNodePtr> {
    public:

        GSVoid setup(Starter::GSContextPtr &context) override;

        Parser::GSNodePtr visit(Parser::GS_RootNode *rootNode) override;

        Parser::GSNodePtr visit(Parser::GS_BlockNode *blockNode) override;

        Parser::GSNodePtr visit(Parser::GS_ValueNode *valueNode) override;

        Parser::GSNodePtr visit(Parser::GS_UnaryNode *unaryNode) override;

        Parser::GSNodePtr visit(Parser::GS_BinaryNode *binaryNode) override;

        Parser::GSNodePtr visit(Parser::GS_AssignmentNode *assignmentNode) override;

        Parser::GSNodePtr visit(Parser::GS_VariableDeclarationNode *variableDeclarationNode) override;

        Parser::GSNodePtr visit(Parser::GS_VariableUsingNode *variableUsingNode) override;
    };

    typedef std::shared_ptr<GS_OptimizerPass> GSOptimizerPassPtr;

    typedef std::vector<GSOptimizerPassPtr> GSOptimizerPassPtrArray;

}

#endif //GSLANGUAGE_GS_OPTIMIZERPASS_H
