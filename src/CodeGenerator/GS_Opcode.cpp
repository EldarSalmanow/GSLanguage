#include <GS_Opcode.h>

namespace GSLanguageCompiler::CodeGenerator {

    std::map<Opcode, GSByte> opcodeToByte = {
            {Opcode::PUSH,            0x0},
            {Opcode::POP,             0x1},

            {Opcode::PUSH_CONSTANT,   0x2},

            {Opcode::TO_REG,          0x3},
            {Opcode::FROM_REG,        0x4},

            {Opcode::ADD,             0x5},
            {Opcode::SUB,             0x6},
            {Opcode::MUL,             0x7},
            {Opcode::DIV,             0x8},

            {Opcode::CALL,            0x9},

            {Opcode::CONSTANT_STRING, 0xa},

            {Opcode::VARIABLE_NUMBER, 0xb},

            {Opcode::SAVE,            0xc},
            {Opcode::GET,             0xd},

            {Opcode::DONE,            0xff}
    };

    std::map<Opcode, GSString> opcodeToString = {
            {Opcode::PUSH,            "PUSH"},
            {Opcode::POP,             "POP"},

            {Opcode::PUSH_CONSTANT,   "PUSH_CONSTANT"},

            {Opcode::TO_REG,          "TO_REG"},
            {Opcode::FROM_REG,        "FROM_REG"},

            {Opcode::ADD,             "ADD"},
            {Opcode::SUB,             "SUB"},
            {Opcode::MUL,             "MUL"},
            {Opcode::DIV,             "DIV"},

            {Opcode::CALL,            "CALL"},

            {Opcode::CONSTANT_STRING, "CONSTANT_STRING"},

            {Opcode::VARIABLE_NUMBER, "VARIABLE_NUMBER"},

            {Opcode::SAVE,            "SAVE"},
            {Opcode::GET,             "GET"},

            {Opcode::DONE,            "DONE"}
    };

}