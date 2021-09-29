#ifndef GSLANGUAGE_GS_VALUENODE_H
#define GSLANGUAGE_GS_VALUENODE_H

#include <map>
#include <any>

#include <Parser/Nodes/GS_Node.h>

namespace GSLanguageCompiler::Parser {

    /**
     * Value types
     */
    enum class ValueType {
        VOID,

        INT,

        STRING
    };

    /**
     * String to value type
     */
    extern std::map<GSString, ValueType> stringToValueType;

    /**
     * Value type to string
     */
    extern std::map<ValueType, GSString> valueTypeToString;

    /**
     * Base class for values
     */
    class GS_Value {
    public:

        /**
         * Constructor for all values
         * @tparam T Type of value
         * @param type String type
         * @param data Value
         */
        template<typename T>
        GS_Value(ValueType type, T data)
            : _type(type), _data(std::move(data)) {}

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
        T getData() {
            return std::any_cast<T>(_data);
        }

        /**
         * Getter for value type
         * @return Value type
         */
        ValueType getType();

        /**
         * Setter for value type
         * @param type Value type
         * @return
         */
        GSVoid setType(ValueType type);

    private:

        /**
         * Container for value
         */
        std::any _data;

        /**
         * Value type
         */
        ValueType _type;
    };

    typedef std::shared_ptr<GS_Value> GSValuePtr;

    /**
     * Integer value
     */
    class GS_IntegerValue : public GS_Value {
    public:

        /**
         * Base constructor for integer value;
         */
        GS_IntegerValue();

        /**
         * Constructor for integer value
         * @param value Integer value
         */
        explicit GS_IntegerValue(GSInt value);
    };

    /**
     * String value
     */
    class GS_StringValue : public GS_Value {
    public:

        /**
         * Base constructor for string value
         */
        GS_StringValue();

        /**
         * Constructor for string value
         * @param value String value
         */
        explicit GS_StringValue(GSString value);
    };

    /**
     * Node for containing values
     */
    class GS_ValueNode : public GS_Node {
    public:

        /**
         * Constructor for value node
         * @param value Value ptr
         */
        explicit GS_ValueNode(GSValuePtr value);

    public:

        /**
         * Getter for value ptr
         * @return Value ptr
         */
        GSValuePtr getValue();

    public:

        /**
         * Getter for node type
         * @return Node type
         */
        NodeType getNodeType() override;

        /**
         * Acceptor for code generation visitors
         * @param visitor Codegen visitor
         * @return LLVM IR instructions
         */
        llvm::Value *accept(GS_Visitor<llvm::Value*> *visitor) override;

        /**
         * Acceptor for semantic visitors
         * @param visitor Semantic visitor
         * @return
         */
        GSVoid accept(GS_Visitor<GSVoid> *visitor) override;

        /**
         * Acceptor for optimizer visitors
         * @param visitor Optimizing visitor
         * @return Optimized node
         */
        GSNodePtr accept(GS_Visitor<GSNodePtr> *visitor) override;

    private:

        /**
         * Value ptr
         */
        GSValuePtr _value;
    };

}

#endif //GSLANGUAGE_GS_VALUENODE_H
