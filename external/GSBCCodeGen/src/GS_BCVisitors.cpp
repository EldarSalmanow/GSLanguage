#include <GS_BCVisitors.h>

#include <GS_BCNodes.h>

namespace GSBCCodeGen {

    GS_BCVisitor::~GS_BCVisitor() = default;

    GS_BCCodeGenVisitor::GS_BCCodeGenVisitor() = default;

    GSByteCode GS_BCCodeGenVisitor::getBytecode() {
        return _bytecode;
    }

    GSVoid GS_BCCodeGenVisitor::visit(GS_BCRootNode *rootNode) {
        rootNode->getNode()->accept(this);
    }

    GSVoid GS_BCCodeGenVisitor::visit(GS_BCBlockNode *blockNode) {
        for (auto &node : blockNode->getNodes()) {
            node->accept(this);
        }
    }

    GSVoid GS_BCCodeGenVisitor::visit(GS_BCValueNode *valueNode) {
        auto type = valueNode->getType();

        if (type == "Int") {
            _bytecode.emplace_back(static_cast<GSByte>(valueNode->getValue<GSInt>()));
        } else if (type == "String") {
            for (auto &symbol : valueNode->getValue<GSString>()) {
                _bytecode.emplace_back(static_cast<GSByte>(symbol));
            }

            _bytecode.emplace_back(0);
        } else {
            throw std::runtime_error("Invalid type for code generation!");
        }
    }

    GSVoid GS_BCCodeGenVisitor::visit(GS_BCInstructionNode *instructionNode) {
        _bytecode.emplace_back(opcodeToByte[instructionNode->getOpcode()]);
    }

    GSVoid GS_BCCodeGenVisitor::visit(GS_BCInstructionWithOperandNode *instructionWithOperandNode) {
        _bytecode.emplace_back(opcodeToByte[instructionWithOperandNode->getOpcode()]);

        auto valueNode = instructionWithOperandNode->getValueNode();

        visit(&valueNode);
    }

    GSVoid GS_BCCodeGenVisitor::visit(GS_BCInstructionWithTwoOperandsNode *instructionWithTwoOperandsNode) {
        _bytecode.emplace_back(opcodeToByte[instructionWithTwoOperandsNode->getOpcode()]);

        auto firstValueNode = instructionWithTwoOperandsNode->getFirstValueNode();

        visit(&firstValueNode);

        auto secondValueNode = instructionWithTwoOperandsNode->getSecondValueNode();

        visit(&secondValueNode);
    }

    GS_BCPrintVisitor::GS_BCPrintVisitor()
            : _tabsCol(0) {};

    GSVoid GS_BCPrintVisitor::visit(GS_BCRootNode *rootNode) {
        std::cerr << "RootNode {\n";

        _incrTab();

        rootNode->getNode()->accept(this);

        _decrTab();

        std::cerr << "}\n";
    }

    GSVoid GS_BCPrintVisitor::visit(GS_BCBlockNode *blockNode) {
        _printTabs();

        std::cerr << "BlockNode {\n";

        _incrTab();

        for (auto &node : blockNode->getNodes()) {
            node->accept(this);
        }

        _decrTab();

        _printTabs();

        std::cerr << "}\n";
    }

    GSVoid GS_BCPrintVisitor::visit(GS_BCValueNode *valueNode) {
        _printTabs();

        std::cerr << "ValueNode {\n";

        _incrTab();

        _printTabs();

        auto type = valueNode->getType();

        if (type == "Int") {
            std::cerr << "Value: " << valueNode->getValue<GSInt>() << "\n";

            _printTabs();

            std::cerr << "Type: Int\n";
        } else if (type == "String") {
            std::cerr << "Value: " << valueNode->getValue<GSString>() << "\n";

            _printTabs();

            std::cerr << "Type: String\n";
        } else if (type == "VoidFunction") {
            std::cerr << "Type: VoidFunction\n";
        } else {
            throw std::runtime_error("Invalid type for printing nodes!");
        }

        _decrTab();

        _printTabs();

        std::cerr << "}\n";
    }

    GSVoid GS_BCPrintVisitor::visit(GS_BCInstructionNode *instructionNode) {
        _printTabs();

        std::cerr << "InstructionNode {\n";

        _incrTab();

        _printTabs();

        std::cerr << "Opcode: " << opcodeToString[instructionNode->getOpcode()] << "\n";

        _decrTab();

        _printTabs();

        std::cerr << "}\n";
    }

    GSVoid GS_BCPrintVisitor::visit(GS_BCInstructionWithOperandNode *instructionWithOperandNode) {
        _printTabs();

        std::cerr << "InstructionWithOperandNode {\n";

        _incrTab();

        _printTabs();

        std::cerr << "Opcode: " << opcodeToString[instructionWithOperandNode->getOpcode()] << "\n";

        instructionWithOperandNode->getValueNode().accept(this);

        _decrTab();

        _printTabs();

        std::cerr << "}\n";
    }

    GSVoid GS_BCPrintVisitor::visit(GS_BCInstructionWithTwoOperandsNode *instructionWithTwoOperandsNode) {
        _printTabs();

        std::cerr << "InstructionWithTwoOperandsNode {\n";

        _incrTab();

        _printTabs();

        std::cerr << "Opcode: " << opcodeToString[instructionWithTwoOperandsNode->getOpcode()] << "\n";

        instructionWithTwoOperandsNode->getFirstValueNode().accept(this);

        instructionWithTwoOperandsNode->getSecondValueNode().accept(this);

        _decrTab();

        _printTabs();

        std::cerr << "}\n";
    }

    GSVoid GS_BCPrintVisitor::_incrTab() {
        ++_tabsCol;
    }

    GSVoid GS_BCPrintVisitor::_decrTab() {
        --_tabsCol;
    }

    GSVoid GS_BCPrintVisitor::_printTabs() {
        for (GSInt col = 0; col < _tabsCol; ++col) {
            std::cerr << "\t";
        }
    }

}
