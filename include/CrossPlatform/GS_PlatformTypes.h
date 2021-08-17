#ifndef GSLANGUAGE_GS_PLATFORMTYPES_H
#define GSLANGUAGE_GS_PLATFORMTYPES_H

#include <string>
#include <vector>

#include <CrossPlatform/GS_PlatformDefines.h>

/*
 * TODO write here
 */

#if defined(OS_WINDOWS)
    typedef void GSVoid;

    typedef bool GSBool;

    typedef char GSChar;

    typedef int GSInt;

    typedef short GSShort;

    typedef long GSLong;

    typedef float GSFloat;

    typedef double GSDouble;

    typedef signed GSSigned;

    typedef unsigned GSUnsigned;

    typedef unsigned long long GSULongLong;

    typedef std::string GSString;

//    namespace GSLanguageCompiler::CodeGenerator {
//        typedef char GSByte;
//
//        typedef std::vector<GSByte> GSByteCode;
//    }

#endif

#endif //GSLANGUAGE_GS_PLATFORMTYPES_H
