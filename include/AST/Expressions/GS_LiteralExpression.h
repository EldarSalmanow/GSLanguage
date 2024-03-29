#ifndef GSLANGUAGE_GS_LITERALEXPRESSION_H
#define GSLANGUAGE_GS_LITERALEXPRESSION_H

#include <any>

#include <Driver/GS_GlobalContext.h>

#include <Semantic/GS_Type.h>

#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Base class for values
     */
    class GS_Value {
    public:

        /*
         *
         * GS_Value PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for value
         * @param type Type
         */
        explicit GS_Value(Semantic::GSTypePtr type);

    public:

        /*
         *
         * GS_Value PUBLIC DESTRUCTORS
         *
         */

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Value();

    public:

        /*
         *
         * GS_Value PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating value
         * @param type Type
         * @return Value ptr
         */
        static std::shared_ptr<GS_Value> Create(Semantic::GSTypePtr type);

    public:

        /*
         *
         * GS_Value PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for type
         * @return Type
         */
        Semantic::GSTypePtr GetType() const;

    public:

        /*
         *
         * GS_Value PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Is literal value
         * @return Is literal value
         */
        virtual Bool IsLiteralValue();

    private:

        /*
         *
         * GS_Value PRIVATE FIELDS
         *
         */

        /**
         * Type
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
    using GSValuePtr = ValuePtr<GS_Value>;

    /**
     * Value ptr array type
     */
    using GSValuePtrArray = std::vector<GSValuePtr>;

    /**
     * Class for literal values
     */
    class GS_LiteralValue : public GS_Value {
    public:

        /*
         *
         * GS_LiteralValue PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for value
         * @tparam ValueT Type of value
         * @param data Value
         * @param type Type
         */
        template<typename ValueT>
        GS_LiteralValue(ValueT value,
                        Semantic::GSTypePtr type)
                : _value(std::move(value)),
                  GS_Value(std::move(type)) {}

    public:

        /*
         *
         * GS_LiteralValue PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating value
         * @tparam ValueT Type of value
         * @param value Value
         * @param type Type
         * @return Value ptr
         */
        template<typename ValueT>
        static std::shared_ptr<GS_Value> Create(ValueT value,
                                                Semantic::GSTypePtr type) {
            return std::make_shared<GS_Value>(std::move(value),
                                              std::move(type));
        }

    public:

        /*
         *
         * GS_LiteralValue PUBLIC METHODS
         *
         */

        /**
         * Getting value wih cast to ValueT
         * @tparam ValueT Type of value
         * @return Value
         */
        template<typename ValueT>
        ValueT GetValueWithCast() const {
            return std::any_cast<ValueT>(_value);
        }

    public:

        /*
         *
         * GS_LiteralValue PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for value
         * @return Value
         */
        ConstLRef<std::any> GetValue() const;

    public:

        /*
         *
         * GS_LiteralValue PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Is literal value
         * @return Is literal value
         */
        Bool IsLiteralValue() override;

    private:

        /*
         *
         * GS_LiteralValue PRIVATE FIELDS
         *
         */

        /**
         * Container for value
         */
        std::any _value;
    };

    /**
     * Bool value
     */
    class GS_BoolValue : public GS_LiteralValue {
    public:

        /*
         *
         * GS_BoolValue PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for Bool value
         * @param value Bool value
         */
        explicit GS_BoolValue(Bool value);

    public:

        /*
         *
         * GS_BoolValue PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating Bool value
         * @param value Bool value
         * @return Bool value ptr
         */
        static std::shared_ptr<GS_BoolValue> Create(Bool value);

    public:

        /*
         *
         * GS_BoolValue PUBLIC METHODS
         *
         */

        /**
         * Getting Bool value
         * @return Bool value
         */
        Bool GetBoolValue() const;
    };

    /**
     * Char value
     */
    class GS_CharValue : public GS_LiteralValue {
    public:

        /*
         *
         * GS_CharValue PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for Char value
         * @param value Char value
         */
        explicit GS_CharValue(USymbol value);

    public:

        /*
         *
         * GS_CharValue PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating Char value
         * @param value Char value
         * @return Char value ptr
         */
        static std::shared_ptr<GS_CharValue> Create(USymbol value);

    public:

        /*
         *
         * GS_CharValue PUBLIC METHODS
         *
         */

        /**
         * Getting Char value
         * @return Char value
         */
        USymbol GetCharValue() const;
    };

    /**
     * Integer value
     */
    class GS_IntegerValue : public GS_LiteralValue {
    public:

        /*
         *
         * GS_IntegerValue PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for integer value
         * @tparam ValueT Value type
         * @param value Value
         * @param integerType Integer type
         */
        template<typename ValueT>
        GS_IntegerValue(ValueT value,
                        Semantic::GSTypePtr integerType)
                : GS_LiteralValue(std::move(value),
                                  std::move(integerType)) {
            if (GetType()->GetType() != Semantic::TypeType::Integer) {
                Driver::GlobalContext().Exit("Can`t create integer value with non integer type!");
            }
        }

    public:

        /*
         *
         * GS_IntegerValue PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating integer value
         * @tparam ValueT Value type
         * @param value Value
         * @param integerType Integer type
         * @return Integer value ptr
         */
        template<typename ValueT>
        static std::shared_ptr<GS_IntegerValue> Create(ValueT value,
                                                       Semantic::GSTypePtr integerType) {
            return std::make_shared<GS_IntegerValue>(std::move(value),
                                                     std::move(integerType));
        }

    public:

        /*
         *
         * GS_IntegerValue PUBLIC METHODS
         *
         */

        /**
         * Getting integer type
         * @return Integer type
         */
        Semantic::TypePtr<Semantic::GS_IntegerType> GetIntegerType() const {
            return std::reinterpret_pointer_cast<Semantic::GS_IntegerType>(GetType());
        }
    };

    /**
     * I8 value
     */
    class GS_I8Value : public GS_IntegerValue {
    public:

        /*
         *
         * GS_I8Value PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for I8 value
         * @param value I8 value
         */
        explicit GS_I8Value(I8 value);

    public:

        /*
         *
         * GS_I8Value PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating I8 value
         * @param value I8 value
         * @return I8 value ptr
         */
        static std::shared_ptr<GS_I8Value> Create(I8 value);

    public:

        /*
         *
         * GS_I8Value PUBLIC METHODS
         *
         */

        /**
         * Getting I8 value
         * @return I8 value
         */
        I8 GetI8Value() const;
    };

    /**
     * I16 value
     */
    class GS_I16Value : public GS_IntegerValue {
    public:

        /*
         *
         * GS_I16Value PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for I16 value
         * @param value I16 value
         */
        explicit GS_I16Value(I16 value);

    public:

        /*
         *
         * GS_I16Value PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating I16 value
         * @param value I16 value
         * @return I16 value ptr
         */
        static std::shared_ptr<GS_I16Value> Create(I16 value);

    public:

        /*
         *
         * GS_I16Value PRIVATE FIELDS
         *
         */

        /**
         * Getting I16 value
         * @return I16 value
         */
        I16 GetI16Value() const;
    };

    /**
     * I32 value
     */
    class GS_I32Value : public GS_IntegerValue {
    public:

        /*
         *
         * GS_I32Value PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for I32 value
         * @param value I32 value
         */
        explicit GS_I32Value(I32 value);

    public:

        /*
         *
         * GS_I32Value PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating I32 value
         * @param value I32 value
         * @return I32 value ptr
         */
        static std::shared_ptr<GS_I32Value> Create(I32 value);

    public:

        /*
         *
         * GS_I32Value PUBLIC METHODS
         *
         */

        /**
         * Getting I32 value
         * @return I32 value
         */
        I32 GetI32Value() const;
    };

    /**
     * I64 value
     */
    class GS_I64Value : public GS_IntegerValue {
    public:

        /*
         *
         * GS_I64Value PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for I64 value
         * @param value I64 value
         */
        explicit GS_I64Value(I64 value);

    public:

        /*
         *
         * GS_I64Value PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating I64 value
         * @param value I64 value
         * @return I64 value ptr
         */
        static std::shared_ptr<GS_I64Value> Create(I64 value);

    public:

        /*
         *
         * GS_I64Value PUBLIC METHODS
         *
         */

        /**
         * Getter for I64 value
         * @return I64 value
         */
        I64 GetI64Value() const;
    };

    /**
     * Unsigned integer value
     */
    class GS_UIntegerValue : public GS_LiteralValue {
    public:

        /*
         *
         * GS_UIntegerValue PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for unsigned integer value
         * @tparam ValueT Value type
         * @param value Value
         * @param unsignedIntegerType Unsigned integer type
         */
        template<typename ValueT>
        GS_UIntegerValue(ValueT value,
                         Semantic::GSTypePtr unsignedIntegerType)
                : GS_LiteralValue(std::move(value),
                                  std::move(unsignedIntegerType)) {
            if (GetType()->GetType() != Semantic::TypeType::UInteger) {
                Driver::GlobalContext().Exit("Can`t create unsigned integer value with non unsigned integer type!");
            }
        }

    public:

        /*
         *
         * GS_UIntegerValue PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating unsigned integer value
         * @tparam ValueT Value type
         * @param value Value
         * @param unsignedIntegerType Unsigned integer type
         * @return Unsigned integer value ptr
         */
        template<typename ValueT>
        static std::shared_ptr<GS_UIntegerValue> Create(ValueT value,
                                                        Semantic::GSTypePtr unsignedIntegerType) {
            return std::make_shared<GS_UIntegerValue>(std::move(value),
                                                      std::move(unsignedIntegerType));
        }

    public:

        /*
         *
         * GS_UIntegerValue PUBLIC METHODS
         *
         */

        /**
         * Getting unsigned integer type
         * @return Unsigned integer type
         */
        Semantic::TypePtr<Semantic::GS_UIntegerType> GetUIntegerType() const {
            return std::reinterpret_pointer_cast<Semantic::GS_UIntegerType>(GetType());
        }
    };

    /**
     * U8 value
     */
    class GS_U8Value : public GS_UIntegerValue {
    public:

        /*
         *
         * GS_U8Value PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for U8 value
         * @param value U8 value
         */
        explicit GS_U8Value(U8 value);

    public:

        /*
         *
         * GS_U8Value PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating U8 value
         * @param value U8 value
         * @return U8 value ptr
         */
        static std::shared_ptr<GS_U8Value> Create(U8 value);

    public:

        /*
         *
         * GS_U8Value PUBLIC METHODS
         *
         */

        /**
         * Getting U8 value
         * @return U8 value
         */
        U8 GetU8Value() const;
    };

    /**
     * U16 value
     */
    class GS_U16Value : public GS_UIntegerValue {
    public:

        /*
         *
         * GS_U16Value PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for U16 value
         * @param value U16 value
         */
        explicit GS_U16Value(U16 value);

    public:

        /*
         *
         * GS_U16Value PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating U16 value
         * @param value U16 value
         * @return U16 value ptr
         */
        static std::shared_ptr<GS_U16Value> Create(U16 value);

    public:

        /*
         *
         * GS_U16Value PUBLIC METHODS
         *
         */

        /**
         * Getting U16 value
         * @return U16 value
         */
        U16 GetU16Value() const;
    };

    /**
     * U32 value
     */
    class GS_U32Value : public GS_UIntegerValue {
    public:

        /*
         *
         * GS_U32Value PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for U32 value
         * @param value U32 value
         */
        explicit GS_U32Value(U32 value);

    public:

        /*
         *
         * GS_U32Value PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating U32 value
         * @param value U32 value
         * @return U32 value ptr
         */
        static std::shared_ptr<GS_U32Value> Create(U32 value);

    public:

        /*
         *
         * GS_U32Value PUBLIC METHODS
         *
         */

        /**
         * Getting U32 value
         * @return U32 value
         */
        U32 GetU32Value() const;
    };

    /**
     * U64 value
     */
    class GS_U64Value : public GS_UIntegerValue {
    public:

        /*
         *
         * GS_U64Value PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for U64 value
         * @param value U64 value
         */
        explicit GS_U64Value(U64 value);

    public:

        /*
         *
         * GS_U64Value PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating U64 value
         * @param value U64 value
         * @return U64 value ptr
         */
        static std::shared_ptr<GS_U64Value> Create(U64 value);

    public:

        /*
         *
         * GS_U64Value PUBLIC METHODS
         *
         */

        /**
         * Getting U64 value
         * @return U64 value
         */
        U64 GetU64Value() const;
    };

    /**
     * String value
     */
    class GS_StringValue : public GS_LiteralValue {
    public:

        /*
         *
         * GS_StringValue PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for String value
         * @param value String value
         */
        explicit GS_StringValue(UString value);

    public:

        /*
         *
         * GS_StringValue PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating String value
         * @param value String value
         * @return String value ptr
         */
        static std::shared_ptr<GS_StringValue> Create(UString value);

    public:

        /*
         *
         * GS_StringValue PUBLIC METHODS
         *
         */

        /**
         * Getting String value
         * @return String value
         */
        UString GetStringValue() const;
    };

    /**
     * Casting value to ValueT
     * @tparam ValueT Type of value
     * @param value Value
     * @return Value or null
     */
    template<typename ValueT>
    inline ValuePtr<ValueT> ToValue(ConstLRef<GSValuePtr> value) {
        static_assert(std::is_base_of_v<GS_Value, ValueT>,
                      "Type for casting must be inherited from GS_Value!");

        auto type = value->GetType();
        auto typeType = type->GetType();

        switch (typeType) {
            case Semantic::TypeType::Void: {
                return nullptr;
            }
            case Semantic::TypeType::Char: {
                if constexpr (!std::is_same_v<GS_CharValue, ValueT>) {
                    return nullptr;
                }

                break;
            }
            case Semantic::TypeType::Integer: {
                auto integerType = std::reinterpret_pointer_cast<Semantic::GS_IntegerType>(type);
                auto integerTypeType = integerType->GetIntegerType();

                if constexpr (std::is_same_v<GS_IntegerValue, ValueT>) {
                    break;
                }

                switch (integerTypeType) {
                    case Semantic::IntegerType::I8: {
                        if constexpr (!std::is_same_v<GS_I8Value, ValueT>) {
                            return nullptr;
                        }

                        break;
                    }
                    case Semantic::IntegerType::I16: {
                        if constexpr (!std::is_same_v<GS_I16Value, ValueT>) {
                            return nullptr;
                        }

                        break;
                    }
                    case Semantic::IntegerType::I32: {
                        if constexpr (!std::is_same_v<GS_I32Value, ValueT>) {
                            return nullptr;
                        }

                        break;
                    }
                    case Semantic::IntegerType::I64: {
                        if constexpr (!std::is_same_v<GS_I64Value, ValueT>) {
                            return nullptr;
                        }

                        break;
                    }
                    case Semantic::IntegerType::User: {
                        return nullptr;
                    }
                }

                break;
            }
            case Semantic::TypeType::UInteger: {
                auto uIntegerType = std::reinterpret_pointer_cast<Semantic::GS_UIntegerType>(type);
                auto uIntegerTypeType = uIntegerType->GetUIntegerType();

                if constexpr (std::is_same_v<GS_UIntegerValue, ValueT>) {
                    break;
                }

                switch (uIntegerTypeType) {
                    case Semantic::UIntegerType::U8: {
                        if constexpr (!std::is_same_v<GS_U8Value, ValueT>) {
                            return nullptr;
                        }

                        break;
                    }
                    case Semantic::UIntegerType::U16: {
                        if constexpr (!std::is_same_v<GS_U16Value, ValueT>) {
                            return nullptr;
                        }

                        break;
                    }
                    case Semantic::UIntegerType::U32: {
                        if constexpr (!std::is_same_v<GS_U32Value, ValueT>) {
                            return nullptr;
                        }

                        break;
                    }
                    case Semantic::UIntegerType::U64: {
                        if constexpr (!std::is_same_v<GS_U64Value, ValueT>) {
                            return nullptr;
                        }

                        break;
                    }
                    case Semantic::UIntegerType::User: {
                        return nullptr;
                    }
                }

                break;
            }
            case Semantic::TypeType::String: {
                if constexpr (!std::is_same_v<GS_StringValue, ValueT>) {
                    return nullptr;
                }

                break;
            }
            case Semantic::TypeType::Array: {
                return nullptr;
            }
            case Semantic::TypeType::User: {
                return nullptr;
            }
            default: {
                return nullptr;
            }
        }

        return std::reinterpret_pointer_cast<ValueT>(value);
    }

    /**
     * Casting value to literal value
     * @param value Value
     * @return Literal value or null
     */
    template<>
    inline ValuePtr<GS_LiteralValue> ToValue(ConstLRef<GSValuePtr> value) {
        if (!value->IsLiteralValue()) {
            return nullptr;
        }

        return std::reinterpret_pointer_cast<GS_LiteralValue>(value);
    }

    /**
     * Class for literal expression in language grammar
     */
    class GS_LiteralExpression : public GS_Expression {
    public:

        /*
         *
         * GS_LiteralExpression PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for literal expression
         * @param value Value
         */
        explicit GS_LiteralExpression(GSValuePtr value);

    public:

        /*
         *
         * GS_LiteralExpression PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating literal expression
         * @param value Value
         * @return Literal expression ptr
         */
        static std::shared_ptr<GS_LiteralExpression> Create(GSValuePtr value);

    public:

        /*
         *
         * GS_LiteralExpression PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for value
         * @return Value
         */
        LRef<GSValuePtr> GetValue();

    public:

        /*
         *
         * GS_LiteralExpression PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for expression type
         * @return Expression type
         */
        ExpressionType GetExpressionType() const override;

    private:

        /*
         *
         * GS_LiteralExpression PRIVATE FIELDS
         *
         */

        /**
         * Value
         */
        GSValuePtr _value;
    };

}

#endif //GSLANGUAGE_GS_LITERALEXPRESSION_H
