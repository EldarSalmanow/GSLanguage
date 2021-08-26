#ifndef GSBCCODEGEN_GS_BCOPCODETYPE_H
#define GSBCCODEGEN_GS_BCOPCODETYPE_H

#include <map>

#include "GS_PlatformTypes.h"

namespace GSBCCodeGen {

    enum class BCOpcodeType {
        CONSTANT,

        VARIABLE,

        PUSH_I,
        PUSH_S,

        POP,

        TO_REG,
        FROM_REG,

        SAVE,
        GET,

        CMP,

        JMP,
        JIE,
        JINE,
        JIG,
        JIL,
        JIEG,
        JIEL,

        CALL,

        I2S,
        S2I,

        ADD,
        SUB,
        MUL,
        DIV,

        DONE
    };

    extern std::map<BCOpcodeType, GSByte> opcodeToByte;

    extern std::map<GSByte, BCOpcodeType> byteToOpcode;

    extern std::map<BCOpcodeType, GSString> opcodeToString;

}

#endif //GSBCCODEGEN_GS_BCOPCODETYPE_H
