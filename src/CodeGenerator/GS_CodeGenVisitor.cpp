#include <GS_CodeGenVisitor.h>

#include <Parser/GS_IncludeNodes.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CodeGenVisitor::GS_CodeGenVisitor() = default;

    GSVoid GS_CodeGenVisitor::createBytecode() {
        if (!_bytecode.empty()) {
            Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                           "Bytecode is created and not empty!");

            Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                           "Please, use \"getBytecode()\" for get bytecode.");

            Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                           "If you see this error, please report error to GSLanguageCompiler repository.");

            Exceptions::errorHandler.throw_();
        }

        _compiler.createDone();

        _bytecode = _compiler.createBytecode();
    }

    GSByteCode GS_CodeGenVisitor::getBytecode() {
        return _bytecode;
    }

    GSVoid GS_CodeGenVisitor::visit(Parser::GS_RootNode *rootNode) {
        rootNode->getNode()->accept(this);
    }

    GSVoid GS_CodeGenVisitor::visit(Parser::GS_BlockNode *blockNode) {
        for (auto &node : blockNode->getNodes()) {
            node->accept(this);
        }
    }

    GSVoid GS_CodeGenVisitor::visit(Parser::GS_ValueNode *valueNode) {
        auto value = valueNode->getValue();
        
        auto type = value->getType();
        
        if (type == "Int") {
            _compiler.createPush(value->getData<GSInt>());
        } else if (type == "String") {
//            auto string = value->getData<GSString>();
//
//            auto stringId = Parser::tableOfConstants.getIdByValue(string);
//
//            _compiler.createConstant(stringId, string);
//
            _compiler.createPush(value->getData<GSString>());
        } else {
            Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                           "Invalid type for generate code for value!");

            Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                           "Type: \"" + type + "\".");

            Exceptions::errorHandler.throw_();
        }
    }
    
    GSVoid GS_CodeGenVisitor::visit(Parser::GS_UnaryNode *unaryNode) {
        Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                       "Generating code for unary expressions not supported!");

        Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                       "Please, not use unary operations in your code.");

        Exceptions::errorHandler.throw_();
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
            Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                           "Invalid type for print value to console!");

            Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                           "Type: \"" + type + "\".");

            Exceptions::errorHandler.throw_();
        }

//        auto string = printNode->getValue()->getData<GSString>();
//
//        auto stringId = Parser::tableOfConstants.getIdByValue(string);
//
//        _compiler.createConstant(stringId, string);
//
//        _compiler.createPushConstant(stringId);
//        _compiler.createToReg(0);

        _compiler.createPush(printNode->getValue()->getData<GSString>());

        _compiler.createCall(0);
    }

}
