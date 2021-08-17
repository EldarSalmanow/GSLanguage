#include <GS_CodeGenVisitor.h>

#include <Parser/GS_IncludeNodes.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CodeGenVisitor::GS_CodeGenVisitor() = default;

    GSVoid GS_CodeGenVisitor::createBytecode() {
        if (!_bytecode.empty()) {
            throw Exceptions::GS_Exception("Bytecode is not empty!");
        }

        _compiler.createDone();

        _bytecode = _compiler.createBytecode();
    }

    GSByteCode GS_CodeGenVisitor::getBytecode() {
        return _bytecode;
    }

    GSVoid GS_CodeGenVisitor::visit(Parser::GS_ValueNode *valueNode) {
        auto value = valueNode->getValue();
        
        auto type = value->getType();
        
        if (type == "Int") {
            _compiler.createPush(value->getData<GSInt>());
        } else if (type == "String") {
            auto string = value->getData<GSString>();
            
            auto stringId = Parser::tableOfConstants.getIdByValue(string);
            
            _compiler.createConstant(stringId, string);
            
            _compiler.createPushConstant(stringId);
        } else {
            throw Exceptions::GS_Exception("Invalid type for code generation!");
        }
    }
    
    GSVoid GS_CodeGenVisitor::visit(Parser::GS_UnaryNode *unaryNode) {
        throw Exceptions::GS_Exception("Generating unary nodes for GSVirtualMachine not supported!");
    }
    
    GSVoid GS_CodeGenVisitor::visit(Parser::GS_BinaryNode *binaryNode) {
        binaryNode->getFirstNode()->accept(this);
        
        binaryNode->getSecondNode()->accept(this);

        switch (binaryNode->getBinaryOperation()) {
            case Parser::BinaryOperation::PLUS:
                _compiler.createAdd();
                break;
            case Parser::BinaryOperation::MINUS:
                _compiler.createSub();
                break;
            case Parser::BinaryOperation::STAR:
                _compiler.createMul();
                break;
            case Parser::BinaryOperation::SLASH:
                _compiler.createDiv();
                break;
        }
    }
    
    GSVoid GS_CodeGenVisitor::visit(Parser::GS_VariableNode *variableNode) {
        auto name = variableNode->getName();

        _compiler.createVariable(Parser::tableOfVariables.getIdByName(name), name);
    }
    
    GSVoid GS_CodeGenVisitor::visit(Parser::GS_PrintNode *printNode) {
        auto type = printNode->getValue()->getType();

        if (type != "String") {
            throw Exceptions::GS_Exception("Unknown type for printing!");
        }

        auto string = printNode->getValue()->getData<GSString>();

        auto stringId = Parser::tableOfConstants.getIdByValue(string);

        _compiler.createConstant(stringId, string);

        _compiler.createPushConstant(stringId);
        _compiler.createToReg(0);

        _compiler.createCall(0);
    }

}
