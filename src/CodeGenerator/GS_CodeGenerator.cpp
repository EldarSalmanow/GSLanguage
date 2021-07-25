#include <GS_CodeGenerator.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CodeGenerator::GS_CodeGenerator(Parser::GSNodePtrArray &nodes)
            : _nodes(nodes), _nodeIterator(_nodes.begin()) {}

    template<typename Out>
    Out castNodePtrTo(Parser::GSNodePtr &ptr) {
        return *dynamic_cast<Out *>(ptr.get());
    }

    GS_VMImageEncoder GS_CodeGenerator::codegen() {
        _encoder.emitFunction(0, "print");

        while (_nodeIterator != _nodes.end()) {
            switch (_nodeIterator[0]->getNodeType()) {
                case Parser::NodeType::VALUE_NODE:
                    _generateValueNode(_nodeIterator[0]);
                    break;
                case Parser::NodeType::UNARY_NODE:
                    _generateUnaryNode(_nodeIterator[0]);
                    break;
                case Parser::NodeType::BINARY_NODE:
                    _generateBinaryNode(_nodeIterator[0]);
                    break;
                case Parser::NodeType::VARIABLE_NODE:
                    _generateVariableNode(_nodeIterator[0]);
                    break;
                case Parser::NodeType::PRINT_NODE:
                    _generatePrintNode(_nodeIterator[0]);
                    break;
            }

            ++_nodeIterator;
        }

        _encoder.emitOpcode(Opcode::DONE);

        return _encoder;
    }

    GSVoid GS_CodeGenerator::_generateNode(Parser::GSNodePtr node) {
        switch (node->getNodeType()) {
            case Parser::NodeType::VALUE_NODE:
                _generateValueNode(node);
                break;
            case Parser::NodeType::UNARY_NODE:
                _generateUnaryNode(node);
                break;
            case Parser::NodeType::BINARY_NODE:
                _generateBinaryNode(node);
                break;
            case Parser::NodeType::VARIABLE_NODE:
                _generateVariableNode(node);
                break;
            case Parser::NodeType::PRINT_NODE:
                _generatePrintNode(node);
                break;
        }
    }

    GSVoid GS_CodeGenerator::_generateValueNode(Parser::GSNodePtr node) {
        _encoder.emitOpcode(Opcode::PUSH);

        _encoder.emitValue(static_cast<GSByte>(
                                   castNodePtrTo<Parser::GS_ValueNode>(
                                           node).getValue()->getData<int>()));
    }

    GSVoid GS_CodeGenerator::_generateUnaryNode(Parser::GSNodePtr node) {
        throw Exceptions::GS_Exception("Generating bytecode for unary nodes not supported!");
    }

    GSVoid GS_CodeGenerator::_generateBinaryNode(Parser::GSNodePtr node) {
        auto binaryNode = castNodePtrTo<Parser::GS_BinaryNode>(node);

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

        _encoder.emitOpcode(operation);
    }

    GSVoid GS_CodeGenerator::_generateVariableNode(Parser::GSNodePtr node) {
        static GSInt variableIndex = 0;

        auto variableNode = castNodePtrTo<Parser::GS_VariableNode>(node);

        auto name = variableNode.getName();
        auto type = variableNode.getType();
        auto expression = variableNode.getNode();

        if (type == "Int") {
            _encoder.emitNumberVariable(variableIndex, name);

            ++variableIndex;
        } else if (type == "String") {
            _encoder.emitStringVariable(variableIndex, name);

            ++variableIndex;
        } else {
            throw Exceptions::GS_Exception("Unknown type for variable!");
        }

        _generateNode(expression);
    }

    GSVoid GS_CodeGenerator::_generatePrintNode(Parser::GSNodePtr node) {
        static GSInt constantIndex = 0;

        auto printNode = castNodePtrTo<Parser::GS_PrintNode>(node);

        auto value = printNode.getString();

        _encoder.emitStringConstant(constantIndex, value.getData<GSString>());

        _encoder.emitOpcode(Opcode::PUSH);

        _encoder.emitValue(constantIndex);

        _encoder.emitOpcode(Opcode::TO_REG);

        _encoder.emitValue(0);

        _encoder.emitOpcode(Opcode::CALL);

        _encoder.emitValue(0);

        ++constantIndex;
    }

}