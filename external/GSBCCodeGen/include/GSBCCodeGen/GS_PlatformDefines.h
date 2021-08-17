#ifndef GSBCCODEGEN_GS_PLATFORMDEFINES_H
#define GSBCCODEGEN_GS_PLATFORMDEFINES_H

// Windows operating system
#if defined(_WIN32) || defined(_WIN64)
#define OS_DETECTED
#define OS_WINDOWS
#endif

// Linux operating system
#if defined(__linux__)
#define OS_DETECTED
#define OS_LINUX
#endif

// MSVC compiler
#if defined(_MSC_VER)
#define COMPILER_DETECTED
#define COMPILER_MSVC
#endif

// MinGW compiler
#if defined(__MINGW32__) || defined(__MINGW64__)
#define COMPILER_DETECTED
#define COMPILER_MINGW
#endif

// Is detected OS
#if !defined(OS_DETECTED)
#error OS not supported!
#endif

// Is detected compiler
#if !defined(COMPILER_DETECTED)
#error Compiler not supported!
#endif

#endif //GSBCCODEGEN_GS_PLATFORMDEFINES_H
