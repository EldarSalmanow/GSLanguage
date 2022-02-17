#ifndef GSLANGUAGE_GS_TABLEOFSYMBOLS_H
#define GSLANGUAGE_GS_TABLEOFSYMBOLS_H

#include <AST/GS_Statement.h>
#include <AST/GS_Expression.h>

#include <AST/GS_Type.h>

namespace GSLanguageCompiler::Semantic {

    /**
     *
     */
    class GS_Symbol {
    public:

        /**
         *
         * @return
         */
        virtual Bool isVariable() const;

        /**
         *
         */
        virtual Bool isFunction() const;
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
    class GS_VariableSymbol : public GS_Symbol {
    public:

        /**
         *
         * @param name
         * @param type
         * @param expression
         */
        GS_VariableSymbol(UString name, AST::GSTypePtr type, AST::GSExpressionPtr expression);

    public:

        /**
         *
         * @return
         */
        UString getName() const;

        /**
         *
         * @return
         */
        LRef<AST::GSTypePtr> getType();

        /**
         *
         * @return
         */
        LRef<AST::GSExpressionPtr> getExpression();

    public:

        /**
         *
         * @return
         */
        Bool isVariable() const override;

    private:

        /**
         *
         */
        UString _name;

        /**
         *
         */
        AST::GSTypePtr _type;

        /**
         *
         */
        AST::GSExpressionPtr _expression;
    };

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
         * @return
         */
        UString getName() const;

        /**
         *
         * @return
         */
        LRef<AST::GSStatementPtrArray> getBody();

    public:

        /**
         *
         * @return
         */
        Bool isFunction() const override;

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
    class GS_TableOfSymbols {
    public:

        /**
         *
         */
        GS_TableOfSymbols();

    public:

        /**
         *
         * @param symbol
         * @return
         */
        Void addSymbol(GSSymbolPtr symbol);

        /**
         *
         * @param name
         * @param type
         * @param expression
         * @return
         */
        Void addVariable(UString name, AST::GSTypePtr type, AST::GSExpressionPtr expression);

        /**
         *
         * @param name
         * @param body
         * @return
         */
        Void addFunction(UString name, AST::GSStatementPtrArray body);

        /**
         *
         * @param name
         * @return
         */
        SharedPtr<GS_VariableSymbol> getVariable(UString name);

    private:

        /**
         *
         */
        GSSymbolPtrArray _symbols;
    };

    /**
     * Table of symbols ptr
     */
    using GSTableOfSymbolsPtr = SharedPtr<GS_TableOfSymbols>;

}

#endif //GSLANGUAGE_GS_TABLEOFSYMBOLS_H
