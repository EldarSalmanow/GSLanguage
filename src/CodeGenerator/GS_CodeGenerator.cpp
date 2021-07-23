#include <GS_CodeGenerator.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CodeGenerator::GS_CodeGenerator(Parser::GSNodePtrArray &nodes)
            : _nodes(nodes), _nodeIterator(_nodes.begin()) {}

    template<typename Out>
    Out castNodePtrTo(Parser::GSNodePtr &ptr) {
        return *dynamic_cast<Out*>(ptr.get());
    }

    GS_VMImage GS_CodeGenerator::codegen() {
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

        _vmImage.emitConstantValue(0, 12);
        _vmImage.emitVariable(0, "x");

        _vmImage.emitOpcode(Opcode::DONE);

        return _vmImage;
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
        _vmImage.emitOpcode(Opcode::PUSH);

        _vmImage.emitValue(static_cast<GSByte>(
                castNodePtrTo<Parser::GS_ValueNode>(
                        _nodeIterator[0]).getValue()->getData<int>()));
    }

    GSVoid GS_CodeGenerator::_generateUnaryNode() {
        throw Exceptions::GS_Exception("Generating bytecode for unary nodes not supported!");
    }

    GSVoid GS_CodeGenerator::_generateBinaryNode() {
        auto binaryNode = castNodePtrTo<Parser::GS_BinaryNode>(_nodeIterator[0]);

        _generateNode(binaryNode.getFirstNode());
        _generateNode(binaryNode.getSecondNode());

        Opcode operation;

        switch (binaryNode.getBinaryOperation()) {
            case Parser::BinaryOperation::PLUS:
                operation = Opcode::ADD;
                break;
            case Parser::BinaryOperation::MINUS:
                operation = Opcode::SUB;
                break;
            case Parser::BinaryOperation::STAR:
                operation = Opcode::MUL;
                break;
            case Parser::BinaryOperation::SLASH:
                operation = Opcode::DIV;
                break;
        }

        _vmImage.emitOpcode(operation);
    }

}