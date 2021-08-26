#ifndef GSLANGUAGE_GS_INTERPRETERVISITOR_H
#define GSLANGUAGE_GS_INTERPRETERVISITOR_H

#include <Parser/Nodes/GS_Visitor.h>

namespace GSLanguageCompiler::Interpreter {

    class GS_InterpreterVisitor : public Parser::GS_Visitor {
    public:

        GS_InterpreterVisitor();

    public:

        GSVoid visit(Parser::GS_ValueNode *valueNode) override;

        GSVoid visit(Parser::GS_UnaryNode *unaryNode) override;

        GSVoid visit(Parser::GS_BinaryNode *binaryNode) override;

        GSVoid visit(Parser::GS_VariableNode *variableNode) override;

        GSVoid visit(Parser::GS_PrintNode *printNode) override;
    };

}

#endif //GSLANGUAGE_GS_INTERPRETERVISITOR_H
