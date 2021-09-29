#ifndef GSLANGUAGE_GS_CONSTANTFOLDINGPASS_H
#define GSLANGUAGE_GS_CONSTANTFOLDINGPASS_H

#include <Optimizer/GS_OptimizerPass.h>

namespace GSLanguageCompiler::Optimizer {

    class GS_ConstantFoldingPass : public GS_OptimizerPass {
    public:

        GS_ConstantFoldingPass();

    public:

        Parser::GSNodePtr visit(Parser::GS_UnaryNode *unaryNode) override;

        Parser::GSNodePtr visit(Parser::GS_BinaryNode *binaryNode) override;

        Parser::GSNodePtr visit(Parser::GS_AssignmentNode *assignmentNode) override;
    };

}

#endif //GSLANGUAGE_GS_CONSTANTFOLDINGPASS_H
