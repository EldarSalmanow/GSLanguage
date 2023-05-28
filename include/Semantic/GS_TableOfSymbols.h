#ifndef GSLANGUAGE_GS_TABLEOFSYMBOLS_H
#define GSLANGUAGE_GS_TABLEOFSYMBOLS_H

#include <optional>

#include <AST/Declarations/GS_FunctionDeclaration.h>

#include <AST/Statements/GS_VariableDeclarationStatement.h>

#include <Semantic/GS_Type.h>

namespace GSLanguageCompiler::Semantic {

    /**
     * Symbol type
     */
    enum class SymbolType {
        Function,
        Variable
    };

    /**
     * Base class for all symbols in table of symbols
     */
    class GS_Symbol {
    public:

        /*
         *
         * GS_Symbol PUBLIC DESTRUCTORS
         *
         */

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Symbol();

    public:

        /*
         *
         * GS_Symbol PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Getter for symbol type
         * @return Symbol type
         */
        virtual SymbolType GetSymbolType() const = 0;
    };

    /**
     * Custom symbol ptr type for any symbol
     */
    template<typename T>
    using SymbolPtr = std::shared_ptr<T>;

    /**
     * Custom symbol ptr array type for any symbol
     */
    template<typename T>
    using SymbolPtrArray = std::vector<SymbolPtr<T>>;

    /**
     * Symbol ptr type
     */
    using GSSymbolPtr = SymbolPtr<GS_Symbol>;

    /**
     * Symbol ptr array type
     */
    using GSSymbolPtrArray = std::vector<GSSymbolPtr>;

    /**
     * Class for functions symbols
     */
    class GS_FunctionSymbol : public GS_Symbol {
    public:

        /*
         *
         * GS_FunctionSymbol PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for function symbol
         * @param name Function name
         * @param signature Function signature
         */
        GS_FunctionSymbol(UString name,
                          AST::GS_FunctionSignature signature);

    public:

        /*
         *
         * GS_FunctionSymbol PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating function symbol
         * @param name Function name
         * @param signature Function signature
         * @return Function symbol ptr
         */
        static std::shared_ptr<GS_FunctionSymbol> Create(UString name,
                                                         AST::GS_FunctionSignature signature);

    public:

        /*
         *
         * GS_FunctionSymbol PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for function name
         * @return Function name
         */
        ConstLRef<UString> GetName() const;

        /**
         * Getter for function signature
         * @return Function signature
         */
        ConstLRef<AST::GS_FunctionSignature> GetSignature() const;

    public:

        /*
         *
         * GS_FunctionSymbol PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for symbol type
         * @return Symbol type
         */
        SymbolType GetSymbolType() const override;

    private:

        /*
         *
         * GS_FunctionSymbol PRIVATE FIELDS
         *
         */

        /**
         * Function name
         */
        UString _name;

        /**
         * Function signature
         */
        AST::GS_FunctionSignature _signature;
    };

    /**
     * Class for variable symbols
     */
    class GS_VariableSymbol : public GS_Symbol {
    public:

        /*
         *
         * GS_VariableSymbol PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for variable symbol
         * @param name Variable name
         * @param type Variable type
         */
        GS_VariableSymbol(UString name,
                          GSTypePtr type);

    public:

        /*
         *
         * GS_VariableSymbol PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating variable symbol
         * @param name Variable name
         * @param type Variable type
         * @return Variable symbol ptr
         */
        static std::shared_ptr<GS_VariableSymbol> Create(UString name,
                                                         GSTypePtr type);

    public:

        /*
         *
         * GS_VariableSymbol PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for variable name
         * @return Variable name
         */
        ConstLRef<UString> GetName() const;

        /**
         * Getter for variable type
         * @return Variable type
         */
        ConstLRef<GSTypePtr> GetType() const;

    public:

        /*
         *
         * GS_VariableSymbol PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for symbol type
         * @return Symbol type
         */
        SymbolType GetSymbolType() const override;

    private:

        /*
         *
         * GS_VariableSymbol PRIVATE FIELDS
         *
         */

        /**
         * Variable name
         */
        UString _name;

        /**
         * Variable type
         */
        GSTypePtr _type;
    };

    /**
     * Casting symbol to SymbolT
     * @tparam SymbolT Type of symbol
     * @param symbol Symbol
     * @return Symbol or null
     */
    template<typename SymbolT>
    inline SymbolPtr<SymbolT> ToSymbol(ConstLRef<GSSymbolPtr> symbol) {
        static_assert(std::is_base_of_v<GS_Symbol, SymbolT>,
                      "Type for casting must be inherited from GS_Symbol!");

        auto symbolType = symbol->GetSymbolType();

        switch (symbolType) {
            case SymbolType::Function: {
                if constexpr (!std::is_same_v<GS_FunctionSymbol, SymbolT>) {
                    return nullptr;
                }

                break;
            }
            case SymbolType::Variable: {
                if constexpr (!std::is_same_v<GS_VariableSymbol, SymbolT>) {
                    return nullptr;
                }

                break;
            }
            default: {
                return nullptr;
            }
        }

        return std::reinterpret_pointer_cast<SymbolT>(symbol);
    }

    /**
     * Class for containing all symbols in program
     */
    class GS_TableOfSymbols {
    public:

        /*
         *
         * GS_TableOfSymbols PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for table of symbols
         * @param symbols Symbols
         */
        explicit GS_TableOfSymbols(GSSymbolPtrArray symbols);

    public:

        /*
         *
         * GS_TableOfSymbols PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating table of symbols
         * @param symbols Symbols
         * @return Table of symbols ptr
         */
        static std::unique_ptr<GS_TableOfSymbols> Create(GSSymbolPtrArray symbols);

        /**
         * Creating table of symbols
         * @return Table of symbols ptr
         */
        static std::unique_ptr<GS_TableOfSymbols> Create();

    public:

        /*
         *
         * GS_TableOfSymbols PUBLIC METHODS
         *
         */

        /**
         * Adding new symbol to table of symbols
         * @param symbol Symbol
         * @return Symbol
         */
        ConstLRef<GSSymbolPtr> AddSymbol(GSSymbolPtr symbol);

        /**
         * Adding new function symbol to table of symbols
         * @param name Function name
         * @param signature Function signature
         * @return Function symbol
         */
        ConstLRef<GS_FunctionSymbol> AddFunction(UString name,
                                                 AST::GS_FunctionSignature signature);

        /**
         * Adding new variable symbol to table of symbols
         * @param name Variable name
         * @param type Variable type
         * @return Variable symbol
         */
        ConstLRef<GS_VariableSymbol> AddVariable(UString name,
                                                 GSTypePtr type);

        /**
         * Getting function symbol by name
         * @param name Function name
         * @return Function symbol or null
         */
        std::optional<GS_FunctionSymbol> GetFunction(UString name) const;

        /**
         * Getting variable symbol by name
         * @param name Variable name
         * @return Variable symbol or null
         */
        std::optional<GS_VariableSymbol> GetVariable(UString name) const;

    public:

        /*
         *
         * GS_TableOfSymbols PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for symbols
         * @return Symbols
         */
        ConstLRef<GSSymbolPtrArray> GetSymbols() const;

    private:

        /*
         *
         * GS_TableOfSymbols PRIVATE FIELDS
         *
         */

        /**
         * Symbols
         */
        GSSymbolPtrArray _symbols;
    };

    /**
     * Table of symbols ptr
     */
    using GSTableOfSymbolsPtr = std::unique_ptr<GS_TableOfSymbols>;

}

#endif //GSLANGUAGE_GS_TABLEOFSYMBOLS_H
