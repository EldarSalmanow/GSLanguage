#ifndef GSLANGUAGE_GS_VISITOR_H
#define GSLANGUAGE_GS_VISITOR_H

#include <Starter/GS_Context.h>

namespace GSLanguageCompiler::Parser {

    class GS_RootNode;
    class GS_BlockNode;
    class GS_ValueNode;
    class GS_UnaryNode;
    class GS_BinaryNode;
    class GS_AssignmentNode;
    class GS_VariableDeclarationNode;
    class GS_VariableUsingNode;

    template<typename T>
    class GS_Visitor {
    public:

        virtual ~GS_Visitor() = default;

    public:

        virtual GSVoid setup(Starter::GSContextPtr &context) = 0;

        virtual T visit(GS_RootNode *rootNode) = 0;

        virtual T visit(GS_BlockNode *blockNode) = 0;

        virtual T visit(GS_ValueNode *valueNode) = 0;

        virtual T visit(GS_UnaryNode *unaryNode) = 0;

        virtual T visit(GS_BinaryNode *binaryNode) = 0;

        virtual T visit(GS_AssignmentNode *assignmentNode) = 0;

        virtual T visit(GS_VariableDeclarationNode *variableDeclarationNode) = 0;

        virtual T visit(GS_VariableUsingNode *variableUsingNode) = 0;

    protected:

        Starter::GSContextPtr _context;
    };

}

#endif //GSLANGUAGE_GS_VISITOR_H
