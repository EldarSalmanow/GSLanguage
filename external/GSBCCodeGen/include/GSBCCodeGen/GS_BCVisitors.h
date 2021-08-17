#ifndef GSBCCODEGEN_GS_BCVISITORS_H
#define GSBCCODEGEN_GS_BCVISITORS_H

#include <iostream>

#include "GS_PlatformTypes.h"

namespace GSBCCodeGen {

    class GS_BCRootNode;
    class GS_BCBlockNode;
    class GS_BCValueNode;
    class GS_BCInstructionNode;
    class GS_BCInstructionWithOperandNode;
    class GS_BCInstructionWithTwoOperandsNode;

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
    };

    class GS_BCCodeGenVisitor : public GS_BCVisitor {
    public:

        GS_BCCodeGenVisitor();

    public:

        GSByteCode getBytecode();

    public:

        GSVoid visit(GS_BCRootNode *rootNode) override;

        GSVoid visit(GS_BCBlockNode *blockNode) override;

        GSVoid visit(GS_BCValueNode *valueNode) override;

        GSVoid visit(GS_BCInstructionNode *instructionNode) override;

        GSVoid visit(GS_BCInstructionWithOperandNode *instructionWithOperandNode) override;

        GSVoid visit(GS_BCInstructionWithTwoOperandsNode *instructionWithTwoOperandsNode) override;

    private:

        GSByteCode _bytecode;
    };

    class GS_BCPrintVisitor : public GS_BCVisitor {
    public:

        GS_BCPrintVisitor();

    public:

        GSVoid visit(GS_BCRootNode *rootNode) override;

        GSVoid visit(GS_BCBlockNode *blockNode) override;

        GSVoid visit(GS_BCValueNode *valueNode) override;

        GSVoid visit(GS_BCInstructionNode *instructionNode) override;

        GSVoid visit(GS_BCInstructionWithOperandNode *instructionWithOperandNode) override;

        GSVoid visit(GS_BCInstructionWithTwoOperandsNode *instructionWithTwoOperandsNode) override;

    private:

        GSVoid _incrTab();

        GSVoid _decrTab();

        GSVoid _printTabs();

    private:

        GSInt _tabsCol;
    };

}

#endif //GSBCCODEGEN_GS_BCVISITORS_H
