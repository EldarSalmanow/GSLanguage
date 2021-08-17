#include <Nodes/Visitors/GS_PrintVisitor.h>

#include <GS_IncludeNodes.h>

namespace GSLanguageCompiler::Parser {

    GS_PrintVisitor::GS_PrintVisitor() = default;

    GSVoid GS_PrintVisitor::visit(GS_ValueNode *valueNode) {
        _printTabs();
        
        std::cerr << "ValueNode {" << std::endl;
        
        _incrTab();
        
        auto value = valueNode->getValue();
        
        auto type = value->getType();
        
        _printTabs();
        
        if (type == "Int") {
            std::cerr << "Value: " << value->getData<GSInt>() << std::endl;
        } else if (type == "String") {
            std::cerr << "Value: \"" << value->getData<GSString>() << "\"" << std::endl;
        } else {
            throw Exceptions::GS_Exception("Invalid type for printing node information!");
        }
        
        _printTabs();
        
        std::cerr << "Type: " << type << std::endl;
        
        _decrTab();
        
        _printTabs();
        
        std::cerr << "}" << std::endl;
    }

    GSVoid GS_PrintVisitor::visit(GS_UnaryNode *unaryNode) {
        _printTabs();
        
        std::cerr << "UnaryNode: {" << std::endl;
        
        _incrTab();
        
        _printTabs();
        
        std::cerr << "UnaryOperation: " << unaryOperationToString[unaryNode->getUnaryOperation()] << std::endl;
        
        unaryNode->getNode()->accept(this);
        
        _decrTab();
        
        _printTabs();
        
        std::cerr << "}" << std::endl;
    }

    GSVoid GS_PrintVisitor::visit(GS_BinaryNode *binaryNode) {
        _printTabs();
        
        std::cerr << "BinaryNode: {" << std::endl;
        
        _incrTab();

        _printTabs();
        
        std::cerr << "BinaryOperation: " << binaryOperationToString[binaryNode->getBinaryOperation()] << std::endl;
        
        binaryNode->getFirstNode()->accept(this);
        
        binaryNode->getSecondNode()->accept(this);
        
        _decrTab();
        
        _printTabs();
        
        std::cerr << "}" << std::endl;
    }
    
    GSVoid GS_PrintVisitor::visit(GS_VariableNode *variableNode) {
        _printTabs();
        
        std::cerr << "VariableNode {" << std::endl;
        
        _incrTab();
        
        _printTabs();
        
        std::cerr << "Name: " << variableNode->getName() << std::endl;
        
        _printTabs();
        
        std::cerr << "Type: " << variableNode->getType() << std::endl;
        
        variableNode->getNode()->accept(this);
        
        _decrTab();
        
        _printTabs();
        
        std::cerr << "}" << std::endl;
    }

    GSVoid GS_PrintVisitor::visit(GS_PrintNode *printNode) {
        _printTabs();
        
        std::cerr << "PrintNode {" << std::endl;
        
        _incrTab();
        
        _printTabs();
        
        auto value = printNode->getValue();
        
        auto type = value->getType();
        
        if (type == "Int") {
            std::cerr << "Value: " << value->getData<GSInt>() << std::endl;
        } else if (type == "String") {
            std::cerr << "Value: \"" << value->getData<GSString>() << "\"" << std::endl;
        } else {
            throw Exceptions::GS_Exception("Invalid type for printing node information!");
        }
        
        _printTabs();
        
        std::cerr << "Type: " << type << std::endl;
        
        _decrTab();
        
        _printTabs();
        
        std::cerr << "}" << std::endl;
    }
    
    GSVoid GS_PrintVisitor::_printTabs() {
        for (GSInt number = 0; number < _tabsCol; ++number) {
            std::cerr << "\t";
        }
    }

    GSVoid GS_PrintVisitor::_incrTab() {
        ++_tabsCol;
    }

    GSVoid GS_PrintVisitor::_decrTab() {
        --_tabsCol;
    }
    
}
