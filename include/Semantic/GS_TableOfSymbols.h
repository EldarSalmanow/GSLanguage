#ifndef GSLANGUAGE_GS_TABLEOFSYMBOLS_H
#define GSLANGUAGE_GS_TABLEOFSYMBOLS_H

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
        virtual Bool isVariable();
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
        GS_VariableSymbol(String name, AST::GSTypePtr type, AST::GSExpressionPtr expression);

    public:

        /**
         *
         * @return
         */
        String getName();

        /**
         *
         * @return
         */
        AST::GSTypePtr getType();

        /**
         *
         * @return
         */
        AST::GSExpressionPtr getExpression();

    public:

        /**
         *
         * @return
         */
        Bool isVariable() override;

    private:

        /**
         *
         */
        String _name;

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
        Void addVariable(String name, AST::GSTypePtr type, AST::GSExpressionPtr expression);

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
