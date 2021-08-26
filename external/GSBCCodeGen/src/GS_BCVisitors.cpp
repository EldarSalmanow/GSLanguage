#include <GS_BCVisitors.h>

#include <GS_BCNodes.h>

namespace GSBCCodeGen {

    GS_BCVisitor::~GS_BCVisitor() = default;

    GS_BCLabelsTable::GS_BCLabelsTable() = default;

    GSVoid GS_BCLabelsTable::addLabel(GSString name, GSInt offset) {
        _labelNameToOffset[std::move(name)] = offset;
    }

    GSInt GS_BCLabelsTable::findLabelOffsetByName(GSString name) {
        return _labelNameToOffset[std::move(name)];
    }

    GS_BCLabelVisitor::GS_BCLabelVisitor() = default;

    GS_BCLabelsTable GS_BCLabelVisitor::getLabelsTable() {
        return _labelsTable;
    }

    GSVoid GS_BCLabelVisitor::visit(GS_BCRootNode *rootNode) {
        _offsetFromStart = 0;

        rootNode->getNode()->accept(this);
    }

    GSVoid GS_BCLabelVisitor::visit(GS_BCBlockNode *blockNode) {
        for (auto &node : blockNode->getNodes()) {
            node->accept(this);
        }
    }

    GSVoid GS_BCLabelVisitor::visit(GS_BCValueNode *valueNode) {
        auto type = valueNode->getType();

        if (type == "Int") {
            _offsetFromStart += 1;
        } else if (type == "String") {
            _offsetFromStart += static_cast<GSInt>(valueNode->getValue<GSString>().size());
        } else {
            throw std::runtime_error("Unknown value type!");
        }
    }

    GSVoid GS_BCLabelVisitor::visit(GS_BCInstructionNode *instructionNode) {
        _offsetFromStart += 1;
    }

    GSVoid GS_BCLabelVisitor::visit(GS_BCInstructionWithOperandNode *instructionWithOperandNode) {
        _offsetFromStart += 1;

        instructionWithOperandNode->getValueNode().accept(this);
    }

    GSVoid GS_BCLabelVisitor::visit(GS_BCInstructionWithTwoOperandsNode *instructionWithTwoOperandsNode) {
        _offsetFromStart += 1;

        instructionWithTwoOperandsNode->getFirstValueNode().accept(this);

        instructionWithTwoOperandsNode->getSecondValueNode().accept(this);
    }

    GSVoid GS_BCLabelVisitor::visit(GS_BCLabelNode *labelNode) {
        _labelsTable.addLabel(labelNode->getName().getValue<GSString>(), _offsetFromStart + 1);
    }

    GSVoid GS_BCLabelVisitor::visit(GS_BCCFInstructionNode *cfInstructionNode) {
        _offsetFromStart += 3;

        cfInstructionNode->setFrom(GS_BCValueNode(_offsetFromStart));
    }

    GS_BCCodeGenVisitor::GS_BCCodeGenVisitor(GS_BCLabelsTable labelsTable)
            : _labelsTable(std::move(labelsTable)) {}

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

    GSVoid GS_BCCodeGenVisitor::visit(GS_BCLabelNode *labelNode) {}

    GSVoid GS_BCCodeGenVisitor::visit(GS_BCCFInstructionNode *cfInstructionNode) {
        _bytecode.emplace_back(opcodeToByte[cfInstructionNode->getOpcode()]);

        auto from = cfInstructionNode->getFrom().getValue<GSInt>();

        auto to = cfInstructionNode->getTo();

        auto labelAddress = _labelsTable.findLabelOffsetByName(to.getName().getValue<GSString>());

        if (labelAddress < from) {
            _bytecode.emplace_back(0);
        
            _bytecode.emplace_back(from - labelAddress);
        } else {
            _bytecode.emplace_back(1);
            
            _bytecode.emplace_back(labelAddress - from);
        }
    }

    GS_BCPrintVisitor::GS_BCPrintVisitor(GS_BCLabelsTable labelsTable)
            : _labelsTable(std::move(labelsTable)), _tabsCol(0) {};

    GSVoid GS_BCPrintVisitor::visit(GS_BCRootNode *rootNode) {
        std::cerr << "RootNode {" << std::endl;

        _incrTab();

        rootNode->getNode()->accept(this);

        _decrTab();

        std::cerr << "}" << std::endl;
    }

