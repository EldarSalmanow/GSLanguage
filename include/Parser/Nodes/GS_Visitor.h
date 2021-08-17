#ifndef GSLANGUAGE_GS_VISITOR_H
#define GSLANGUAGE_GS_VISITOR_H

#include <memory>

#include <CrossPlatform/GS_PlatformTypes.h>

namespace GSLanguageCompiler::Parser {

    class GS_ValueNode;
    class GS_UnaryNode;
    class GS_BinaryNode;
    class GS_VariableNode;
    class GS_PrintNode;

    class GS_Visitor {
    public:

        virtual ~GS_Visitor() = default;

    public:

        virtual GSVoid visit(GS_ValueNode *valueNode) = 0;

        virtual GSVoid visit(GS_UnaryNode *unaryNode) = 0;

        virtual GSVoid visit(GS_BinaryNode *binaryNode) = 0;

        virtual GSVoid visit(GS_VariableNode *variableNode) = 0;

        virtual GSVoid visit(GS_PrintNode *printNode) = 0;
    };

    typedef std::shared_ptr<GS_Visitor> GSVisitorPtr;

}

#endif //GSLANGUAGE_GS_VISITOR_H
