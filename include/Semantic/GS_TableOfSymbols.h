#ifndef GSLANGUAGE_GS_TABLEOFSYMBOLS_H
#define GSLANGUAGE_GS_TABLEOFSYMBOLS_H

#include <AST/GS_Statement.h>
#include <AST/GS_Expression.h>

#include <Semantic/GS_Type.h>

namespace GSLanguageCompiler::Semantic {

    /**
     *
     */
    class GS_Symbol {
    public:

        virtual ~GS_Symbol();

    public:

        /**
         *
         * @return
         */
        virtual Bool IsVariable() const;

        /**
         *
         */
        virtual Bool IsFunction() const;
    };

    /**
     * Symbol ptr type
     */
    using GSSymbolPtr = SharedPtr<GS_Symbol>;

    /**
     * Symbol ptr array type
     */
    using GSSymbolPtrArray = Vector<GSSymbolPtr>;

    /**
     *
     */
    class GS_FunctionSymbol : public GS_Symbol {
    public:

        /**
         *
         * @param name
         * @param body
         */
        GS_FunctionSymbol(UString name, AST::GSStatementPtrArray body);

    public:

        /**
         *
         * @param name
         * @param body
         * @return
         */
        static SharedPtr<GS_FunctionSymbol> Create(UString name, AST::GSStatementPtrArray body);

    public:

        /**
         *
         * @return
         */
        UString GetName() const;

        /**
         *
         * @return
         */
        LRef<AST::GSStatementPtrArray> GetBody();

    public:

        /**
         *
         * @return
         */
        Bool IsFunction() const override;

    private:

        /**
         *
         */
        UString _name;

        /**
         *
         */
        AST::GSStatementPtrArray _body;
    };

    /**
     *
     */
    class GS_VariableSymbol : public GS_Symbol {
    public:

        /**
         *
         * @param name
         * @param type
         * @param expression
         */
        GS_VariableSymbol(UString name, GSTypePtr type, AST::GSExpressionPtr expression);

    public:

        /**
         *
         * @param name
         * @param type
         * @param expression
         * @return
         */
        static SharedPtr<GS_VariableSymbol> Create(UString name, GSTypePtr type, AST::GSExpressionPtr expression);

    public:

        /**
         *
         * @return
         */
        UString GetName() const;

        /**
         *
         * @return
         */
        LRef<GSTypePtr> GetType();

        /**
         *
         * @return
         */
        LRef<AST::GSExpressionPtr> GetExpression();

    public:

        /**
         *
         * @return
         */
        Bool IsVariable() const override;

    private:

        /**
         *
         */
        UString _name;

        /**
         *
         */
        GSTypePtr _type;

        /**
         *
         */
        AST::GSExpressionPtr _expression;
    };

    /**
     *
     */
    class GS_TableOfSymbols {
    public:

        /**
         *
         */
        GS_TableOfSymbols();

    public:

        /**
         *
         * @return
         */
        static SharedPtr<GS_TableOfSymbols> Create();

    public:

        /**
         *
         * @param name
         * @param body
         * @return
         */
        Void AddFunction(UString name, AST::GSStatementPtrArray body);

        /**
         *
         * @param name
         * @param type
         * @param expression
         * @return
         */
        Void AddVariable(UString name, GSTypePtr type, AST::GSExpressionPtr expression);

        /**
         *
         * @param name
         * @return
         */
        SharedPtr<GS_FunctionSymbol> FindFunction(UString name);

        /**
         *
         * @param name
         * @return
         */
        SharedPtr<GS_VariableSymbol> FindVariable(UString name);

    public:

        /**
         *
         * @return
         */
        Vector<SharedPtr<GS_FunctionSymbol>> GetFunctions() const;

        /**
         *
         * @return
         */
        Vector<SharedPtr<GS_VariableSymbol>> GetVariables() const;

    private:

        /**
         *
         */
        Vector<SharedPtr<GS_FunctionSymbol>> _functions;

        /**
         *
         */
        Vector<SharedPtr<GS_VariableSymbol>> _variables;
    };

    /**
     * Table of symbols ptr
     */
    using GSTableOfSymbolsPtr = SharedPtr<GS_TableOfSymbols>;

}

#endif //GSLANGUAGE_GS_TABLEOFSYMBOLS_H
