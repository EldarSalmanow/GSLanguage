#include <GS_Opcode.h>

namespace GSLanguageCompiler::CodeGenerator {

    std::map<Opcode, GSByte> opcodeToByte = {
            {Opcode::PUSH,            0x0},
            {Opcode::POP,             0x1},

            {Opcode::ADD,             0x2},
            {Opcode::SUB,             0x3},
            {Opcode::MUL,             0x4},
            {Opcode::DIV,             0x5},

            {Opcode::CALL,            0x6},

            {Opcode::TO_REG,          0x7},
            {Opcode::FROM_REG,        0x8},

            {Opcode::CONSTANT_NUMBER, 0x9},
            {Opcode::CONSTANT_STRING, 0xa},

            {Opcode::VARIABLE_NUMBER, 0xb},
            {Opcode::VARIABLE_STRING, 0xc},

            {Opcode::FUNCTION,        0xd},

            {Opcode::DONE,            0xff}
    };

    std::map<Opcode, GSString> opcodeToString = {
            {Opcode::PUSH,            "PUSH"},
            {Opcode::POP,             "POP"},

            {Opcode::ADD,             "ADD"},
            {Opcode::SUB,             "SUB"},
            {Opcode::MUL,             "MUL"},
            {Opcode::DIV,             "DIV"},

            {Opcode::CALL,            "CALL"},

            {Opcode::TO_REG,          "TO_REG"},
            {Opcode::FROM_REG,        "FROM_REG"},

            {Opcode::CONSTANT_NUMBER, "CONSTANT_NUMBER"},
            {Opcode::CONSTANT_STRING, "CONSTANT_STRING"},

            {Opcode::VARIABLE_NUMBER, "VARIABLE_NUMBER"},
            {Opcode::VARIABLE_STRING, "VARIABLE_STRING"},

            {Opcode::FUNCTION,        "FUNCTION"},

            {Opcode::DONE,            "DONE"}
    };

}