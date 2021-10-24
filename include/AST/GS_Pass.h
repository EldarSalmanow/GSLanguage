#ifndef GSLANGUAGE_GS_PASS_H
#define GSLANGUAGE_GS_PASS_H

#include <AST/GS_Declaration.h>
#include <AST/GS_Statement.h>
#include <AST/GS_Expression.h>

#include <AST/GS_Visitor.h>

namespace GSLanguageCompiler::AST {

    /**
     *
     */
    class GS_Pass {
    public:

        /**
         *
         * @param visitor
         */
        explicit GS_Pass(GSVisitorPtr visitor);

    public:

        virtual ~GS_Pass();

    public:

        /**
         *
         * @return
         */
        GSVisitorPtr getVisitor();

    public:

        /**
         *
         * @param declarations
         * @return
         */
        virtual Void runForDeclarations(GSDeclarationPtrArray &declarations);

        /**
         *
         * @param statements
         * @return
         */
        virtual Void runForStatements(GSStatementPtrArray &statements);

        /**
         *
         * @param expressions
         * @return
         */
        virtual Void runForExpressions(GSExpressionPtrArray &expressions);

    private:

        /**
         *
         */
        GSVisitorPtr _visitor;
    };

}

#endif //GSLANGUAGE_GS_PASS_H
