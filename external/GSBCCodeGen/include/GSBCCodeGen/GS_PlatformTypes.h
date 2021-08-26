#ifndef GSBCCODEGEN_GS_PLATFORMTYPES_H
#define GSBCCODEGEN_GS_PLATFORMTYPES_H

#include <string>
#include <vector>

#include "GS_PlatformDefines.h"

#if defined(OS_WINDOWS)
    typedef void GSVoid;

    typedef bool GSBool;

    typedef char GSChar;

    typedef int GSInt;

    typedef std::string GSString;

    typedef unsigned char GSByte;

    typedef GSByte* GSBytePtr;

    typedef std::vector<GSByte> GSByteCode;

#endif

#endif //GSBCCODEGEN_GS_PLATFORMTYPES_H
