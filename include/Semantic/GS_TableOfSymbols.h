#ifndef GSLANGUAGE_GS_TABLEOFSYMBOLS_H
#define GSLANGUAGE_GS_TABLEOFSYMBOLS_H

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

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Symbol();

    public:

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
    using GSSymbolPtr = std::shared_ptr<GS_Symbol>;

    /**
     * Symbol ptr array type
     */
    using GSSymbolPtrArray = std::vector<GSSymbolPtr>;

    /**
     * Class for functions symbols
     */
    class GS_FunctionSymbol : public GS_Symbol {
    public:

        /**
         * Constructor for function symbol
         * @param name Function name
         * @param signature Function signature
         */
        GS_FunctionSymbol(UString name, AST::GS_FunctionSignature signature);

    public:

        /**
         * Creating function symbol
         * @param name Function name
         * @param signature Function signature
         * @return Function symbol ptr
         */
        static std::shared_ptr<GS_FunctionSymbol> Create(UString name, AST::GS_FunctionSignature signature);

    public:

        /**
         * Getter for function name
         * @return Function name
         */
        UString GetName() const;

        /**
         * Getter for function signature
         * @return Function signature
         */
        AST::GS_FunctionSignature GetSignature() const;

    public:

        /**
         * Getter for symbol type
         * @return Symbol type
         */
        SymbolType GetSymbolType() const override;

    private:

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

        /**
         * Constructor for variable symbol
         * @param name Variable name
         * @param type Variable type
         */
        GS_VariableSymbol(UString name, GSTypePtr type);

    public:

        /**
         * Creating variable symbol
         * @param name Variable name
         * @param type Variable type
         * @return Variable symbol ptr
         */
        static std::shared_ptr<GS_VariableSymbol> Create(UString name, GSTypePtr type);

    public:

        /**
         * Getter for variable name
         * @return Variable name
         */
        UString GetName() const;

        /**
         * Getter for variable type
         * @return Variable type
         */
        GSTypePtr GetType() const;

    public:

        /**
         * Getter for symbol type
         * @return Symbol type
         */
        SymbolType GetSymbolType() const override;

    private:

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
     * Casting symbol to any type of symbol
     * @tparam T Type for symbol
     * @param symbol Symbol
     * @return Symbol or nullptr
     */
    template<typename T>
    inline SymbolPtr<T> ToSymbol(ConstLRef<GSSymbolPtr> symbol) {
        static_assert(std::is_base_of_v<GS_Symbol, T>, "Type for casting must be inherited from GS_Symbol!");

        switch (symbol->GetSymbolType()) {
            case SymbolType::Function:
                if constexpr (!std::is_same_v<GS_FunctionSymbol, T>) {
                    return nullptr;
                }

                break;
            case SymbolType::Variable:
                if constexpr (!std::is_same_v<GS_VariableSymbol, T>) {
                    return nullptr;
                }

                break;
        }

        return std::reinterpret_pointer_cast<T>(symbol);
    }

    /**
     * Class for containing all symbols in program
     */
    class GS_TableOfSymbols {
    public:

        /**
         * Constructor for table of symbols
         * @param symbols Symbols
         */
        explicit GS_TableOfSymbols(GSSymbolPtrArray symbols);

    public:

        /**
         * Creating table of symbols
         * @param symbols Symbols
         * @return Table of symbols ptr
         */
        static std::shared_ptr<GS_TableOfSymbols> Create(GSSymbolPtrArray symbols);

        /**
         * Creating table of symbols
         * @return Table of symbols ptr
         */
        static std::shared_ptr<GS_TableOfSymbols> Create();

    public:

        /**
         * Adding new symbol to table of symbols
         * @param symbol Symbol
         * @return
         */
        Void AddSymbol(GSSymbolPtr symbol);

        /**
         * Adding new function symbol to table of symbols
         * @param name Function name
         * @param signature Function signature
         * @return
         */
        Void AddFunction(UString name, AST::GS_FunctionSignature signature);

        /**
         * Adding new variable symbol to table of symbols
         * @param name Variable name
         * @param type Variable type
         * @return
         */
        Void AddVariable(UString name, GSTypePtr type);

        /**
         * Getting function symbol by name
         * @param name Function name
         * @return Function symbol
         */
        SymbolPtr<GS_FunctionSymbol> GetFunction(UString name) const;

        /**
         * Getting variable symbol by name
         * @param name Variable name
         * @return Variable symbol
         */
        SymbolPtr<GS_VariableSymbol> GetVariable(UString name) const;

    public:

        /**
         * Getter for symbols
         * @return Symbols
         */
        GSSymbolPtrArray GetSymbols() const;

    private:

        /**
         * Symbols
         */
        GSSymbolPtrArray _symbols;
    };

    /**
     * Table of symbols ptr
     */
    using GSTableOfSymbolsPtr = std::shared_ptr<GS_TableOfSymbols>;

}

#endif //GSLANGUAGE_GS_TABLEOFSYMBOLS_H
