#include <GS_BCLowDecompiler.h>

namespace GSBCCodeGen {

    GS_BCLowDecompiler::GS_BCLowDecompiler(GSByteCode bytecode)
            : _bytecode(std::move(bytecode)), _bytecodeIterator(_bytecode.begin()) {}

    GSByte GS_BCLowDecompiler::getValue() {
        if (_bytecodeIterator == _bytecode.end()) {
            throw std::runtime_error("Bytecode is ended!");
        }

        return _bytecodeIterator[0];
    }

    GSString GS_BCLowDecompiler::getString() {
        GSString string;

        while (true) {
            auto symbol = getValue();

            if (symbol == 0) {
                break;
            }

            string += static_cast<GSChar>(symbol);

            nextByte();
        }

        return string;
    }

    BCOpcodeType GS_BCLowDecompiler::getOpcode() {
        return byteToOpcode[getValue()];
    }

    GSVoid GS_BCLowDecompiler::nextByte() {
        ++_bytecodeIterator;
    }

}
