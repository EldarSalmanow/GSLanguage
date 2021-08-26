#ifndef GSLANGUAGE_GS_OPTIMIZERPASS_H
#define GSLANGUAGE_GS_OPTIMIZERPASS_H

#include <memory>
#include <vector>

namespace GSLanguageCompiler::Parser {

    class GS_Node;

    typedef std::shared_ptr<GS_Node> GSNodePtr;

    typedef std::vector<GSNodePtr> GSNodePtrArray;

    class GS_RootNode;
    class GS_BlockNode;
    class GS_ValueNode;
    class GS_UnaryNode;
    class GS_BinaryNode;
    class GS_VariableNode;
    class GS_PrintNode;

}

namespace GSLanguageCompiler::Optimizer {

    class GS_OptimizerPass {
    public:

        virtual Parser::GSNodePtr visit(Parser::GS_RootNode *rootNode);

        virtual Parser::GSNodePtr visit(Parser::GS_BlockNode *blockNode);

        virtual Parser::GSNodePtr visit(Parser::GS_ValueNode *valueNode);

        virtual Parser::GSNodePtr visit(Parser::GS_UnaryNode *unaryNode);

        virtual Parser::GSNodePtr visit(Parser::GS_BinaryNode *binaryNode);

        virtual Parser::GSNodePtr visit(Parser::GS_VariableNode *variableNode);

        virtual Parser::GSNodePtr visit(Parser::GS_PrintNode *printNode);
    };

    typedef std::shared_ptr<GS_OptimizerPass> GSOptimizerPassPtr;

    typedef std::vector<GSOptimizerPassPtr> GSOptimizerPassPtrArray;

}

#endif //GSLANGUAGE_GS_OPTIMIZERPASS_H