    GSVoid GS_BCPrintVisitor::visit(GS_BCBlockNode *blockNode) {
        _printTabs();

        std::cerr << "BlockNode {" << std::endl;

        _incrTab();

        for (auto &node : blockNode->getNodes()) {
            node->accept(this);
        }

        _decrTab();

        _printTabs();

        std::cerr << "}" << std::endl;
    }

    GSVoid GS_BCPrintVisitor::visit(GS_BCValueNode *valueNode) {
        _printTabs();

        std::cerr << "ValueNode {" << std::endl;

        _incrTab();

        _printTabs();

        auto type = valueNode->getType();

        if (type == "Int") {
            std::cerr << "Value: " << valueNode->getValue<GSInt>() << std::endl;

            _printTabs();

            std::cerr << "Type: Int" << std::endl;
        } else if (type == "String") {
            std::cerr << "Value: " << valueNode->getValue<GSString>() << std::endl;

            _printTabs();

            std::cerr << "Type: String" << std::endl;
        } else {
            throw std::runtime_error("Invalid type for printing nodes!");
        }

        _decrTab();

        _printTabs();

        std::cerr << "}" << std::endl;
    }

    GSVoid GS_BCPrintVisitor::visit(GS_BCInstructionNode *instructionNode) {
        _printTabs();

        std::cerr << "InstructionNode {" << std::endl;

        _incrTab();

        _printTabs();

        std::cerr << "Opcode: " << opcodeToString[instructionNode->getOpcode()] << std::endl;

        _decrTab();

        _printTabs();

        std::cerr << "}" << std::endl;
    }

    GSVoid GS_BCPrintVisitor::visit(GS_BCInstructionWithOperandNode *instructionWithOperandNode) {
        _printTabs();

        std::cerr << "InstructionWithOperandNode {" << std::endl;

        _incrTab();

        _printTabs();

        std::cerr << "Opcode: " << opcodeToString[instructionWithOperandNode->getOpcode()] << std::endl;

        instructionWithOperandNode->getValueNode().accept(this);

        _decrTab();

        _printTabs();

        std::cerr << "}" << std::endl;
    }

    GSVoid GS_BCPrintVisitor::visit(GS_BCInstructionWithTwoOperandsNode *instructionWithTwoOperandsNode) {
        _printTabs();

        std::cerr << "InstructionWithTwoOperandsNode {" << std::endl;

        _incrTab();

        _printTabs();

        std::cerr << "Opcode: " << opcodeToString[instructionWithTwoOperandsNode->getOpcode()] << std::endl;

        instructionWithTwoOperandsNode->getFirstValueNode().accept(this);

        instructionWithTwoOperandsNode->getSecondValueNode().accept(this);

        _decrTab();

        _printTabs();

        std::cerr << "}" << std::endl;
    }

    GSVoid GS_BCPrintVisitor::visit(GS_BCLabelNode *labelNode) {
        _printTabs();

        std::cerr << "LabelNode {\n";

        _incrTab();

        _printTabs();

        std::cerr << "Name: " << labelNode->getName().getValue<GSString>() << std::endl;

        _printTabs();

        std::cerr << "Address: " << _labelsTable.findLabelOffsetByName(labelNode->getName().getValue<GSString>()) << std::endl;

        _decrTab();

        _printTabs();

        std::cerr << "}" << std::endl;
    }

    GSVoid GS_BCPrintVisitor::visit(GS_BCCFInstructionNode *cfInstructionNode) {
        _printTabs();

        std::cerr << "CFInstructionNode {" << std::endl;

        _incrTab();

        _printTabs();

        std::cerr << "Opcode: " << opcodeToString[cfInstructionNode->getOpcode()] << std::endl;

        _printTabs();

        std::cerr << "From: " << cfInstructionNode->getFrom().getValue<GSInt>() << std::endl;

        _printTabs();

        std::cerr << "To: " << _labelsTable.findLabelOffsetByName(cfInstructionNode->getTo().getName().getValue<GSString>()) << std::endl;

        _decrTab();

        _printTabs();

        std::cerr << "}" << std::endl;
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
