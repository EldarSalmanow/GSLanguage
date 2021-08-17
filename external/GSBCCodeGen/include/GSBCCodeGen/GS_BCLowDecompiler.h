#ifndef GSBCCODEGEN_GS_BCLOWDECOMPILER_H
#define GSBCCODEGEN_GS_BCLOWDECOMPILER_H

#include "GS_BCNodes.h"

namespace GSBCCodeGen {

    class GS_BCLowDecompiler {
    public:

        explicit GS_BCLowDecompiler(GSByteCode bytecode);

    public:

        GSByte getValue();

        GSString getString();

        BCOpcodeType getOpcode();

        GSVoid nextByte();

    private:

        GSByteCode _bytecode;

        GSByteCode::iterator _bytecodeIterator;
    };

}

#endif //GSBCCODEGEN_GS_BCLOWDECOMPILER_H
