#ifndef GSLANGUAGE_GS_MATCHSTATEMENT_H
#define GSLANGUAGE_GS_MATCHSTATEMENT_H

#include <AST/GS_Statement.h>
#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /*
     *
     * match <expression> {
     *     <pattern> -> {
     *         <action>
     *     }
     *     ...
     * }
     *
     */

    class GS_MatchPattern {
    public:

        GS_MatchPattern(GSExpressionPtr pattern,
                        GSStatementPtrArray actions);

    public:



    private:

        GSExpressionPtr _pattern;

        GSStatementPtrArray _actions;
    };

    using GSMatchPatternArray = std::vector<GS_MatchPattern>;

    class GS_MatchStatement : public GS_Statement {
    public:

        GS_MatchStatement(GSExpressionPtr expression,
                          GSMatchPatternArray patterns);

    private:

        GSExpressionPtr _expression;

        GSMatchPatternArray _patterns;
    };

}

#endif //GSLANGUAGE_GS_MATCHSTATEMENT_H
