#include <GS_BCHighDecompiler.h>

namespace GSBCCodeGen {

    GS_BCHighDecompiler::GS_BCHighDecompiler(GSByteCode bytecode)
            : _decompiler(std::move(bytecode)), _rootNode(new GS_BCRootNode()), _blockNode(new GS_BCBlockNode()) {
        _rootNode->setNode(_blockNode);
    }

    GS_BCRootNode *GS_BCHighDecompiler::decompile() {
        for (; _decompiler.getOpcode() != BCOpcodeType::DONE; _decompiler.nextByte()) {
            GSBCNodePtr node;

            auto opcode = _decompiler.getOpcode();

//            if (opcode == BCOpcodeType::CONSTANT_STRING || opcode == BCOpcodeType::VARIABLE_NUMBER) {
//                _decompiler.nextByte();
//
//                auto id = _decompiler.getValue();
//
//                _decompiler.nextByte();
//
//                auto value = _decompiler.getString();
//
//                node = new GS_BCInstructionWithTwoOperandsNode(opcode,
//                                                               GS_BCValueNode(id),
//                                                               GS_BCValueNode(value));
//            } else if (opcode == BCOpcodeType::PUSH_CONSTANT
//                    || opcode == BCOpcodeType::TO_REG
//                    || opcode == BCOpcodeType::FROM_REG
//                    || opcode == BCOpcodeType::SAVE
//                    || opcode == BCOpcodeType::GET
//                    || opcode == BCOpcodeType::CALL
//                    || opcode == BCOpcodeType::PUSH) {
//                _decompiler.nextByte();
//
//                node = new GS_BCInstructionWithOperandNode(
//                        opcode,
//                        GS_BCValueNode(static_cast<GSInt>(_decompiler.getValue())));
//            } else {
//                node = new GS_BCInstructionNode(opcode);
//            }
//
//            _blockNode->addNode(node);
        }

        _blockNode->addNode(new GS_BCInstructionNode(BCOpcodeType::DONE));

        return _rootNode;
    }

}
