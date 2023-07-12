#ifndef GSLANGUAGE_GS_INDEXEXPRESSION_H
#define GSLANGUAGE_GS_INDEXEXPRESSION_H

#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    class GS_IndexExpression : public GS_Expression {
    public:

        GS_IndexExpression(GSExpressionPtr value,
                           GSExpressionPtr index);

    public:

        static std::shared_ptr<GS_IndexExpression> Create(GSExpressionPtr value,
                                                          GSExpressionPtr index);

    public:

        LRef<GSExpressionPtr> GetValue();

        LRef<GSExpressionPtr> GetIndex();

    public:

        ExpressionType GetExpressionType() const override;

    private:

        GSExpressionPtr _value;

        GSExpressionPtr _index;
    };

}

#endif //GSLANGUAGE_GS_INDEXEXPRESSION_H
