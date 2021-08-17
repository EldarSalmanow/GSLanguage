#ifndef GSBCCODEGEN_GS_BCHIGHDECOMPILER_H
#define GSBCCODEGEN_GS_BCHIGHDECOMPILER_H

#include "GS_BCLowDecompiler.h"

namespace GSBCCodeGen {

    class GS_BCHighDecompiler {
    public:

        explicit GS_BCHighDecompiler(GSByteCode bytecode);

    public:

        GS_BCRootNode *decompile();

    public:

        GS_BCLowDecompiler _decompiler;

        GS_BCRootNode *_rootNode;

        GS_BCBlockNode *_blockNode;
    };

}

#endif //GSBCCODEGEN_GS_BCHIGHDECOMPILER_H
