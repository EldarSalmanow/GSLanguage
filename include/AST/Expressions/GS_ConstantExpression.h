#ifndef GSLANGUAGE_GS_CONSTANTEXPRESSION_H
#define GSLANGUAGE_GS_CONSTANTEXPRESSION_H

#include <any>

#include <Semantic/GS_Type.h>

#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Base class for values
     */
    class GS_Value {
    public:

        /**
         * Constructor for value
         * @param type Type ptr
         */
        explicit GS_Value(Semantic::GSTypePtr type);

    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Value();

    public:

        /**
         * Creating value ptr
         * @param type Type ptr
         * @return Value ptr
         */
        static std::shared_ptr<GS_Value> Create(Semantic::GSTypePtr type);

    public:

        /**
         * Getter for type ptr
         * @return Type ptr
         */
        Semantic::GSTypePtr GetType() const;

    public:

        /**
         * Is literal value
         * @return Is literal value
         */
        virtual Bool IsLiteralValue();

    private:

        /**
         * Type ptr
         */
        Semantic::GSTypePtr _type;
    };

    /**
     * Custom value ptr type for any value
     */
    template<typename T>
    using ValuePtr = std::shared_ptr<T>;

    /**
     * Custom value ptr array type for any value
     */
    template<typename T>
    using ValuePtrArray = std::vector<ValuePtr<T>>;

    /**
     * Value ptr type
     */
    using GSValuePtr = std::shared_ptr<GS_Value>;

    /**
     * Value ptr array type
     */
    using GSValuePtrArray = std::vector<GSValuePtr>;

    /**
     * Class for literal values
     */
    class GS_LiteralValue : public GS_Value {
    public:

        /**
         * Constructor for value
         * @tparam T Type of value
         * @param data Value
         * @param type Type ptr
         */
        template<typename T>
        GS_LiteralValue(T value, Semantic::GSTypePtr type)
                : _value(std::move(value)), GS_Value(std::move(type)) {}

    public:

        /**
         * Creating value ptr
         * @tparam T Type of value
         * @param value Value
         * @param type Type ptr
         * @return Value ptr
         */
        template<typename T>
        static std::shared_ptr<GS_Value> Create(T value, Semantic::GSTypePtr type) {
            return std::make_shared<GS_Value>(std::move(value), std::move(type));
        }

    public:

        /**
         * Getter for data value
         * @tparam T Type for getting
         * @return Value
         */
        template<typename T>
        T GetValueWithCast() const {
            return std::any_cast<T>(GetValue());
        }

    public:

        /**
         * Getter for value
         * @return Value
         */
        std::any GetValue() const;

    public:

        /**
         * Is literal value
         * @return Is literal value
         */
        Bool IsLiteralValue() override;

    private:

        /**
         * Container for value
         */
        std::any _value;
    };

    /**
     * Char value
     */
    class GS_CharValue : public GS_LiteralValue {
    public:

        /**
         * Constructor for Char value
         * @param symbol Char value
         */
        explicit GS_CharValue(USymbol symbol);

    public:

        /**
         * Creating Char value
         * @param symbol Char value
         * @return Char value ptr
         */
        static std::shared_ptr<GS_CharValue> Create(USymbol symbol);

    public:

        /**
         * Getter for Char value
         * @return Char value
         */
        USymbol GetCharValue() const;
    };

    // add (u)integer value ?

    /**
     * I8 value
     */
    class GS_I8Value : public GS_LiteralValue {
    public:

        /**
         * Constructor for I8 value
         * @param value I8 value
         */
        explicit GS_I8Value(I8 value);

    public:

        /**
         * Creating I8 value
         * @param value I8 value
         * @return I8 value ptr
         */
        static std::shared_ptr<GS_I8Value> Create(I8 value);

    public:

        /**
         * Getter for I8 value
         * @return I8 value
         */
        I8 GetI8Value() const;
    };

    /**
     * I16 value
     */
    class GS_I16Value : public GS_LiteralValue {
    public:

        /**
         * Constructor for I16 value
         * @param value I16 value
         */
        explicit GS_I16Value(I16 value);

    public:

        /**
         * Creating I16 value
         * @param value I16 value
         * @return I16 value ptr
         */
        static std::shared_ptr<GS_I16Value> Create(I16 value);

    public:

        /**
         * Getter for I16 value
         * @return I16 value
         */
        I16 GetI16Value() const;
    };

    /**
     * I32 value
     */
    class GS_I32Value : public GS_LiteralValue {
    public:

        /**
         * Constructor for I32 value
         * @param value I32 value
         */
        explicit GS_I32Value(I32 value);

    public:

        /**
         * Creating I32 value
         * @param value I32 value
         * @return I32 value ptr
         */
        static std::shared_ptr<GS_I32Value> Create(I32 value);

    public:

        /**
         * Getter for I32 value
         * @return I32 value
         */
        I32 GetI32Value() const;
    };

    /**
     * I64 value
     */
    class GS_I64Value : public GS_LiteralValue {
    public:

        /**
         * Constructor for I64 value
         * @param value I64 value
         */
        explicit GS_I64Value(I64 value);

    public:

        /**
         * Creating I64 value
         * @param value I64 value
         * @return I64 value ptr
         */
        static std::shared_ptr<GS_I64Value> Create(I64 value);

    public:

        /**
         * Getter for I64 value
         * @return I64 value
         */
        I64 GetI64Value() const;
    };

    /**
     * U8 value
     */
    class GS_U8Value : public GS_LiteralValue {
    public:

        /**
         * Constructor for U8 value
         * @param value U8 value
         */
        explicit GS_U8Value(U8 value);

    public:

        /**
         * Creating U8 value
         * @param value U8 value
         * @return U8 value ptr
         */
        static std::shared_ptr<GS_U8Value> Create(U8 value);

    public:

        /**
         * Getter for U8 value
         * @return U8 value
         */
        U8 GetU8Value() const;
    };

    /**
     * U16 value
     */
    class GS_U16Value : public GS_LiteralValue {
    public:

        /**
         * Constructor for U16 value
         * @param value U16 value
         */
        explicit GS_U16Value(U16 value);

    public:

        /**
         * Creating U16 value
         * @param value U16 value
         * @return U16 value ptr
         */
        static std::shared_ptr<GS_U16Value> Create(U16 value);

    public:

        /**
         * Getter for U16 value
         * @return U16 value
         */
        U16 GetU16Value() const;
    };

    /**
     * U32 value
     */
    class GS_U32Value : public GS_LiteralValue {
    public:

        /**
         * Constructor for U32 value
         * @param value U32 value
         */
        explicit GS_U32Value(U32 value);

    public:

        /**
         * Creating U32 value
         * @param value U32 value
         * @return U32 value ptr
         */
        static std::shared_ptr<GS_U32Value> Create(U32 value);

    public:

        /**
         * Getter for U32 value
         * @return U32 value
         */
        U32 GetU32Value() const;
    };

    /**
     * U64 value
     */
    class GS_U64Value : public GS_LiteralValue {
    public:

        /**
         * Constructor for U64 value
         * @param value U64 value
         */
        explicit GS_U64Value(U64 value);

    public:

        /**
         * Creating U64 value
         * @param value U64 value
         * @return U64 value ptr
         */
        static std::shared_ptr<GS_U64Value> Create(U64 value);

    public:

        /**
         * Getter for U64 value
         * @return U64 value
         */
        U64 GetU64Value() const;
    };

    /**
     * String value
     */
    class GS_StringValue : public GS_LiteralValue {
    public:

        /**
         * Constructor for String value
         * @param value String value
         */
        explicit GS_StringValue(UString value);

    public:

        /**
         * Creating String value
         * @param value String value
         * @return String value ptr
         */
        static std::shared_ptr<GS_StringValue> Create(UString value);

    public:

        /**
         * Getter for String value
         * @return String value
         */
        UString GetStringValue() const;
    };

    /**
     * Casting any value ptr to concrete value ptr
     * @tparam T Type of value
     * @param value Any value ptr
     * @return Concrete value ptr or nullptr
     */
    template<typename T>
    inline Semantic::TypePtr<T> ToValue(GSValuePtr value) {
        static_assert(std::is_base_of_v<GS_Value, T>, "Type for casting must be inherited from GS_Value!");

        // todo may be optimized

        auto type = value->GetType();
        auto typeType = type->GetType();

        if constexpr (std::is_same_v<GS_CharValue, T>) {
            if (typeType == Semantic::TypeType::Char) {
                return std::reinterpret_pointer_cast<GS_CharValue>(value);
            }

            return nullptr;
        }

        if constexpr (std::is_same_v<GS_I8Value, T>) {
            if (typeType == Semantic::TypeType::Integer) {
                auto integerType = std::reinterpret_pointer_cast<Semantic::GS_IntegerType>(type);
                auto integerTypeType = integerType->GetIntegerType();

                if (integerTypeType == Semantic::IntegerType::I8) {
                    return std::reinterpret_pointer_cast<GS_I8Value>(value);
                }
            }

            return nullptr;
        }

        if constexpr (std::is_same_v<GS_I16Value, T>) {
            if (typeType == Semantic::TypeType::Integer) {
                auto integerType = std::reinterpret_pointer_cast<Semantic::GS_IntegerType>(type);
                auto integerTypeType = integerType->GetIntegerType();

                if (integerTypeType == Semantic::IntegerType::I16) {
                    return std::reinterpret_pointer_cast<GS_I16Value>(value);
                }
            }

            return nullptr;
        }

        if constexpr (std::is_same_v<GS_I32Value, T>) {
            if (typeType == Semantic::TypeType::Integer) {
                auto integerType = std::reinterpret_pointer_cast<Semantic::GS_IntegerType>(type);
                auto integerTypeType = integerType->GetIntegerType();

                if (integerTypeType == Semantic::IntegerType::I32) {
                    return std::reinterpret_pointer_cast<GS_I32Value>(value);
                }
            }

            return nullptr;
        }

        if constexpr (std::is_same_v<GS_I64Value, T>) {
            if (typeType == Semantic::TypeType::Integer) {
                auto integerType = std::reinterpret_pointer_cast<Semantic::GS_IntegerType>(type);
                auto integerTypeType = integerType->GetIntegerType();

                if (integerTypeType == Semantic::IntegerType::I64) {
                    return std::reinterpret_pointer_cast<GS_I64Value>(value);
                }
            }

            return nullptr;
        }

        if constexpr (std::is_same_v<GS_U8Value, T>) {
            if (typeType == Semantic::TypeType::UInteger) {
                auto uIntegerType = std::reinterpret_pointer_cast<Semantic::GS_UIntegerType>(type);
                auto uIntegerTypeType = uIntegerType->GetUIntegerType();

                if (uIntegerTypeType == Semantic::UIntegerType::U8) {
                    return std::reinterpret_pointer_cast<GS_U8Value>(value);
                }
            }

            return nullptr;
        }

        if constexpr (std::is_same_v<GS_U16Value, T>) {
            if (typeType == Semantic::TypeType::UInteger) {
                auto uIntegerType = std::reinterpret_pointer_cast<Semantic::GS_UIntegerType>(type);
                auto uIntegerTypeType = uIntegerType->GetUIntegerType();

                if (uIntegerTypeType == Semantic::UIntegerType::U16) {
                    return std::reinterpret_pointer_cast<GS_U16Value>(value);
                }
            }

            return nullptr;
        }

        if constexpr (std::is_same_v<GS_U32Value, T>) {
            if (typeType == Semantic::TypeType::UInteger) {
                auto uIntegerType = std::reinterpret_pointer_cast<Semantic::GS_UIntegerType>(type);
                auto uIntegerTypeType = uIntegerType->GetUIntegerType();

                if (uIntegerTypeType == Semantic::UIntegerType::U32) {
                    return std::reinterpret_pointer_cast<GS_U8Value>(value);
                }
            }

            return nullptr;
        }

        if constexpr (std::is_same_v<GS_U64Value, T>) {
            if (typeType == Semantic::TypeType::UInteger) {
                auto uIntegerType = std::reinterpret_pointer_cast<Semantic::GS_UIntegerType>(type);
                auto uIntegerTypeType = uIntegerType->GetUIntegerType();

                if (uIntegerTypeType == Semantic::UIntegerType::U64) {
                    return std::reinterpret_pointer_cast<GS_U8Value>(value);
                }
            }

            return nullptr;
        }

        if constexpr (std::is_same_v<GS_StringValue, T>) {
            if (typeType == Semantic::TypeType::String) {
                return std::reinterpret_pointer_cast<GS_StringValue>(value);
            }

            return nullptr;
        }

        return std::reinterpret_pointer_cast<T>(value);
    }

    /**
     * Class for all constants in language grammar
     */
    class GS_ConstantExpression : public GS_Expression {
    public:

        /**
         * Constructor for constant expression
         * @param value Value ptr
         */
        explicit GS_ConstantExpression(GSValuePtr value);

    public:

        /**
         * Creating constant expression ptr
         * @param value Value ptr
         * @return Constant expression ptr
         */
        static std::shared_ptr<GS_ConstantExpression> Create(GSValuePtr value);

    public:

        /**
         * Getter for value ptr
         * @return Value ptr
         */
        LRef<GSValuePtr> GetValue();

    public:

        /**
         * Getter for expression type
         * @return Expression type
         */
        ExpressionType GetExpressionType() const override;

    private:

        /**
         * Value ptr
         */
        GSValuePtr _value;
    };

}

#endif //GSLANGUAGE_GS_CONSTANTEXPRESSION_H
