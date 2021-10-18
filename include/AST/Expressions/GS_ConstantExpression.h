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
         * Constructor for all values
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
         * Getter for data value
         * @tparam T Type for getting
         * @return Value
         */
        template<typename T>
        T getValueWithCast() {
            return std::any_cast<T>(_value);
        }

    public:

        /**
         * Getter for value
         * @return Value
         */
        Any getValue();

        /**
         * Getter for type ptr
         * @return Type ptr
         */
        GSTypePtr getType();

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
        explicit GS_StringValue(String value);
    };

    /**
     * Class for all constants in language grammar
     */
    class GS_ConstantExpression : public GS_Expression {
    public:

        /**
         * Constructor for GS_ConstantExpression
         * @param value Value ptr
         */
        explicit GS_ConstantExpression(GSValuePtr value);

    public:

        /**
         * Getter for value ptr
         * @return Value ptr
         */
        GSValuePtr getValue();

    public:

        /**
         * Getter for expression type
         * @return Expression type
         */
        ExpressionType getExpressionType() override;

    private:

        /**
         * Value ptr
         */
        GSValuePtr _value;
    };

}

#endif //GSLANGUAGE_GS_CONSTANTEXPRESSION_H
