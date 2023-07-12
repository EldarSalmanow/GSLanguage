#ifndef GSLANGUAGE_GS_RANGEEXPRESSION_H
#define GSLANGUAGE_GS_RANGEEXPRESSION_H

#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    class GS_RangeExpression : public GS_Expression {
    private:

        GSExpressionPtr _startExpression;

        GSExpressionPtr _endExpression;
    };

}

#endif //GSLANGUAGE_GS_RANGEEXPRESSION_H
