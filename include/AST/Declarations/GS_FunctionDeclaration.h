#ifndef GSLANGUAGE_GS_FUNCTIONDECLARATION_H
#define GSLANGUAGE_GS_FUNCTIONDECLARATION_H

#include <Semantic/GS_Type.h>

#include <AST/GS_Declaration.h>
#include <AST/GS_Statement.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for containing information about function signature
     */
    class GS_FunctionSignature {
    public:

        /*
         *
         * GS_FunctionSignature PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for function signature
         * @param paramTypes Param types
         * @param returnType Return type
         */
        GS_FunctionSignature(Semantic::GSTypePtrArray paramTypes,
                             Semantic::GSTypePtr returnType);

    public:

        /*
         *
         * GS_FunctionSignature PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating function signature
         * @param paramTypes Param types
         * @param returnType Return type
         * @return Function signature
         */
        static GS_FunctionSignature Create(Semantic::GSTypePtrArray paramTypes,
                                           Semantic::GSTypePtr returnType);

        /**
         * Creating function signature
         * @param paramTypes Param types
         * @return Function signature
         */
        static GS_FunctionSignature Create(Semantic::GSTypePtrArray paramTypes);

        /**
         * Creating function signature
         * @param returnType Return type
         * @return Function signature
         */
        static GS_FunctionSignature Create(Semantic::GSTypePtr returnType);

        /**
         * Creating function signature
         * @return Function signature
         */
        static GS_FunctionSignature Create();

    public:

        /*
         *
         * GS_FunctionSignature PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for param types
         * @return Param types
         */
        ConstLRef<Semantic::GSTypePtrArray> GetParamTypes() const;

        /**
         * Getter for return type
         * @return Return type
         */
        ConstLRef<Semantic::GSTypePtr> GetReturnType() const;

    private:

        /*
         *
         * GS_FunctionSignature PRIVATE FIELDS
         *
         */

        /**
         * Param types
         */
        Semantic::GSTypePtrArray _paramTypes;

        /**
         * Return type
         */
        Semantic::GSTypePtr _returnType;
    };

    /**
     * Class for function declarations in language
     */
    class GS_FunctionDeclaration : public GS_Declaration {
    public:

        /*
         *
         * GS_FunctionDeclaration PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for function declaration
         * @param name Name
         * @param signature Signature
         * @param body Body
         */
        GS_FunctionDeclaration(UString name,
                               GS_FunctionSignature signature,
                               GSStatementPtrArray body);

    public:

        /*
         *
         * GS_FunctionDeclaration PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating function declaration
         * @param name Name
         * @param signature Signature
         * @param body Body
         * @return Function declaration ptr
         */
        static std::shared_ptr<GS_FunctionDeclaration> Create(UString name,
                                                              GS_FunctionSignature signature,
                                                              GSStatementPtrArray body);

        /**
         * Creating function declaration
         * @param name Name
         * @param signature Signature
         * @return Function declaration ptr
         */
        static std::shared_ptr<GS_FunctionDeclaration> Create(UString name,
                                                              GS_FunctionSignature signature);

        /**
         * Creating function declaration
         * @param name Name
         * @param body Body
         * @return Function declaration ptr
         */
        static std::shared_ptr<GS_FunctionDeclaration> Create(UString name,
                                                              GSStatementPtrArray body);

        /**
         * Creating function declaration
         * @param name Name
         * @return Function declaration ptr
         */
        static std::shared_ptr<GS_FunctionDeclaration> Create(UString name);

    public:

        /*
         *
         * GS_FunctionDeclaration PUBLIC METHODS
         *
         */

        /**
         * Adding statement to function body
         * @param statement Statement
         * @return Statement
         */
        LRef<GSStatementPtr> AddStatement(GSStatementPtr statement);

        /**
         * Creating and adding new statement to body and return it
         * @tparam StatementT Type of statement for creating
         * @tparam StatementArgs Argument types for creating statement
         * @param args Arguments for creating statement
         * @return Created statement
         */
        template<typename StatementT,
                 typename... StatementArgs>
        inline auto AddStatement(StatementArgs... args) {
            static_assert(std::is_base_of_v<GS_Statement, StatementT>,
                          "Type for creating must be inherited from GS_Statement!");

            auto statement = StatementT::Create(args...);

            auto statementRef = AddStatement(statement);

            return statementRef;
        }

    public:

        /*
         *
         * GS_FunctionDeclaration PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for function name
         * @return Function name
         */
        LRef<UString> GetName();

        /**
         * Getter for function signature
         * @return Function signature
         */
        LRef<GS_FunctionSignature> GetSignature();

        /**
         * Getter for function code
         * @return Function code
         */
        LRef<GSStatementPtrArray> GetBody();

    public:

        /*
         *
         * GS_FunctionDeclaration PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for declaration type
         * @return Declaration type
         */
        DeclarationType GetDeclarationType() const override;

    private:

        /*
         *
         * GS_FunctionDeclaration PRIVATE FIELDS
         *
         */

        /**
         * Function name
         */
        UString _name;

        /**
         * Function signature
         */
        GS_FunctionSignature _signature;

        /**
         * Function code
         */
        GSStatementPtrArray _body;
    };

}

#endif //GSLANGUAGE_GS_FUNCTIONDECLARATION_H
