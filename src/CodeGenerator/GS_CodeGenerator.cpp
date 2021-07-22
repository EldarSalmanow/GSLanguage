#include <GS_CodeGenerator.h>

namespace GSLanguageCompiler::CodeGenerator {

    std::map<Opcode, Byte> opcodeToByte = {
            {Opcode::PUSH,       0x0},
            {Opcode::POP,        0x1},

            {Opcode::ADD,        0x2},
            {Opcode::SUB,        0x3},

            {Opcode::TO_REG_1,   0xf},
            {Opcode::FROM_REG_1, 0xf1},

            {Opcode::TO_REG_2,   0xf2},
            {Opcode::FROM_REG_2, 0xf3},

            {Opcode::TO_REG_3,   0xf4},
            {Opcode::FROM_REG_3, 0xf5},

            {Opcode::DONE,       0xff},
    };

    GS_CodeGenerator::GS_CodeGenerator(Parser::GSNodePtrArray &nodes)
            : _nodes(nodes), _nodeIterator(_nodes.begin()) {}

    template<typename Out>
    Out castNodePtrTo(Parser::GSNodePtr &ptr) {
        return *dynamic_cast<Out*>(ptr.get());
    }

    GSByteCode GS_CodeGenerator::codegen() {
        while (_nodeIterator != _nodes.end()) {
            switch (_nodeIterator[0]->getNodeType()) {
                case Parser::NodeType::VALUE_NODE:
                    _generateValueNode();
                    break;
                case Parser::NodeType::UNARY_NODE:
                    _generateUnaryNode();
                    break;
                case Parser::NodeType::BINARY_NODE:
                    _generateBinaryNode();
                    break;
            }

            ++_nodeIterator;
        }

	_bytecode.emplace_back(opcodeToByte[Opcode::DONE]);

        return _bytecode;
    }

    GSVoid GS_CodeGenerator::_generateNode(Parser::GSNodePtr node) {
        switch (_nodeIterator[0]->getNodeType()) {
            case Parser::NodeType::VALUE_NODE:
                _generateValueNode();
                break;
            case Parser::NodeType::UNARY_NODE:
                _generateUnaryNode();
                break;
            case Parser::NodeType::BINARY_NODE:
                _generateBinaryNode();
                break;
        }
    }

    GSVoid GS_CodeGenerator::_generateValueNode() {
        auto valueNode = castNodePtrTo<Parser::GS_ValueNode>(_nodeIterator[0]);

        _bytecode.emplace_back(opcodeToByte[Opcode::PUSH]);

        auto byteValue = static_cast<Byte>(valueNode.getValue()->getData<int>());

        _bytecode.emplace_back(byteValue);
    }

    GSVoid GS_CodeGenerator::_generateUnaryNode() {
        throw Exceptions::GS_Exception("Generating bytecode for unary node not supported!");
    }

    GSVoid GS_CodeGenerator::_generateBinaryNode() {
        auto binaryNode = castNodePtrTo<Parser::GS_BinaryNode>(_nodeIterator[0]);

        _generateNode(binaryNode.getFirstNode());
        _generateNode(binaryNode.getSecondNode());

        Byte operation;

        switch (binaryNode.getBinaryOperation()) {
            case Parser::BinaryOperation::PLUS:
                operation = opcodeToByte[Opcode::ADD];
                break;
            case Parser::BinaryOperation::MINUS:
                operation = opcodeToByte[Opcode::SUB];
                break;
            case Parser::BinaryOperation::STAR:
                throw Exceptions::GS_Exception("Generating for star operation in binary node not supported!");
            case Parser::BinaryOperation::SLASH:
                throw Exceptions::GS_Exception("Generating for slash operation in binary node not supported!");
        }

        _bytecode.emplace_back(operation);
    }

}