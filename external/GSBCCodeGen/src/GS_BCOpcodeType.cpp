#include <GS_BCOpcodeType.h>

namespace GSBCCodeGen {

    std::map<BCOpcodeType, GSByte> opcodeToByte = {
            {BCOpcodeType::CONSTANT_STRING, 0x0},

            {BCOpcodeType::VARIABLE_NUMBER, 0x1},

            {BCOpcodeType::PUSH,            0x2},
            {BCOpcodeType::POP,             0x3},

            {BCOpcodeType::PUSH_CONSTANT,   0x4},

            {BCOpcodeType::TO_REG,          0x5},
            {BCOpcodeType::FROM_REG,        0x6},

            {BCOpcodeType::SAVE,            0x7},
            {BCOpcodeType::GET,             0x8},

            {BCOpcodeType::CALL,            0x9},

            {BCOpcodeType::ADD,             0xa},
            {BCOpcodeType::SUB,             0xb},
            {BCOpcodeType::MUL,             0xc},
            {BCOpcodeType::DIV,             0xd},

            {BCOpcodeType::DONE,            0xff}
    };

    std::map<GSByte, BCOpcodeType> byteToOpcode = {
            {0x0,  BCOpcodeType::CONSTANT_STRING},

            {0x1,  BCOpcodeType::VARIABLE_NUMBER},

            {0x2,  BCOpcodeType::PUSH},
            {0x3,  BCOpcodeType::POP},

            {0x4,  BCOpcodeType::PUSH_CONSTANT},

            {0x5,  BCOpcodeType::TO_REG},
            {0x6,  BCOpcodeType::FROM_REG},

            {0x7,  BCOpcodeType::SAVE},
            {0x8,  BCOpcodeType::GET},

            {0x9,  BCOpcodeType::CALL},

            {0xa,  BCOpcodeType::ADD},
            {0xb,  BCOpcodeType::SUB},
            {0xc,  BCOpcodeType::MUL},
            {0xd,  BCOpcodeType::DIV},

            {0xff, BCOpcodeType::DONE}
    };

    std::map<BCOpcodeType, GSString> opcodeToString = {
            {BCOpcodeType::CONSTANT_STRING, "CONSTANT_STRING"},

            {BCOpcodeType::VARIABLE_NUMBER, "VARIABLE_NUMBER"},

            {BCOpcodeType::PUSH,            "PUSH"},
            {BCOpcodeType::POP,             "POP"},

            {BCOpcodeType::PUSH_CONSTANT,   "PUSH_CONSTANT"},

            {BCOpcodeType::TO_REG,          "TO_REG"},
            {BCOpcodeType::FROM_REG,        "FROM_REG"},

            {BCOpcodeType::SAVE,            "SAVE"},
            {BCOpcodeType::GET,             "GET"},

            {BCOpcodeType::CALL,            "CALL"},

            {BCOpcodeType::ADD,             "ADD"},
            {BCOpcodeType::SUB,             "SUB"},
            {BCOpcodeType::MUL,             "MUL"},
            {BCOpcodeType::DIV,             "DIV"},

            {BCOpcodeType::DONE,            "DONE"}
    };

}
