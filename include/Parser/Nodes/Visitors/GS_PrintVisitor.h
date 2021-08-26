#ifndef GSLANGUAGE_GS_PRINTVISITOR_H
#define GSLANGUAGE_GS_PRINTVISITOR_H

#include <Parser/Nodes/GS_Visitor.h>

namespace GSLanguageCompiler::Parser {

    class GS_PrintVisitor : public GS_Visitor {
    public:

        GS_PrintVisitor();

    public:

        GSVoid visit(GS_RootNode *rootNode) override;

        GSVoid visit(GS_BlockNode *blockNode) override;

        GSVoid visit(GS_ValueNode *valueNode) override;

        GSVoid visit(GS_UnaryNode *unaryNode) override;

        GSVoid visit(GS_BinaryNode *binaryNode) override;

        GSVoid visit(GS_VariableNode *variableNode) override;

        GSVoid visit(GS_PrintNode *printNode) override;

    private:

        GSVoid _printTabs();

        inline GSVoid _incrTab();

        inline GSVoid _decrTab();

    private:

        GSInt _tabsCol;
    };

}

#endif //GSLANGUAGE_GS_PRINTVISITOR_H
