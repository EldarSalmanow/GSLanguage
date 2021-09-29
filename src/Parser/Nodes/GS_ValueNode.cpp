#include <Nodes/GS_ValueNode.h>

namespace GSLanguageCompiler::Parser {

    std::map<GSString, ValueType> stringToValueType = {
            {"Void",   ValueType::VOID},

            {"Int",    ValueType::INT},

            {"String", ValueType::STRING}
    };

    std::map<ValueType, GSString> valueTypeToString = {
            {ValueType::VOID,   "VOID"},

            {ValueType::INT,    "INT"},

            {ValueType::STRING, "STRING"}
    };

    GS_Value::~GS_Value() = default;

    ValueType GS_Value::getType() {
        return _type;
    }

    GSVoid GS_Value::setType(ValueType type) {
        _type = type;
    }

    GS_IntegerValue::GS_IntegerValue()
        : GS_Value(ValueType::INT, 0) {}

    GS_IntegerValue::GS_IntegerValue(GSInt value)
        : GS_Value(ValueType::INT, value) {}

    GS_StringValue::GS_StringValue()
        : GS_Value(ValueType::STRING, "") {}

    GS_StringValue::GS_StringValue(GSString value)
        : GS_Value(ValueType::STRING, std::move(value)) {}

    GS_ValueNode::GS_ValueNode(GSValuePtr value)
            : _value(std::move(value)) {}

    GSValuePtr GS_ValueNode::getValue() {
        return _value;
    }

    NodeType GS_ValueNode::getNodeType() {
        return NodeType::VALUE_NODE;
    }

    llvm::Value *GS_ValueNode::accept(GS_Visitor<llvm::Value*> *visitor) {
        return visitor->visit(this);
    }

    GSVoid GS_ValueNode::accept(GS_Visitor<GSVoid> *visitor) {
        return visitor->visit(this);
    }

    GSNodePtr GS_ValueNode::accept(GS_Visitor<GSNodePtr> *visitor) {
        return visitor->visit(this);
    }

}