#ifndef GSLANGUAGE_GS_CONSTANTFOLDINGPASS_H
#define GSLANGUAGE_GS_CONSTANTFOLDINGPASS_H

#include <AST/GS_Pass.h>

namespace GSLanguageCompiler::Optimizer {

    /**
     * Transformer class for applying constant folding optimization on nodes
     */
    class GS_ConstantFoldingTransformer : public AST::GS_Transformer {
    public:

        /**
         * Transform unary expression
         *
         * Transformation rules:
         * --- - ( constant expression ) -> - constant expression
         *
         * @param unaryExpression Unary expression
         * @param context Context
         * @return Transformed unary expression
         */
        AST::GSNodePtr TransformUnaryExpression(AST::NodePtrLRef<AST::GS_UnaryExpression> unaryExpression,
                                                LRef<Driver::GSContextPtr> context) override;

        /**
         * Transform binary expression
         *
         * Transformation rules:
         * --- ( constant expression ) +|-|*|/ ( constant expression ) -> constant expression +|-|*|/ constant expression
         *
         * @param binaryExpression Binary expression
         * @param context Context
         * @return Transformed binary expression
         */
        AST::GSNodePtr TransformBinaryExpression(AST::NodePtrLRef<AST::GS_BinaryExpression> binaryExpression,
                                                 LRef<Driver::GSContextPtr> context) override;
    };

    /**
     * Pass class for run constant folding optimization transformer on nodes
     */
    class GS_ConstantFoldingPass : public AST::GS_TransformPass<GS_ConstantFoldingTransformer> {};

    /**
     * Creating constant folding optimization pass
     * @return Constant folding optimization pass
     */
    AST::GSPassPtr CreateConstantFoldingPass();

}

#endif //GSLANGUAGE_GS_CONSTANTFOLDINGPASS_H
