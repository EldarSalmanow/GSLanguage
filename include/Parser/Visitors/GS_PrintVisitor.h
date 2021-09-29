#ifndef GSLANGUAGE_GS_PRINTVISITOR_H
#define GSLANGUAGE_GS_PRINTVISITOR_H

#include <iostream>

#include <Parser/Visitors/GS_Visitor.h>

#include <Exceptions/GS_ErrorHandler.h>

namespace GSLanguageCompiler::Parser {

    class GS_PrintVisitor : public GS_Visitor<GSVoid> {
    public:

        GS_PrintVisitor();

    public:

        GSVoid setup(Starter::GSContextPtr &context) override;

        GSVoid visit(GS_RootNode *rootNode) override;

        GSVoid visit(GS_BlockNode *blockNode) override;

        GSVoid visit(GS_ValueNode *valueNode) override;

        GSVoid visit(GS_UnaryNode *unaryNode) override;

        GSVoid visit(GS_BinaryNode *binaryNode) override;

        GSVoid visit(GS_AssignmentNode *assignmentNode) override;

        GSVoid visit(GS_VariableDeclarationNode *variableDeclarationNode) override;

        GSVoid visit(GS_VariableUsingNode *variableUsingNode) override;

    private:

        GSVoid _printTabs();

        inline GSVoid _incrTab();

        inline GSVoid _decrTab();

    private:

        GSInt _tabsCol;
    };

}

#endif //GSLANGUAGE_GS_PRINTVISITOR_H
