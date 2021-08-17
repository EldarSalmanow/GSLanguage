#ifndef GSBCCODEGEN_GS_BCBUILDER_H
#define GSBCCODEGEN_GS_BCBUILDER_H

#include "GS_BCNodes.h"

namespace GSBCCodeGen {

    class GS_BCBuilder {
    public:

        GS_BCBuilder();

    public:

        GSBCNodePtr createConstant(GSInt id, GSString string);

        GSBCNodePtr createVariable(GSInt id, GSString name);

        GSBCNodePtr createPush(GSInt value);

        GSBCNodePtr createPop();

        GSBCNodePtr createPushConstant(GSInt id);

        GSBCNodePtr createToReg(GSInt registerNumber);

        GSBCNodePtr createFromReg(GSInt registerNumber);

        GSBCNodePtr createSave(GSInt variableId);

        GSBCNodePtr createGet(GSInt variableId);

        GSBCNodePtr createCall(GSInt functionId);

        GSBCNodePtr createAdd();

        GSBCNodePtr createSub();

        GSBCNodePtr createMul();

        GSBCNodePtr createDiv();

        GSBCNodePtr createDone();
    };

}

#endif //GSBCCODEGEN_GS_BCBUILDER_H
