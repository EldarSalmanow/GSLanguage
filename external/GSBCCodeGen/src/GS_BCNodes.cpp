#include <GS_BCNodes.h>

#include <GS_BCVisitors.h>

namespace GSBCCodeGen {

    GS_BCNode::~GS_BCNode() = default;

    GS_BCRootNode::GS_BCRootNode()
            : _node(nullptr) {}

    GSBCNodePtr GS_BCRootNode::getNode() {
        return _node;
    }

    GSVoid GS_BCRootNode::setNode(GSBCNodePtr node) {
        _node = node;
    }

    BCNodeType GS_BCRootNode::getNodeType() {
        return BCNodeType::ROOT_NODE;
    }

    GSVoid GS_BCRootNode::accept(GS_BCVisitor *visitor) {
        visitor->visit(this);
    }

    GS_BCBlockNode::GS_BCBlockNode()
            : _nodes() {}

    GS_BCBlockNode::GS_BCBlockNode(GSBCNodePtrArray nodes)
            : _nodes(std::move(nodes)) {}

    GSVoid GS_BCBlockNode::addNode(GSBCNodePtr node) {
        _nodes.emplace_back(node);
    }

    GSBCNodePtrArray GS_BCBlockNode::getNodes() {
        return _nodes;
    }

    BCNodeType GS_BCBlockNode::getNodeType() {
        return BCNodeType::BLOCK_NODE;
    }

    GSVoid GS_BCBlockNode::accept(GS_BCVisitor *visitor) {
        visitor->visit(this);
    }

    GS_BCValueNode::GS_BCValueNode(GSInt value)
            : _value(value), _type("Int") {}

    GS_BCValueNode::GS_BCValueNode(GSString value)
            : _value(std::move(value)), _type("String") {}

    GSString GS_BCValueNode::getType() {
        return _type;
    }

    BCNodeType GS_BCValueNode::getNodeType() {
        return BCNodeType::VALUE_NODE;
    }

    GSVoid GS_BCValueNode::accept(GS_BCVisitor *visitor) {
        visitor->visit(this);
    }

    GS_BCInstructionNode::GS_BCInstructionNode(BCOpcodeType opcode)
            : _opcode(opcode) {}

    BCOpcodeType GS_BCInstructionNode::getOpcode() {
        return _opcode;
    }

    BCNodeType GS_BCInstructionNode::getNodeType() {
        return BCNodeType::INSTRUCTION_NODE;
    }

    GSVoid GS_BCInstructionNode::accept(GS_BCVisitor *visitor) {
        visitor->visit(this);
    }

    GS_BCInstructionWithOperandNode::GS_BCInstructionWithOperandNode(BCOpcodeType opcode, GS_BCValueNode valueNode)
            : GS_BCInstructionNode(opcode), _valueNode(std::move(valueNode)) {}

    GS_BCValueNode GS_BCInstructionWithOperandNode::getValueNode() {
        return _valueNode;
    }

    BCNodeType GS_BCInstructionWithOperandNode::getNodeType() {
        return BCNodeType::INSTRUCTION_WITH_OPERAND_NODE;
    }

    GSVoid GS_BCInstructionWithOperandNode::accept(GS_BCVisitor *visitor) {
        visitor->visit(this);
    }

    GS_BCInstructionWithTwoOperandsNode::GS_BCInstructionWithTwoOperandsNode(BCOpcodeType opcode,
                                                                             GS_BCValueNode firstValueNode,
                                                                             GS_BCValueNode secondValueNode)
            : GS_BCInstructionNode(opcode),
            _firstValueNode(std::move(firstValueNode)),
            _secondValueNode(std::move(secondValueNode)) {}

    GS_BCValueNode GS_BCInstructionWithTwoOperandsNode::getFirstValueNode() {
        return _firstValueNode;
    }

    GS_BCValueNode GS_BCInstructionWithTwoOperandsNode::getSecondValueNode() {
        return _secondValueNode;
    }

    BCNodeType GS_BCInstructionWithTwoOperandsNode::getNodeType() {
        return BCNodeType::INSTRUCTION_WITH_TWO_OPERANDS_NODE;
    }

    GSVoid GS_BCInstructionWithTwoOperandsNode::accept(GS_BCVisitor *visitor) {
        visitor->visit(this);
    }

}
