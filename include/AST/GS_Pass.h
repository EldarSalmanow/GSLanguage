#ifndef GSLANGUAGE_GS_PASS_H
#define GSLANGUAGE_GS_PASS_H

#include <AST/GS_Visitor.h>

namespace GSLanguageCompiler::AST {

    /**
     * Base class for AST passes
     */
    class GS_Pass {
    public:

        /**
         * Constructor for GS_Pass
         * @param visitor Visitor
         */
        explicit GS_Pass(GSVisitorPtr visitor);

        /**
         * Constructor for GS_Pass
         * @param transformer Transformer
         */
        explicit GS_Pass(GSTransformerPtr transformer);

    public:

        /**
         * Run pass for nodes
         * @param nodes Nodes
         * @return Is success
         */
        virtual Bool run(GSNodePtrArray nodes);

        /**
         * Run pass for declarations
         * @param declarations Declarations
         * @return Is success
         */
        virtual Bool runForDeclarations(GSDeclarationPtrArray declarations);

        /**
         * Run pass for statements
         * @param statements Statements
         * @return Is success
         */
        virtual Bool runForStatements(GSStatementPtrArray statements);

        /**
         * Run pass for expressions
         * @param expressions Expressions
         * @return Is success
         */
        virtual Bool runForExpressions(GSExpressionPtrArray expressions);

    private:

        /**
         * Visitor ptr
         */
        GSVisitorPtr _visitor;

        /**
         * Transformer ptr
         */
        GSTransformerPtr _transformer;
    };

}

#endif //GSLANGUAGE_GS_PASS_H
