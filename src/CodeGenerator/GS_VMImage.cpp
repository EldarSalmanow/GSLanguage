#include <GS_VMImage.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_VMImage::GS_VMImage() = default;

    GSVoid GS_VMImage::emitOpcode(Opcode opcode) {
        _bytecode.emplace_back(opcodeToByte[opcode]);
    }

    GSVoid GS_VMImage::emitConstantValue(GSInt index, GSInt value) {
        _constantTable.emplace_back(opcodeToByte[Opcode::CONSTANT]);

        _constantTable.emplace_back(index);

        _constantTable.emplace_back(value);
    }

    GSVoid GS_VMImage::emitVariable(GSInt index, GSString variableName) {
        _variablesTable.emplace_back(opcodeToByte[Opcode::VARIABLE]);

        _variablesTable.emplace_back(index);

        for (GSInt i = 0; i < variableName.size(); ++i) {
            _variablesTable.emplace_back(variableName[i]);
        }

        _variablesTable.emplace_back(0x0);
    }

    GSVoid GS_VMImage::emitValue(GSByte byte) {
        _bytecode.emplace_back(byte);
    }

    GSByteCode GS_VMImage::getByteCode() {
        GSByteCode bytecode;

        for (auto &byte : _constantTable) {
            bytecode.emplace_back(byte);
        }

        for (auto &byte : _variablesTable) {
            bytecode.emplace_back(byte);
        }

        for (auto &byte : _bytecode) {
            bytecode.emplace_back(byte);
        }

        return bytecode;
    }

}