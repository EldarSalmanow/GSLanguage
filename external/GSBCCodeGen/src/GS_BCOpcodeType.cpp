#include <GS_BCOpcodeType.h>

namespace GSBCCodeGen {

    std::map<BCOpcodeType, GSByte> opcodeToByte = {
            {BCOpcodeType::CONSTANT, 0x10},

            {BCOpcodeType::VARIABLE, 0x11},

            {BCOpcodeType::PUSH_I,   0x12},
            {BCOpcodeType::PUSH_S,   0x13},
            {BCOpcodeType::POP,      0x14},

            {BCOpcodeType::TO_REG,   0x15},
            {BCOpcodeType::FROM_REG, 0x16},

            {BCOpcodeType::SAVE,     0x17},
            {BCOpcodeType::GET,      0x18},

            {BCOpcodeType::CMP,      0x19},

            {BCOpcodeType::JMP,      0x1a},
            {BCOpcodeType::JIE,      0x1b},
            {BCOpcodeType::JINE,     0x1c},
            {BCOpcodeType::JIG,      0x1e},
            {BCOpcodeType::JIL,      0x1f},
            {BCOpcodeType::JIEG,     0x21},
            {BCOpcodeType::JIEL,     0x22},

            {BCOpcodeType::CALL,     0x23},

            {BCOpcodeType::I2S,      0x24},
            {BCOpcodeType::S2I,      0x25},

            {BCOpcodeType::ADD,      0x26},
            {BCOpcodeType::SUB,      0x27},
            {BCOpcodeType::MUL,      0x28},
            {BCOpcodeType::DIV,      0x29},

            {BCOpcodeType::DONE,     0xff}
    };

    std::map<GSByte, BCOpcodeType> byteToOpcode = {
            {0x10, BCOpcodeType::CONSTANT},

            {0x11, BCOpcodeType::VARIABLE},

            {0x12, BCOpcodeType::PUSH_I},
            {0x13, BCOpcodeType::PUSH_S},
            {0x14, BCOpcodeType::POP},

            {0x15, BCOpcodeType::TO_REG},
            {0x16, BCOpcodeType::FROM_REG},

            {0x17, BCOpcodeType::SAVE},
            {0x18, BCOpcodeType::GET},

            {0x19, BCOpcodeType::CMP},

            {0x1a, BCOpcodeType::JMP},
            {0x1b, BCOpcodeType::JIE},
            {0x1c, BCOpcodeType::JINE},
            {0x1e, BCOpcodeType::JIG},
            {0x1f, BCOpcodeType::JIL},
            {0x21, BCOpcodeType::JIEG},
            {0x22, BCOpcodeType::JIEL},

            {0x23, BCOpcodeType::CALL},

            {0x24, BCOpcodeType::I2S},
            {0x25, BCOpcodeType::S2I},

            {0x26, BCOpcodeType::ADD},
            {0x27, BCOpcodeType::SUB},
            {0x28, BCOpcodeType::MUL},
            {0x29, BCOpcodeType::DIV},

            {0xff, BCOpcodeType::DONE}
    };

    std::map<BCOpcodeType, GSString> opcodeToString = {
            {BCOpcodeType::CONSTANT, "CONSTANT"},

            {BCOpcodeType::VARIABLE, "VARIABLE"},

            {BCOpcodeType::PUSH_I,   "PUSH_I"},
            {BCOpcodeType::PUSH_S,   "PUSH_S"},
            {BCOpcodeType::POP,      "POP"},

            {BCOpcodeType::TO_REG,   "TO_REG"},
            {BCOpcodeType::FROM_REG, "FROM_REG"},

            {BCOpcodeType::SAVE,     "SAVE"},
            {BCOpcodeType::GET,      "GET"},

            {BCOpcodeType::JMP,      "JMP"},
            {BCOpcodeType::JIE,      "JIE"},
            {BCOpcodeType::JINE,     "JINE"},
            {BCOpcodeType::JIG,      "JIG"},
            {BCOpcodeType::JIL,      "JIL"},
            {BCOpcodeType::JIEG,     "JIEG"},
            {BCOpcodeType::JIEL,     "JIEL"},

            {BCOpcodeType::CALL,     "CALL"},

            {BCOpcodeType::I2S,      "I2S"},
            {BCOpcodeType::S2I,      "S2I"},

            {BCOpcodeType::ADD,      "ADD"},
            {BCOpcodeType::SUB,      "SUB"},
            {BCOpcodeType::MUL,      "MUL"},
            {BCOpcodeType::DIV,      "DIV"},

            {BCOpcodeType::DONE,     "DONE"}
    };

}
