#ifndef GSBCCODEGEN_GS_BCREADER_H
#define GSBCCODEGEN_GS_BCREADER_H

#include <fstream>

#include <GS_PlatformTypes.h>

namespace GSBCCodeGen {

    class GS_BCReader {
    public:

        explicit GS_BCReader(GSString filename);

    public:

        GSByteCode read();

    private:

        GSString _filename;
    };

}

#endif //GSBCCODEGEN_GS_BCREADER_H
