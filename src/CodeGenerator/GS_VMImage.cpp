#include <GS_VMImage.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_VMImage::GS_VMImage() = default;

    GSVoid GS_VMImage::emitOpcode(Opcode opcode) {
        _bytecode.emplace_back(opcodeToByte[opcode]);
    }

    GSVoid GS_VMImage::emitValue(GSByte byte) {
        _bytecode.emplace_back(byte);
    }

//    GSByteCode GS_VMImage::getByteCode() {
//        return _bytecode;
//    }

}