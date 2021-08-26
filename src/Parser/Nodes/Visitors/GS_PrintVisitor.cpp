#include <Nodes/Visitors/GS_PrintVisitor.h>

#include <GS_IncludeNodes.h>

namespace GSLanguageCompiler::Parser {

    GS_PrintVisitor::GS_PrintVisitor()
            : _tabsCol(0) {};

    GSVoid GS_PrintVisitor::visit(GS_RootNode *rootNode) {
        std::cout << "RootNode {" << std::endl;

        _incrTab();

        rootNode->getNode()->accept(this);

        _decrTab();

        _printTabs();

        std::cout << "}" << std::endl;
    }

    GSVoid GS_PrintVisitor::visit(GS_BlockNode *blockNode) {
        _printTabs();

        std::cout << "BlockNode {" << std::endl;

        _incrTab();

        for (auto &node : blockNode->getNodes()) {
            node->accept(this);
        }

        _decrTab();

        _printTabs();

        std::cout << "}" << std::endl;
    }

    GSVoid GS_PrintVisitor::visit(GS_ValueNode *valueNode) {
        _printTabs();
        
        std::cout << "ValueNode {" << std::endl;
        
        _incrTab();
        
        auto value = valueNode->getValue();
        
        auto type = value->getType();
        
        _printTabs();
        
        if (type == "Int") {
            std::cout << "Value: " << value->getData<GSInt>() << std::endl;
        } else if (type == "String") {
            std::cout << "Value: \"" << value->getData<GSString>() << "\"" << std::endl;
        } else {
            Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                           "Invalid type for printing node information!");

            Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                           "Please, report this error to GSLanguageCompiler repository.");

            Exceptions::errorHandler.throw_();
        }
        
        _printTabs();
        
        std::cout << "Type: " << type << std::endl;
        
        _decrTab();
        
        _printTabs();
        
        std::cout << "}" << std::endl;
    }

    GSVoid GS_PrintVisitor::visit(GS_UnaryNode *unaryNode) {
        _printTabs();
        
        std::cout << "UnaryNode: {" << std::endl;
        
        _incrTab();
        
        _printTabs();
        
        std::cout << "UnaryOperation: " << unaryOperationToString[unaryNode->getUnaryOperation()] << std::endl;
        
        unaryNode->getNode()->accept(this);
        
        _decrTab();
        
        _printTabs();
        
        std::cout << "}" << std::endl;
    }

    GSVoid GS_PrintVisitor::visit(GS_BinaryNode *binaryNode) {
        _printTabs();
        
        std::cout << "BinaryNode: {" << std::endl;
        
        _incrTab();

        _printTabs();
        
        std::cout << "BinaryOperation: " << binaryOperationToString[binaryNode->getBinaryOperation()] << std::endl;
        
        binaryNode->getFirstNode()->accept(this);
        
        binaryNode->getSecondNode()->accept(this);
        
        _decrTab();
        
        _printTabs();
        
        std::cout << "}" << std::endl;
    }
    
    GSVoid GS_PrintVisitor::visit(GS_VariableNode *variableNode) {
        _printTabs();
        
        std::cout << "VariableNode {" << std::endl;
        
        _incrTab();
        
        _printTabs();
        
        std::cout << "Name: " << variableNode->getName() << std::endl;
        
        _printTabs();
        
        std::cout << "Type: " << variableNode->getType() << std::endl;
        
        variableNode->getNode()->accept(this);
        
        _decrTab();
        
        _printTabs();
        
        std::cout << "}" << std::endl;
    }

    GSVoid GS_PrintVisitor::visit(GS_PrintNode *printNode) {
        _printTabs();
        
        std::cout << "PrintNode {" << std::endl;
        
        _incrTab();
        
        _printTabs();
        
        auto value = printNode->getValue();
        
        auto type = value->getType();
        
        if (type == "Int") {
            std::cout << "Value: " << value->getData<GSInt>() << std::endl;
        } else if (type == "String") {
            std::cout << "Value: \"" << value->getData<GSString>() << "\"" << std::endl;
        } else {
            Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                           "Invalid type for printing node information!");

            Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                           "Please, report this error to GSLanguageCompiler repository.");

            Exceptions::errorHandler.throw_();
        }
        
        _printTabs();
        
        std::cout << "Type: " << type << std::endl;
        
        _decrTab();
        
        _printTabs();
        
        std::cout << "}" << std::endl;
    }
    
    GSVoid GS_PrintVisitor::_printTabs() {
        for (GSInt number = 0; number < _tabsCol; ++number) {
            std::cout << "\t";
        }
    }

    GSVoid GS_PrintVisitor::_incrTab() {
        ++_tabsCol;
    }

    GSVoid GS_PrintVisitor::_decrTab() {
        --_tabsCol;
    }
    
}
