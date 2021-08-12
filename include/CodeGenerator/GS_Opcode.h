#ifndef GSLANGUAGE_GS_OPCODE_H
#define GSLANGUAGE_GS_OPCODE_H

#include <map>

#include <CrossPlatform/GS_PlatformTypes.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     *
     */
    enum class Opcode {
        PUSH,
        POP,

        PUSH_CONSTANT,

        TO_REG,
        FROM_REG,

        ADD,
        SUB,
        MUL,
        DIV,

        CALL,

        CONSTANT_STRING,

        VARIABLE_NUMBER,

        SAVE,
        GET,

        DONE
    };

    /**
     *
     */
    extern std::map<Opcode, GSByte> opcodeToByte;

    /**
     *
     */
    extern std::map<Opcode, GSString> opcodeToString;

}

#endif //GSLANGUAGE_GS_OPCODE_H
