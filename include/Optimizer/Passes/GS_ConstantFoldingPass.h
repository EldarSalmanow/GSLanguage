#ifndef GSLANGUAGE_GS_CONSTANTFOLDINGPASS_H
#define GSLANGUAGE_GS_CONSTANTFOLDINGPASS_H

#include <AST/GS_Pass.h>

namespace GSLanguageCompiler::Optimizer {

    /**
     * Folding unary expression
     * @param session Session
     * @param operation Unary operation
     * @param value Value
     * @return Folded value
     */
    AST::GSValuePtr FoldConstants(LRef<Driver::GS_Session> session,
                                  AST::UnaryOperation operation,
                                  ConstLRef<AST::GSValuePtr> value);

    /**
     * Folding binary expression
     * @param session Session
     * @param operation Binary operation
     * @param firstValue First value
     * @param secondValue Second value
     * @return Folded value
     */
    AST::GSValuePtr FoldConstants(LRef<Driver::GS_Session> session,
                                  AST::BinaryOperation operation,
                                  ConstLRef<AST::GSValuePtr> firstValue,
                                  ConstLRef<AST::GSValuePtr> secondValue);

    /**
     * Transformer class for applying constant folding optimization on nodes
     */
    class GS_ConstantFoldingTransformer : public AST::GS_Transformer {
    public:

        /*
         *
         * GS_ConstantFoldingTransformer PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Default constructor for constant folding transformer
         */
        GS_ConstantFoldingTransformer();

    public:

        /*
         *
         * GS_ConstantFoldingTransformer PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Transform unary expression
         *
         * Transformation rules:
         * --- - ( constant expression ) -> - constant expression
         *
         * @param session Session
         * @param unaryExpression Unary expression
         * @return Transformed unary expression
         */
        AST::GSNodePtr TransformUnaryExpression(LRef<Driver::GS_Session> session,
                                                AST::NodePtrLRef<AST::GS_UnaryExpression> unaryExpression) override;

        /**
         * Transform binary expression
         *
         * Transformation rules:
         * --- ( constant expression ) +|-|*|/ ( constant expression ) -> constant expression +|-|*|/ constant expression
         *
         * @param session Session
         * @param binaryExpression Binary expression
         * @return Transformed binary expression
         */
        AST::GSNodePtr TransformBinaryExpression(LRef<Driver::GS_Session> session,
                                                 AST::NodePtrLRef<AST::GS_BinaryExpression> binaryExpression) override;
    };

    /**
     * Pass class for run constant folding optimization transformer on nodes
     */
    class GS_ConstantFoldingPass : public AST::GS_TransformPass<GS_ConstantFoldingTransformer> {};

    /**
     * Creating constant folding optimization pass
     * @return Constant folding optimization pass ptr
     */
    AST::GSPassPtr CreateConstantFoldingPass();

}

#endif //GSLANGUAGE_GS_CONSTANTFOLDINGPASS_H
