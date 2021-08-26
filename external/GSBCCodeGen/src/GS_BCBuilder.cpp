#include <GS_BCBuilder.h>

namespace GSBCCodeGen {

    GS_BCBuilder::GS_BCBuilder() = default;

    GS_BCValueNode *GS_BCBuilder::createInt(GSInt value) {
        return new GS_BCValueNode(value);
    }

    GS_BCValueNode *GS_BCBuilder::createString(GSString value) {
        return new GS_BCValueNode(std::move(value));
    }

    GS_BCInstructionWithTwoOperandsNode *GS_BCBuilder::createConstant(GS_BCValueNode id, GS_BCValueNode string) {
        if (id.getType() != "Int" || string.getType() != "String") {
            throw std::runtime_error("Invalid values for generating constant!");
        }

        return new GS_BCInstructionWithTwoOperandsNode(BCOpcodeType::CONSTANT, id, string);
    }

    GS_BCInstructionWithTwoOperandsNode *GS_BCBuilder::createVariable(GS_BCValueNode id, GS_BCValueNode name) {
        if (id.getType() != "Int" || name.getType() != "String") {
            throw std::runtime_error("Invalid values for generating variable!");
        }

        return new GS_BCInstructionWithTwoOperandsNode(BCOpcodeType::VARIABLE, id, name);
    }

    GS_BCInstructionWithOperandNode *GS_BCBuilder::createPush(GS_BCValueNode value) {
        auto type = value.getType();

        if (type == "Int") {
            return new GS_BCInstructionWithOperandNode(BCOpcodeType::PUSH_I, value);
        } else if (type == "String") {
            return new GS_BCInstructionWithOperandNode(BCOpcodeType::PUSH_S, value);
        } else {
            throw std::runtime_error("Invalid type for generating push instruction!");
        }
    }

    GS_BCInstructionNode *GS_BCBuilder::createPop() {
        return new GS_BCInstructionNode(BCOpcodeType::POP);
    }

    GS_BCInstructionWithOperandNode *GS_BCBuilder::createToReg(GS_BCValueNode registerNumber) {
        if (registerNumber.getType() != "Int") {
            throw std::runtime_error("Invalid type for generating to reg instruction!");
        }

        return new GS_BCInstructionWithOperandNode(BCOpcodeType::TO_REG, registerNumber);
    }

    GS_BCInstructionWithOperandNode *GS_BCBuilder::createFromReg(GS_BCValueNode registerNumber) {
        if (registerNumber.getType() != "Int") {
            throw std::runtime_error("Invalid type for generating from reg instruction!");
        }

        return new GS_BCInstructionWithOperandNode(BCOpcodeType::FROM_REG, registerNumber);
    }

    GS_BCInstructionWithOperandNode *GS_BCBuilder::createSave(GS_BCValueNode variableId) {
        if (variableId.getType() != "Int") {
            throw std::runtime_error("Invalid type for generating save instruction!");
        }

        return new GS_BCInstructionWithOperandNode(BCOpcodeType::SAVE, variableId);
    }

    GS_BCInstructionWithOperandNode *GS_BCBuilder::createGet(GS_BCValueNode variableId) {
        if (variableId.getType() != "Int") {
            throw std::runtime_error("Invalid type for generating get instruction!");
        }

        return new GS_BCInstructionWithOperandNode(BCOpcodeType::GET, variableId);
    }

    GS_BCInstructionNode *GS_BCBuilder::createCmp() {
        return new GS_BCInstructionNode(BCOpcodeType::CMP);
    }

    GS_BCCFInstructionNode *GS_BCBuilder::createJmp(GS_BCLabelNode label) {
        return new GS_BCCFInstructionNode(BCOpcodeType::JMP, std::move(label));
    }

    GS_BCCFInstructionNode *GS_BCBuilder::createJie(GS_BCLabelNode label) {
        return new GS_BCCFInstructionNode(BCOpcodeType::JIE, std::move(label));
    }

    GS_BCCFInstructionNode *GS_BCBuilder::createJine(GS_BCLabelNode label) {
        return new GS_BCCFInstructionNode(BCOpcodeType::JINE, std::move(label));
    }

    GS_BCCFInstructionNode *GS_BCBuilder::createJig(GS_BCLabelNode label) {
        return new GS_BCCFInstructionNode(BCOpcodeType::JIG, std::move(label));
    }

    GS_BCCFInstructionNode *GS_BCBuilder::createJil(GS_BCLabelNode label) {
        return new GS_BCCFInstructionNode(BCOpcodeType::JIL, std::move(label));
    }

    GS_BCCFInstructionNode *GS_BCBuilder::createJieg(GS_BCLabelNode label) {
        return new GS_BCCFInstructionNode(BCOpcodeType::JIEG, std::move(label));
    }

    GS_BCCFInstructionNode *GS_BCBuilder::createJiel(GS_BCLabelNode label) {
        return new GS_BCCFInstructionNode(BCOpcodeType::JIEL, std::move(label));
    }

    GS_BCInstructionWithOperandNode *GS_BCBuilder::createCall(GS_BCValueNode functionId) {
        if (functionId.getType() != "Int") {
            throw std::runtime_error("Invalid type for generating call instruction!");
        }

        return new GS_BCInstructionWithOperandNode(BCOpcodeType::CALL, functionId);
    }

    GS_BCInstructionNode *GS_BCBuilder::createI2s() {
        return new GS_BCInstructionNode(BCOpcodeType::I2S);
    }

    GS_BCInstructionNode *GS_BCBuilder::createS2i() {
        return new GS_BCInstructionNode(BCOpcodeType::S2I);
    }

    GS_BCInstructionNode *GS_BCBuilder::createAdd() {
        return new GS_BCInstructionNode(BCOpcodeType::ADD);
    }

    GS_BCInstructionNode *GS_BCBuilder::createSub() {
        return new GS_BCInstructionNode(BCOpcodeType::SUB);
    }

    GS_BCInstructionNode *GS_BCBuilder::createMul() {
        return new GS_BCInstructionNode(BCOpcodeType::MUL);
    }

    GS_BCInstructionNode *GS_BCBuilder::createDiv() {
        return new GS_BCInstructionNode(BCOpcodeType::DIV);
    }

    GS_BCInstructionNode *GS_BCBuilder::createDone() {
        return new GS_BCInstructionNode(BCOpcodeType::DONE);
    }

    GS_BCLabelNode *GS_BCBuilder::createLabel(GS_BCValueNode name) {
        if (name.getType() != "String") {
            throw std::runtime_error("Invalid type for generating label!");
        }

        return new GS_BCLabelNode(std::move(name));
    }

}
