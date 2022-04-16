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
         */
        GS_FunctionDeclaration(UString name, GSStatementPtrArray body);

    public:

        /**
         * Creating function declaration ptr
         * @param name Name
         * @param body Body
         * @return Function declaration ptr
         */
        static SharedPtr<GS_FunctionDeclaration> Create(UString name, GSStatementPtrArray body);

        /**
         * Creating function declaration ptr
         * @param name Name
         * @return Function declaration ptr
         */
        static SharedPtr<GS_FunctionDeclaration> Create(UString name);

    public:

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
//        template<typename T, typename... Args>
//        inline auto AddStatement(Args... args) {
//            static_assert(std::is_base_of_v<GS_Statement, T>, "Type for creating must be inherited from GS_Statement!");
//
//            auto node = T::Create(args...);
//
//            AddStatement(node);
//
//            return node;
//        } TODO may be remove

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
    };

}

#endif //GSLANGUAGE_GS_FUNCTIONDECLARATION_H
