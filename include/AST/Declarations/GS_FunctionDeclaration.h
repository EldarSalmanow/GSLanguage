#ifndef GSLANGUAGE_GS_FUNCTIONDECLARATION_H
#define GSLANGUAGE_GS_FUNCTIONDECLARATION_H

#include <AST/GS_Declaration.h>
#include <AST/GS_Statement.h>

namespace GSLanguageCompiler::AST {

    /**
     * Declaring expression
     */
    class GS_Expression;

    /**
     * Class for function declarations in language
     */
    class GS_FunctionDeclaration : public GS_Declaration {
    public:

        /**
         * Constructor for function declaration
         * @param name Name
         * @param body Body
         * @param scope Scope
         */
        GS_FunctionDeclaration(UString name, GSStatementPtrArray body, GSScopePtr scope);

    public:

        /**
         * Creating function declaration ptr
         * @param name Name
         * @param body Body
         * @param scope Scope
         * @return Function declaration ptr
         */
        static SharedPtr<GS_FunctionDeclaration> Create(UString name, GSStatementPtrArray body, GSScopePtr scope);

        /**
         * Creating function declaration ptr
         * @param name Name
         * @param scope Scope
         * @return Function declaration ptr
         */
        static SharedPtr<GS_FunctionDeclaration> Create(UString name, GSScopePtr scope);

    public:

        /**
         * Creating new statement or expression in function scope and return it
         * @tparam T Type of statement or expression for creating
         * @tparam Args Argument types for creating statement or expression
         * @param args Arguments for creating statement or expression
         * @return Created statement or expression
         */
        template<typename T, typename... Args>
        inline auto CreateStatement(Args... args) {
            static_assert(std::is_base_of_v<GS_Statement, T> || std::is_base_of_v<GS_Expression, T>, "Element for creating must be a statement or expression!");

            return T::Create(args..., _functionScope);
        }

        /**
         * Adding statement to function body
         * @param statement Statement
         * @return
         */
        Void AddStatement(GSStatementPtr statement);

        /**
         * Creating and adding new statement to body and scope and return it
         * @tparam T Type of statement for creating
         * @tparam Args Argument types for creating statement
         * @param args Arguments for creating statement
         * @return Created statement
         */
        template<typename T, typename... Args>
        inline auto AddStatement(Args... args) {
            static_assert(std::is_base_of_v<GS_Statement, T>, "Element for creating must be a statement!");

            auto node = CreateStatement<T>(args...);

            AddStatement(node);

            return node;
        }

    public:

        /**
         * Getter for function name
         * @return Function name
         */
        LRef<UString> GetName();

        /**
         * Getter for function code
         * @return Function code
         */
        LRef<GSStatementPtrArray> GetBody();

        /**
         * Getter for function scope
         * @return Function scope
         */
        LRef<GSScopePtr> GetFunctionScope();

    public:

        /**
         * Getter for declaration type
         * @return Declaration type
         */
        DeclarationType GetDeclarationType() const override;

    private:

        /**
         * Function name
         */
        UString _name;

        /**
         * Function code
         */
        GSStatementPtrArray _body;

        /**
         * Function scope
         */
        GSScopePtr _functionScope;
    };

}

#endif //GSLANGUAGE_GS_FUNCTIONDECLARATION_H
