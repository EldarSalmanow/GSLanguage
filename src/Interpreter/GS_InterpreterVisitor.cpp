#include <GS_InterpreterVisitor.h>

#include <Parser/GS_IncludeNodes.h>

namespace GSLanguageCompiler::Interpreter {

    GS_InterpreterVisitor::GS_InterpreterVisitor() = default;

    GSVoid GS_InterpreterVisitor::visit(Parser::GS_ValueNode *valueNode) {

    }

    GSVoid GS_InterpreterVisitor::visit(Parser::GS_UnaryNode *unaryNode) {

    }

    GSVoid GS_InterpreterVisitor::visit(Parser::GS_BinaryNode *binaryNode) {

    }

    GSVoid GS_InterpreterVisitor::visit(Parser::GS_VariableNode *variableNode) {

    }

    GSVoid GS_InterpreterVisitor::visit(Parser::GS_PrintNode *printNode) {

    }

}
