#include <GS_BCBuilder.h>

namespace GSBCCodeGen {

    GS_BCBuilder::GS_BCBuilder() = default;

    GSBCNodePtr GS_BCBuilder::createConstant(GSInt id, GSString string) {
        return new GS_BCInstructionWithTwoOperandsNode(BCOpcodeType::CONSTANT_STRING,
                                                       GS_BCValueNode(id),
                                                       GS_BCValueNode(std::move(string)));
    }

    GSBCNodePtr GS_BCBuilder::createVariable(GSInt id, GSString name) {
        return new GS_BCInstructionWithTwoOperandsNode(BCOpcodeType::VARIABLE_NUMBER,
                                                       GS_BCValueNode(id),
                                                       GS_BCValueNode(std::move(name)));
    }

    GSBCNodePtr GS_BCBuilder::createPush(GSInt value) {
        return new GS_BCInstructionWithOperandNode(BCOpcodeType::PUSH,
                                                   GS_BCValueNode(value));
    }

    GSBCNodePtr GS_BCBuilder::createPop() {
        return new GS_BCInstructionNode(BCOpcodeType::POP);
    }

    GSBCNodePtr GS_BCBuilder::createPushConstant(GSInt id) {
        return new GS_BCInstructionWithOperandNode(BCOpcodeType::PUSH_CONSTANT,
                                                   GS_BCValueNode(id));
    }

    GSBCNodePtr GS_BCBuilder::createToReg(GSInt registerNumber) {
        return new GS_BCInstructionWithOperandNode(BCOpcodeType::TO_REG,
                                                   GS_BCValueNode(registerNumber));
    }

    GSBCNodePtr GS_BCBuilder::createFromReg(GSInt registerNumber) {
        return new GS_BCInstructionWithOperandNode(BCOpcodeType::FROM_REG,
                                                   GS_BCValueNode(registerNumber));
    }

    GSBCNodePtr GS_BCBuilder::createSave(GSInt variableId) {
        return new GS_BCInstructionWithOperandNode(BCOpcodeType::SAVE,
                                                   GS_BCValueNode(variableId));
    }

    GSBCNodePtr GS_BCBuilder::createGet(GSInt variableId) {
        return new GS_BCInstructionWithOperandNode(BCOpcodeType::GET,
                                                   GS_BCValueNode(variableId));
    }

    GSBCNodePtr GS_BCBuilder::createCall(GSInt functionId) {
        return new GS_BCInstructionWithOperandNode(BCOpcodeType::CALL,
                                                   GS_BCValueNode(functionId));
    }

    GSBCNodePtr GS_BCBuilder::createAdd() {
        return new GS_BCInstructionNode(BCOpcodeType::ADD);
    }

    GSBCNodePtr GS_BCBuilder::createSub() {
        return new GS_BCInstructionNode(BCOpcodeType::SUB);
    }

    GSBCNodePtr GS_BCBuilder::createMul() {
        return new GS_BCInstructionNode(BCOpcodeType::MUL);
    }

    GSBCNodePtr GS_BCBuilder::createDiv() {
        return new GS_BCInstructionNode(BCOpcodeType::DIV);
    }

    GSBCNodePtr GS_BCBuilder::createDone() {
        return new GS_BCInstructionNode(BCOpcodeType::DONE);
    }

}
