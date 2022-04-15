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
         */
        GS_Statement();

    public:

        /**
         * Is statement
         * @return Is statement
         */
        Bool IsStatement() const override;

    public:

        /**
         * Getter for statement type
         * @return Statement type
         */
        virtual StatementType GetStatementType() const = 0;
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

    /**
     * Casting to any type of statement if node is statement
     * @tparam T Type of statement
     * @param node Node
     * @return Statement or nullptr
     */
    template<typename T>
    SharedPtr<T> ToStatement(GSNodePtr node) {
        static_assert(std::is_base_of_v<GS_Statement, T>, "Type for casting must be inherited from GS_Statement!");

        auto statement = ToStatement(node);

        if (!statement) {
            return nullptr;
        }

        return std::reinterpret_pointer_cast<T>(statement);
    }

}

#endif //GSLANGUAGE_GS_STATEMENT_H
