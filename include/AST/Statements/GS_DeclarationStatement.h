#ifndef GSLANGUAGE_GS_DECLARATIONSTATEMENT_H
#define GSLANGUAGE_GS_DECLARATIONSTATEMENT_H

#include <AST/GS_Declaration.h>
#include <AST/GS_Statement.h>

namespace GSLanguageCompiler::AST {

    class GS_DeclarationStatement : public GS_Statement {
    public:

        explicit GS_DeclarationStatement(GSStatementPtr &statement);

    public:

        GSStatementPtr getStatement();

    public:

        Void accept(GS_Visitor *visitor) override;

    public:

        StatementType getStatementType() override;

    private:

        GSStatementPtr _statement;
    };

}

#endif //GSLANGUAGE_GS_DECLARATIONSTATEMENT_H
