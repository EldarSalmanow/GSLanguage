#ifndef GSLANGUAGE_GS_CODEGENVISITOR_H
#define GSLANGUAGE_GS_CODEGENVISITOR_H

#include <Parser/Nodes/GS_Visitor.h>

#include <GSBCCodeGen/GS_BCCompiler.h>

#include <Exceptions/GS_ErrorHandler.h>

namespace GSLanguageCompiler::CodeGenerator {

    class GS_CodeGenVisitor : public Parser::GS_Visitor {
    public:

        GS_CodeGenVisitor();

    public:

        GSVoid createBytecode();

    public:

        GSByteCode getBytecode();

    public:

        GSVoid visit(Parser::GS_RootNode *rootNode) override;

        GSVoid visit(Parser::GS_BlockNode *blockNode) override;

        GSVoid visit(Parser::GS_ValueNode *valueNode) override;

        GSVoid visit(Parser::GS_UnaryNode *unaryNode) override;

        GSVoid visit(Parser::GS_BinaryNode *binaryNode) override;

        GSVoid visit(Parser::GS_VariableNode *variableNode) override;

        GSVoid visit(Parser::GS_PrintNode *printNode) override;

    private:

        GSBCCodeGen::GS_BCCompiler _compiler;

        GSByteCode _bytecode;
    };

}

#endif //GSLANGUAGE_GS_CODEGENVISITOR_H
