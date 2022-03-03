#ifndef GSLANGUAGE_GS_CONSTANTEXPRESSION_H
#define GSLANGUAGE_GS_CONSTANTEXPRESSION_H

#include <AST/GS_Expression.h>

#include <AST/GS_Type.h>

namespace GSLanguageCompiler::AST {

    /**
     * Base class for values
     */
    class GS_Value {
    public:

        /**
         * Constructor for value
         * @tparam T Type of value
         * @param type Type ptr
         * @param data Value
         */
        template<typename T>
        GS_Value(GSTypePtr type, T value)
                : _type(std::move(type)), _value(std::move(value)) {}

    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Value();

    public:

        /**
         * Creating value ptr
         * @tparam T Type of value
         * @param type Type ptr
         * @param value Value
         * @return Value ptr
         */
        template<typename T>
        static SharedPtr<GS_Value> Create(GSTypePtr type, T value) {
            return std::make_shared<GS_Value>(std::move(type), std::move(value));
        }

    public:

        /**
         * Getter for data value
         * @tparam T Type for getting
         * @return Value
         */
        template<typename T>
        T getValueWithCast() const {
            return std::any_cast<T>(getValue());
        }

    public:

        /**
         * Getter for value
         * @return Value
         */
        Any getValue() const;

        /**
         * Getter for type ptr
         * @return Type ptr
         */
        GSTypePtr getType() const;

    private:

        /**
         * Container for value
         */
        Any _value;

        /**
         * Type ptr
         */
        GSTypePtr _type;
    };

    /**
     * Value ptr type
     */
    using GSValuePtr = SharedPtr<GS_Value>;

    /**
     * I32 value
     */
    class GS_I32Value : public GS_Value {
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
        static SharedPtr<GS_I32Value> Create(I32 value);
    };

    /**
     * String value
     */
    class GS_StringValue : public GS_Value {
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
        static SharedPtr<GS_StringValue> Create(UString value);
    };

    /**
     * Class for all constants in language grammar
     */
    class GS_ConstantExpression : public GS_Expression {
    public:

        /**
         * Constructor for constant expression
         * @param value Value ptr
         * @param scope Scope
         */
        GS_ConstantExpression(GSValuePtr value, GSScopePtr scope);

    public:

        /**
         * Creating constant expression ptr
         * @param value Value ptr
         * @param scope Scope ptr
         * @return Constant expression ptr
         */
        static SharedPtr<GS_ConstantExpression> Create(GSValuePtr value, GSScopePtr scope);

    public:

        /**
         * Getter for value ptr
         * @return Value ptr
         */
        LRef<GSValuePtr> getValue();

    public:

        /**
         * Getter for expression type
         * @return Expression type
         */
        ExpressionType getExpressionType() const override;

    private:

        /**
         * Value ptr
         */
        GSValuePtr _value;
    };

}

#endif //GSLANGUAGE_GS_CONSTANTEXPRESSION_H
