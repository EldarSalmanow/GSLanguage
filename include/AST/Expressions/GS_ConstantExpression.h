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
     * Value ptr type
     */
    using GSValuePtr = std::shared_ptr<GS_Value>;

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
         * Creating I32 value ptr
         * @param value Value
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
         * Creating String value ptr
         * @param value Value
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
    inline std::shared_ptr<T> GSValueCast(GSValuePtr value) {
        static_assert(std::is_base_of_v<GS_Value, T>, "Type for casting must be inherited from GS_Value!");

        auto type = value->GetType();
        auto name = type->GetName();

        if constexpr (std::is_same_v<GS_I32Value, T>) {
            if (name == "I32") {
                return std::reinterpret_pointer_cast<GS_I32Value>(value);
            }

            return nullptr;
        }

        if constexpr (std::is_same_v<GS_StringValue, T>) {
            if (name == "String") {
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
