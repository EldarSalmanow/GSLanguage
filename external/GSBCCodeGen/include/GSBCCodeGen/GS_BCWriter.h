#ifndef GSBCCODEGEN_GS_BCWRITER_H
#define GSBCCODEGEN_GS_BCWRITER_H

#include <fstream>

#include "GS_PlatformTypes.h"

namespace GSBCCodeGen {

    class GS_BCWriter {
    public:

        explicit GS_BCWriter(GSString filename);

    public:

        GSVoid write(GSByteCode bytecode);

    private:

        GSString _filename;

        GSByteCode _bytecode;
    };

}

#endif //GSBCCODEGEN_GS_BCWRITER_H
