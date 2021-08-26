#ifndef GSBCCODEGEN_GS_BCCOMPILER_H
#define GSBCCODEGEN_GS_BCCOMPILER_H

#include "GS_BCBuilder.h"

#include "GS_BCVisitors.h"

namespace GSBCCodeGen {

    class GS_BCCompiler {
    public:

        GS_BCCompiler();

    public:

        GSByteCode createBytecode();

    public:

        GSVoid createConstant(GSInt id, GSString string);

        GSVoid createVariable(GSInt id, GSString name);

        GSVoid createPush(GSInt value);

        GSVoid createPush(GSString value);

        GSVoid createPop();

        GSVoid createToReg(GSInt registerNumber);

        GSVoid createFromReg(GSInt registerNumber);

        GSVoid createSave(GSInt variableId);

        GSVoid createGet(GSInt variableId);

        GSVoid createCmp();

        GSVoid createJmp(GS_BCLabelNode *label);

        GSVoid createJie(GS_BCLabelNode *label);

        GSVoid createJine(GS_BCLabelNode *label);

        GSVoid createJig(GS_BCLabelNode *label);

        GSVoid createJil(GS_BCLabelNode *label);

        GSVoid createJieg(GS_BCLabelNode *label);

        GSVoid createJiel(GS_BCLabelNode *label);

        GSVoid createCall(GSInt functionId);

        GSVoid createI2s();

        GSVoid createS2i();

        GSVoid createAdd();

        GSVoid createSub();

        GSVoid createMul();

        GSVoid createDiv();

        GSVoid createDone();

        GS_BCLabelNode *createLabel(GSString name);

        GSVoid bindLabel(GS_BCLabelNode *label);

    public:

        GS_BCRootNode *getRootNode();

    private:

        GS_BCBuilder _builder;

        GS_BCRootNode *_rootNode;

        GS_BCBlockNode *_blockNode;
    };

}

#endif //GSBCCODEGEN_GS_BCCOMPILER_H
