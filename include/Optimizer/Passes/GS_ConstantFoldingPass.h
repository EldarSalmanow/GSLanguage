#ifndef GSLANGUAGE_GS_CONSTANTFOLDINGPASS_H
#define GSLANGUAGE_GS_CONSTANTFOLDINGPASS_H

#include <AST/GS_Pass.h>

namespace GSLanguageCompiler::Optimizer {

    class GS_ConstantFoldingTransformer : public AST::GS_Transformer {
    public:

        AST::GSNodePtr TransformUnaryExpression(LRef<std::shared_ptr<AST::GS_UnaryExpression>> unaryExpression) override;

        AST::GSNodePtr TransformBinaryExpression(LRef<std::shared_ptr<AST::GS_BinaryExpression>> binaryExpression) override;
    };

    class GS_ConstantFoldingPass : public AST::GS_TransformPass<GS_ConstantFoldingTransformer> {};

    AST::GSPassPtr CreateConstantFoldingPass();

}

#endif //GSLANGUAGE_GS_CONSTANTFOLDINGPASS_H
