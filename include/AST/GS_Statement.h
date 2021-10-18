#ifndef GSLANGUAGE_GS_STATEMENT_H
#define GSLANGUAGE_GS_STATEMENT_H

#include <AST/GS_Node.h>

namespace GSLanguageCompiler::AST {

    /**
     * Statement type
     */
    enum class StatementType {
        VariableDeclarationStatement,
        AssignmentStatement,
        ExpressionStatement
    };

    /**
     * Class for all language grammar statements
     */
    class GS_Statement : public GS_Node {
    public:

        /**
         * Default constructor for GS_Statement
         */
        GS_Statement();

    public:

        /**
         * Is statement
         * @return Is statement
         */
        Bool isStatement() override;

    public:

        /**
         * Getter for statement type
         * @return Statement type
         */
        virtual StatementType getStatementType() = 0;
    };

    /**
     * Statement ptr type
     */
    using GSStatementPtr = SharedPtr<GS_Statement>;

    /**
     * Statement ptr array type
     */
    using GSStatementPtrArray = Vector<GSStatementPtr>;

}

#endif //GSLANGUAGE_GS_STATEMENT_H
