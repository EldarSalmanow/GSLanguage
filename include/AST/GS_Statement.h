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
        IfStatement,
        ForStatement,
        WhileStatement,
        ExpressionStatement
    };

    /**
     * Class for all language grammar statements
     */
    class GS_Statement : public GS_Node {
    public:

        /*
         *
         * GS_Statement PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for statement
         */
        GS_Statement();

    public:

        /*
         *
         * GS_Statement PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Is statement
         * @return Is statement
         */
        Bool IsStatement() const override;

    public:

        /*
         *
         * GS_Statement PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Getter for statement type
         * @return Statement type
         */
        virtual StatementType GetStatementType() const = 0;
    };

    /**
     * Statement ptr type
     */
    using GSStatementPtr = NodePtr<GS_Statement>;

    /**
     * Statement ptr array type
     */
    using GSStatementPtrArray = std::vector<GSStatementPtr>;

    /**
     * Casting to statement if node is statement
     * @param node Node
     * @return Statement or null
     */
    GSStatementPtr ToStatement(ConstLRef<GSNodePtr> node);

    /**
     * Declaring statements for cast function
     */
    class GS_VariableDeclarationStatement;
    class GS_AssignmentStatement;
    class GS_IfStatement;
    class GS_ForStatement;
    class GS_WhileStatement;
    class GS_ExpressionStatement;

    /**
     * Casting to StatementT if node is statement
     * @tparam StatementT Type of statement
     * @param node Node
     * @return Statement or null
     */
    template<typename StatementT>
    inline NodePtr<StatementT> ToStatement(ConstLRef<GSNodePtr> node) {
        static_assert(std::is_base_of_v<GS_Statement, StatementT>,
                      "Type for casting must be inherited from GS_Statement!");

        auto statement = ToStatement(node);

        if (!statement) {
            return nullptr;
        }

        auto statementType = statement->GetStatementType();

        switch (statementType) {
            case StatementType::VariableDeclarationStatement: {
                if constexpr (!std::is_same_v<GS_VariableDeclarationStatement, StatementT>) {
                    return nullptr;
                }

                break;
            }
            case StatementType::AssignmentStatement: {
                if constexpr (!std::is_same_v<GS_AssignmentStatement, StatementT>) {
                    return nullptr;
                }

                break;
            }
            case StatementType::IfStatement: {
                if constexpr (!std::is_same_v<GS_IfStatement, StatementT>) {
                    return nullptr;
                }

                break;
            }
            case StatementType::ForStatement: {
                if constexpr (!std::is_same_v<GS_ForStatement, StatementT>) {
                    return nullptr;
                }

                break;
            }
            case StatementType::WhileStatement: {
                if constexpr (!std::is_same_v<GS_WhileStatement, StatementT>) {
                    return nullptr;
                }

                break;
            }
            case StatementType::ExpressionStatement: {
                if constexpr (!std::is_same_v<GS_ExpressionStatement, StatementT>) {
                    return nullptr;
                }

                break;
            }
            default: {
                return nullptr;
            }
        }

        return std::reinterpret_pointer_cast<StatementT>(statement);
    }

}

#endif //GSLANGUAGE_GS_STATEMENT_H
