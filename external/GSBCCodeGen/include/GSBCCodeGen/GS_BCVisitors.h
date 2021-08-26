#ifndef GSBCCODEGEN_GS_BCVISITORS_H
#define GSBCCODEGEN_GS_BCVISITORS_H

#include <iostream>
#include <map>

#include "GS_PlatformTypes.h"

namespace GSBCCodeGen {

    class GS_BCRootNode;
    class GS_BCBlockNode;
    class GS_BCValueNode;
    class GS_BCInstructionNode;
    class GS_BCInstructionWithOperandNode;
    class GS_BCInstructionWithTwoOperandsNode;
    class GS_BCLabelNode;
    class GS_BCCFInstructionNode;

    class GS_BCVisitor {
    public:

        virtual ~GS_BCVisitor();

    public:

        virtual GSVoid visit(GS_BCRootNode *rootNode) = 0;

        virtual GSVoid visit(GS_BCBlockNode *blockNode) = 0;

        virtual GSVoid visit(GS_BCValueNode *valueNode) = 0;

        virtual GSVoid visit(GS_BCInstructionNode *instructionNode) = 0;

        virtual GSVoid visit(GS_BCInstructionWithOperandNode *instructionWithOperandNode) = 0;

        virtual GSVoid visit(GS_BCInstructionWithTwoOperandsNode *instructionWithTwoOperandsNode) = 0;

        virtual GSVoid visit(GS_BCLabelNode *labelNode) = 0;

        virtual GSVoid visit(GS_BCCFInstructionNode *cfInstructionNode) = 0;
    };

    class GS_BCLabelsTable {
    public:

        GS_BCLabelsTable();

    public:

        GSVoid addLabel(GSString name, GSInt offset);

        GSInt findLabelOffsetByName(GSString name);

    private:

        std::map<GSString, GSInt> _labelNameToOffset;
    };

    class GS_BCLabelVisitor : public GS_BCVisitor {
    public:

        GS_BCLabelVisitor();

    public:

        GS_BCLabelsTable getLabelsTable();

    public:

        GSVoid visit(GS_BCRootNode *rootNode) override;

        GSVoid visit(GS_BCBlockNode *blockNode) override;

        GSVoid visit(GS_BCValueNode *valueNode) override;

        GSVoid visit(GS_BCInstructionNode *instructionNode) override;

        GSVoid visit(GS_BCInstructionWithOperandNode *instructionWithOperandNode) override;

        GSVoid visit(GS_BCInstructionWithTwoOperandsNode *instructionWithTwoOperandsNode) override;

        GSVoid visit(GS_BCLabelNode *labelNode) override;

        GSVoid visit(GS_BCCFInstructionNode *cfInstructionNode) override;

    private:

        GSInt _offsetFromStart;

        GS_BCLabelsTable _labelsTable;
    };

    class GS_BCCodeGenVisitor : public GS_BCVisitor {
    public:

        explicit GS_BCCodeGenVisitor(GS_BCLabelsTable labelsTable);

    public:

        GSByteCode getBytecode();

    public:

        GSVoid visit(GS_BCRootNode *rootNode) override;

        GSVoid visit(GS_BCBlockNode *blockNode) override;

        GSVoid visit(GS_BCValueNode *valueNode) override;

        GSVoid visit(GS_BCInstructionNode *instructionNode) override;

        GSVoid visit(GS_BCInstructionWithOperandNode *instructionWithOperandNode) override;

        GSVoid visit(GS_BCInstructionWithTwoOperandsNode *instructionWithTwoOperandsNode) override;

        GSVoid visit(GS_BCLabelNode *labelNode) override;

        GSVoid visit(GS_BCCFInstructionNode *cfInstructionNode) override;

    private:

        GS_BCLabelsTable _labelsTable;

        GSByteCode _bytecode;
    };

    class GS_BCPrintVisitor : public GS_BCVisitor {
    public:

        explicit GS_BCPrintVisitor(GS_BCLabelsTable labelsTable);

    public:

        GSVoid visit(GS_BCRootNode *rootNode) override;

        GSVoid visit(GS_BCBlockNode *blockNode) override;

        GSVoid visit(GS_BCValueNode *valueNode) override;

        GSVoid visit(GS_BCInstructionNode *instructionNode) override;

        GSVoid visit(GS_BCInstructionWithOperandNode *instructionWithOperandNode) override;

        GSVoid visit(GS_BCInstructionWithTwoOperandsNode *instructionWithTwoOperandsNode) override;

        GSVoid visit(GS_BCLabelNode *labelNode) override;

        GSVoid visit(GS_BCCFInstructionNode *cfInstructionNode) override;

    private:

        GSVoid _incrTab();

        GSVoid _decrTab();

        GSVoid _printTabs();

    private:

        GS_BCLabelsTable _labelsTable;

        GSInt _tabsCol;
    };

}

#endif //GSBCCODEGEN_GS_BCVISITORS_H
