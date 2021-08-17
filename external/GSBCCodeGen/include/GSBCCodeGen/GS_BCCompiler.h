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

        GSVoid createPop();

        GSVoid createPushConstant(GSInt id);

        GSVoid createToReg(GSInt registerNumber);

        GSVoid createFromReg(GSInt registerNumber);

        GSVoid createSave(GSInt variableId);

        GSVoid createGet(GSInt variableId);

        GSVoid createCall(GSInt functionId);

        GSVoid createAdd();

        GSVoid createSub();

        GSVoid createMul();

        GSVoid createDiv();

        GSVoid createDone();

    public:

        GS_BCRootNode *getRootNode();

    private:

        GS_BCBuilder _builder;

        GS_BCRootNode *_rootNode;

        GS_BCBlockNode *_blockNode;
    };

}

#endif //GSBCCODEGEN_GS_BCCOMPILER_H
