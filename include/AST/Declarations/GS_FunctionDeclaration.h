#ifndef GSLANGUAGE_GS_FUNCTIONDECLARATION_H
#define GSLANGUAGE_GS_FUNCTIONDECLARATION_H

#include <Semantic/GS_Type.h>

#include <AST/GS_Declaration.h>
#include <AST/GS_Statement.h>

#include <AST/GS_Qualifiers.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for containing function qualifiers
     */
    class GS_FunctionQualifiers {
    public:

        /**
         * Constructor for function qualifiers
         * @param externType Extern type
         */
        explicit GS_FunctionQualifiers(ExternType externType);

    public:

        /**
         * Creating function qualifiers
         * @param externType Extern type
         * @return Function qualifiers
         */
        static GS_FunctionQualifiers Create(ExternType externType);

        /**
         * Creating function qualifiers
         * @return Function qualifiers
         */
        static GS_FunctionQualifiers Create();

    public:

        /**
         * Has extern qualifier
         * @return Has extern qualifier
         */
        Bool IsExtern() const;

    public:

        /**
         * Getter for extern type
         * @return Extern type
         */
        ExternType GetExternType() const;

    private:

        /**
         * Extern type
         */
        ExternType _externType;
    };

    /**
     * CLass for containing information about function param
     */
    class GS_FunctionParam {
    public:

        /**
         * Constructor for function param
         * @param name Name
         * @param type Type
         */
        GS_FunctionParam(UString name,
                         Semantic::GSTypePtr type);

    public:

        /**
         * Creating function param
         * @param name Name
         * @param type Type
         * @return Function param
         */
        static GS_FunctionParam Create(UString name,
                                       Semantic::GSTypePtr type);

    public:

        /**
         * Getter for name
         * @return Name
         */
        ConstLRef<UString> GetName() const;

        /**
         * Getter for type
         * @return Type
         */
        ConstLRef<Semantic::GSTypePtr> GetType() const;

    private:

        /**
         * Name
         */
        UString _name;

        /**
         * Type
         */
        Semantic::GSTypePtr _type;
    };

    /**
     * Function param array type
     */
    using GSFunctionParamArray = std::vector<GS_FunctionParam>;

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
         * @param params Params
         * @param returnType Return type
         * @param qualifiers Qualifiers
         */
        GS_FunctionSignature(GSFunctionParamArray params,
                             Semantic::GSTypePtr returnType,
                             GS_FunctionQualifiers qualifiers);

    public:

        /*
         *
         * GS_FunctionSignature PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating function signature
         * @param params Params
         * @param returnType Return type
         * @param qualifiers Qualifiers
         * @return Function signature
         */
        static GS_FunctionSignature Create(GSFunctionParamArray params,
                                           Semantic::GSTypePtr returnType,
                                           GS_FunctionQualifiers qualifiers);

        /**
         * Creating function signature
         * @param params Params
         * @param returnType Return type
         * @return Function signature
         */
        static GS_FunctionSignature Create(GSFunctionParamArray params,
                                           Semantic::GSTypePtr returnType);

        /**
         * Creating function signature
         * @param params Params
         * @return Function signature
         */
        static GS_FunctionSignature Create(GSFunctionParamArray params);

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
         * Getter for params
         * @return Params
         */
        ConstLRef<GSFunctionParamArray> GetParams() const;

        /**
         * Getter for return type
         * @return Return type
         */
        ConstLRef<Semantic::GSTypePtr> GetReturnType() const;

        /**
         * Getter for qualifiers
         * @return Qualifiers
         */
        ConstLRef<GS_FunctionQualifiers> GetQualifiers() const;

    private:

        /*
         *
         * GS_FunctionSignature PRIVATE FIELDS
         *
         */

        /**
         * Params
         */
        GSFunctionParamArray _params;

        /**
         * Return type
         */
        Semantic::GSTypePtr _returnType;

        /**
         * Qualifiers
         */
        GS_FunctionQualifiers _qualifiers;
    };

    /**
     * Class for function declaration in language grammar
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
         * Creating and adding new statement to function body and return it
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
