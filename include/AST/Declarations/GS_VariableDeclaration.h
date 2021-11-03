#ifndef GSLANGUAGE_GS_VARIABLEDECLARATION_H
#define GSLANGUAGE_GS_VARIABLEDECLARATION_H

#include <AST/GS_Declaration.h>
#include <AST/GS_Expression.h>

#include <AST/GS_Type.h>

namespace GSLanguageCompiler::AST {

    class GS_VariableDeclaration : public GS_Declaration {
    public:

        GS_VariableDeclaration(String name, GSTypePtr type, GSExpressionPtr expression);

    public:

        String getName();

        GSTypePtr getType();

        GSExpressionPtr getExpression();

    public:

        Void accept(GS_Visitor *visitor) override;

    public:

        DeclarationType getDeclarationType() override;

    private:

        String _name;

        GSTypePtr _type;

        GSExpressionPtr _expression;
    };

}

#endif //GSLANGUAGE_GS_VARIABLEDECLARATION_H
