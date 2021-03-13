#ifndef GSLANGUAGE_GS_PLATFORMDEFINES_H
#define GSLANGUAGE_GS_PLATFORMDEFINES_H

#if defined(_WIN32) || defined(_WIN64)
#define OS_DETECTED
#define OS_WINDOWS
#endif

#if defined(_MSC_VER)
#define COMPILER_DETECTED
#define COMPILER_MSVC
#endif

#if defined(__MINGW32__) || defined(__MINGW64__)
#define COMPILER_DETECTED
#define COMPILER_MINGW
#endif

#if !defined(OS_DETECTED)
#error OS not supported!
#endif

#if !defined(COMPILER_DETECTED)
#error Compiler not supported!
#endif

#endif //GSLANGUAGE_GS_PLATFORMDEFINES_H
