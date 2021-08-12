#ifndef GSLANGUAGE_GS_VM_NODES_H
#define GSLANGUAGE_GS_VM_NODES_H

#include <any>
#include <memory>

#include <CodeGenerator/GS_Opcode.h>

namespace GSLanguageCompiler::CodeGenerator {

    enum class ValueType {
        INT,

        STRING
    };

    class GS_VM_Value {
    public:

        template<typename T>
        GS_VM_Value(ValueType type, T value)
                : _type(type), _value(value) {}

    public:

        ValueType getType() {
            return _type;
        }

        template<typename T>
        T getData() {
            return std::any_cast<T>(_value);
        }

    private:

        ValueType _type;

        std::any _value;
    };

    class GS_VM_IntegerValue : public GS_VM_Value {
    public:

        explicit GS_VM_IntegerValue(GSInt value)
                : GS_VM_Value(ValueType::INT, value) {}
    };

    class GS_VM_StringValue : public GS_VM_Value {
    public:

        explicit GS_VM_StringValue(GSString value)
                : GS_VM_Value(ValueType::STRING, std::move(value)) {}
    };

    typedef std::shared_ptr<GS_VM_Value> GSVMValuePtr;

    class GS_VM_Node {
    public:

        virtual GSByteCode generateCode() =  0;
    };

    typedef std::shared_ptr<GS_VM_Node> GSVMNodePtr;

    typedef std::vector<GSVMNodePtr> GSVMNodePtrArray;

    class GS_VM_ValueNode : public GS_VM_Node {
    public:

        explicit GS_VM_ValueNode(GSVMValuePtr value)
                : _value(std::move(value)) {}

    public:

        GSByteCode generateCode() override {
            GSByteCode bytecode;

            auto type = _value->getType();

            switch (type) {
                case ValueType::INT:
                    bytecode.emplace_back(static_cast<GSByte>(_value->getData<GSInt>()));

                    break;
                case ValueType::STRING:
                    for (auto &symbol : _value->getData<GSString>()) {
                        bytecode.emplace_back(static_cast<GSByte>(symbol));
                    }

                    bytecode.emplace_back(0);

                    break;
            }

            return bytecode;
        }

    private:

        GSVMValuePtr _value;
    };

    class GS_VM_InstructionNode : public GS_VM_Node {
    public:

        explicit GS_VM_InstructionNode(Opcode opcode)
                : _opcode(opcode) {}

    public:

        Opcode getOpcode() {
            return _opcode;
        }

    public:

        GSByteCode generateCode() override {
            GSByteCode bytecode;

            bytecode.emplace_back(opcodeToByte[_opcode]);

            return bytecode;
        }

    private:

        Opcode _opcode;
    };

    class GS_VM_InstructionWithOperandNode : public GS_VM_InstructionNode {
    public:

        GS_VM_InstructionWithOperandNode(Opcode opcode, GS_VM_ValueNode valueNode)
                : GS_VM_InstructionNode(opcode), _valueNode(std::move(valueNode)) {}

    public:

        GSByteCode generateCode() override {
            GSByteCode bytecode;

            bytecode.emplace_back(opcodeToByte[getOpcode()]);

            for (auto &byte : _valueNode.generateCode()) {
                bytecode.emplace_back(byte);
            }

            return bytecode;
        }

    private:

        GS_VM_ValueNode _valueNode;
    };

}

#endif //GSLANGUAGE_GS_VM_NODES_H
