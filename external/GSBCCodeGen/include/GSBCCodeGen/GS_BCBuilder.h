#ifndef GSBCCODEGEN_GS_BCBUILDER_H
#define GSBCCODEGEN_GS_BCBUILDER_H

#include "GS_BCNodes.h"

namespace GSBCCodeGen {

    class GS_BCBuilder {
    public:

        GS_BCBuilder();

    public:

        GS_BCValueNode *createInt(GSInt value);

        GS_BCValueNode *createString(GSString value);

        GS_BCInstructionWithTwoOperandsNode *createConstant(GS_BCValueNode id, GS_BCValueNode string);

        GS_BCInstructionWithTwoOperandsNode *createVariable(GS_BCValueNode id, GS_BCValueNode name);

        GS_BCInstructionWithOperandNode *createPush(GS_BCValueNode value);

        GS_BCInstructionNode *createPop();

        GS_BCInstructionWithOperandNode *createToReg(GS_BCValueNode registerNumber);

        GS_BCInstructionWithOperandNode *createFromReg(GS_BCValueNode registerNumber);

        GS_BCInstructionWithOperandNode *createSave(GS_BCValueNode variableId);

        GS_BCInstructionWithOperandNode *createGet(GS_BCValueNode variableId);

        GS_BCInstructionNode *createCmp();

        GS_BCCFInstructionNode *createJmp(GS_BCLabelNode label);

        GS_BCCFInstructionNode *createJie(GS_BCLabelNode label);

        GS_BCCFInstructionNode *createJine(GS_BCLabelNode label);

        GS_BCCFInstructionNode *createJig(GS_BCLabelNode label);

        GS_BCCFInstructionNode *createJil(GS_BCLabelNode label);

        GS_BCCFInstructionNode *createJieg(GS_BCLabelNode label);

        GS_BCCFInstructionNode *createJiel(GS_BCLabelNode label);

        GS_BCInstructionWithOperandNode *createCall(GS_BCValueNode functionId);

        GS_BCInstructionNode *createI2s();

        GS_BCInstructionNode *createS2i();

        GS_BCInstructionNode *createAdd();

        GS_BCInstructionNode *createSub();

        GS_BCInstructionNode *createMul();

        GS_BCInstructionNode *createDiv();

        GS_BCInstructionNode *createDone();

        GS_BCLabelNode *createLabel(GS_BCValueNode name);
    };

}

#endif //GSBCCODEGEN_GS_BCBUILDER_H
