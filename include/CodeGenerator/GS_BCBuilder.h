#ifndef GSLANGUAGE_GS_BCBUILDER_H
#define GSLANGUAGE_GS_BCBUILDER_H

#include <CodeGenerator/GS_VM_Nodes.h>

namespace GSLanguageCompiler::CodeGenerator {

    class GS_BCBuilder {
    public:

        GS_BCBuilder() = default;

    public:

        GSByteCode createByteCode() {
            GSByteCode bytecode;

            _nodes.emplace_back(std::make_shared<GS_VM_InstructionNode>(Opcode::DONE));

            for (auto &node : _nodes) {
                for (auto &byte : node->generateCode()) {
                    bytecode.emplace_back(byte);
                }
            }

            return bytecode;
        }

    public:

        GSVoid createConstant(GSString value, GSInt id) {
            auto instructionNode = std::make_shared<GS_VM_InstructionWithOperandNode>(
                    Opcode::CONSTANT_STRING,
                    GS_VM_ValueNode(std::make_shared<GS_VM_IntegerValue>(id)));

            auto valueNode = std::make_shared<GS_VM_ValueNode>(std::make_shared<GS_VM_StringValue>(value));

            _nodes.emplace_back(instructionNode);

            _nodes.emplace_back(valueNode);
        }

        GSVoid createVariable(GSString name, GSInt id) {
            auto instructionNode = std::make_shared<GS_VM_InstructionWithOperandNode>(
                    Opcode::VARIABLE_NUMBER,
                    GS_VM_ValueNode(std::make_shared<GS_VM_IntegerValue>(id)));

            auto valueNode = std::make_shared<GS_VM_ValueNode>(std::make_shared<GS_VM_StringValue>(name));

            _nodes.emplace_back(instructionNode);

            _nodes.emplace_back(valueNode);
        }

        GSVoid createSave(GSInt id) {
            auto instructionNode = std::make_shared<GS_VM_InstructionWithOperandNode>(
                    Opcode::SAVE,
                    GS_VM_ValueNode(std::make_shared<GS_VM_IntegerValue>(id)));

            _nodes.emplace_back(instructionNode);
        }

        GSVoid createGet(GSInt id) {
            auto instructionNode = std::make_shared<GS_VM_InstructionWithOperandNode>(
                    Opcode::GET,
                    GS_VM_ValueNode(std::make_shared<GS_VM_IntegerValue>(id)));

            _nodes.emplace_back(instructionNode);
        }

        GSVoid createPush(GSInt value) {
            auto valueNode = GS_VM_ValueNode(std::make_shared<GS_VM_IntegerValue>(value));

            auto instructionNode = std::make_shared<GS_VM_InstructionWithOperandNode>(Opcode::PUSH, valueNode);

            _nodes.emplace_back(instructionNode);
        }

        GSVoid createPop() {
            auto instructionNode = std::make_shared<GS_VM_InstructionNode>(Opcode::POP);

            _nodes.emplace_back(instructionNode);
        }

        GSVoid createPushConstant(GSInt id) {
            auto instructionNode = std::make_shared<GS_VM_InstructionWithOperandNode>(
                    Opcode::PUSH_CONSTANT,
                    GS_VM_ValueNode(std::make_shared<GS_VM_IntegerValue>(id)));

            _nodes.emplace_back(instructionNode);
        }

        GSVoid createToReg(GSInt registerNumber) {
            auto valueNode = GS_VM_ValueNode(std::make_shared<GS_VM_IntegerValue>(registerNumber));

            auto instructionNode = std::make_shared<GS_VM_InstructionWithOperandNode>(Opcode::TO_REG, valueNode);

            _nodes.emplace_back(instructionNode);
        }

        GSVoid createFromReg(GSInt registerNumber) {
            auto valueNode = GS_VM_ValueNode(std::make_shared<GS_VM_IntegerValue>(registerNumber));

            auto instructionNode = std::make_shared<GS_VM_InstructionWithOperandNode>(Opcode::FROM_REG, valueNode);

            _nodes.emplace_back(instructionNode);
        }

        GSVoid createAdd() {
            auto instructionNode = std::make_shared<GS_VM_InstructionNode>(Opcode::ADD);

            _nodes.emplace_back(instructionNode);
        }

        GSVoid createSub() {
            auto instructionNode = std::make_shared<GS_VM_InstructionNode>(Opcode::SUB);

            _nodes.emplace_back(instructionNode);
        }

        GSVoid createMul() {
            auto instructionNode = std::make_shared<GS_VM_InstructionNode>(Opcode::MUL);

            _nodes.emplace_back(instructionNode);
        }

        GSVoid createDiv() {
            auto instructionNode = std::make_shared<GS_VM_InstructionNode>(Opcode::DIV);

            _nodes.emplace_back(instructionNode);
        }

        GSVoid createCall() {
            auto instructionNode = std::make_shared<GS_VM_InstructionNode>(Opcode::CALL);

            _nodes.emplace_back(instructionNode);
        }

    private:

        GSVMNodePtrArray _nodes;
    };

}

#endif //GSLANGUAGE_GS_BCBUILDER_H
