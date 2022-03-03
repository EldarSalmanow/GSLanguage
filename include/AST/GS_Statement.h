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
         * Constructor for statement
         * @param scope Statement scope
         */
        explicit GS_Statement(GSScopePtr scope);

    public:

        /**
         * Is statement
         * @return Is statement
         */
        Bool isStatement() const override;

    public:

        /**
         * Getter for statement type
         * @return Statement type
         */
        virtual StatementType getStatementType() const = 0;
    };

    /**
     * Statement ptr type
     */
    using GSStatementPtr = SharedPtr<GS_Statement>;

    /**
     * Statement ptr array type
     */
    using GSStatementPtrArray = Vector<GSStatementPtr>;

    /**
     * Casting to statement if node is statement
     * @param node Node
     * @return Statement or nullptr
     */
    GSStatementPtr ToStatement(GSNodePtr node);

}

#endif //GSLANGUAGE_GS_STATEMENT_H
