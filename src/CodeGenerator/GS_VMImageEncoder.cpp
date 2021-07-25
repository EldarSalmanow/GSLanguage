#include <GS_VMImageEncoder.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_VMImageEncoder::GS_VMImageEncoder() = default;

    GSVoid GS_VMImageEncoder::emitOpcode(Opcode opcode) {
        _bytecode.emplace_back(opcodeToByte[opcode]);
    }

    GSVoid GS_VMImageEncoder::emitNumberConstant(GSInt index, GSInt value) {
        _constantTable.emplace_back(opcodeToByte[Opcode::CONSTANT_NUMBER]);

        _constantTable.emplace_back(static_cast<GSByte>(index));

        _constantTable.emplace_back(static_cast<GSByte>(value));
    }

    GSVoid GS_VMImageEncoder::emitStringConstant(GSInt index, GSString value) {
        _constantTable.emplace_back(opcodeToByte[Opcode::CONSTANT_STRING]);

        _constantTable.emplace_back(static_cast<GSByte>(index));

        for (GSInt i = 0; i < value.size(); ++i) {
            _constantTable.emplace_back(value[i]);
        }

        _constantTable.emplace_back(0x0);
    }

    GSVoid GS_VMImageEncoder::emitNumberVariable(GSInt index, GSString variableName) {
        _variableTable.emplace_back(opcodeToByte[Opcode::VARIABLE_NUMBER]);

        _variableTable.emplace_back(static_cast<GSByte>(index));

        for (GSInt i = 0; i < variableName.size(); ++i) {
            _variableTable.emplace_back(variableName[i]);
        }

        _variableTable.emplace_back(0x0);
    }

    GSVoid GS_VMImageEncoder::emitStringVariable(GSInt index, GSString variableName) {
        _variableTable.emplace_back(opcodeToByte[Opcode::VARIABLE_STRING]);

        _variableTable.emplace_back(static_cast<GSByte>(index));

        for (GSInt i = 0; i < variableName.size(); ++i) {
            _variableTable.emplace_back(variableName[i]);
        }

        _variableTable.emplace_back(0x0);
    }

    GSVoid GS_VMImageEncoder::emitFunction(GSInt index, GSString functionName) {
        _variableTable.emplace_back(opcodeToByte[Opcode::FUNCTION]);

        _variableTable.emplace_back(static_cast<GSByte>(index));

        for (GSInt i = 0; i < functionName.size(); ++i) {
            _variableTable.emplace_back(functionName[i]);
        }

        _variableTable.emplace_back(0x0);
    }

    GSVoid GS_VMImageEncoder::emitValue(GSByte byte) {
        _bytecode.emplace_back(byte);
    }

    GSByteCode GS_VMImageEncoder::getByteCode() {
        GSByteCode bytecode;

        for (auto &byte : _constantTable) {
            bytecode.emplace_back(byte);
        }

        for (auto &byte : _variableTable) {
            bytecode.emplace_back(byte);
        }

        for (auto &byte : _functionTable) {
            bytecode.emplace_back(byte);
        }

        for (auto &byte : _bytecode) {
            bytecode.emplace_back(byte);
        }

        return bytecode;
    }

}