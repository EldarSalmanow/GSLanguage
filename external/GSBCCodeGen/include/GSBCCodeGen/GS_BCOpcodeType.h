#ifndef GSBCCODEGEN_GS_BCOPCODETYPE_H
#define GSBCCODEGEN_GS_BCOPCODETYPE_H

#include <map>

#include "GS_PlatformTypes.h"

namespace GSBCCodeGen {

    enum class BCOpcodeType {
        CONSTANT_STRING,

        VARIABLE_NUMBER,

        PUSH,
        POP,

        PUSH_CONSTANT,

        TO_REG,
        FROM_REG,

        SAVE,
        GET,

        CALL,

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
