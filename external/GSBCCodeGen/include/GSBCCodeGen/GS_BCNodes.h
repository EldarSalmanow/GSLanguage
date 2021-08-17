#ifndef GSBCCODEGEN_GS_BCNODES_H
#define GSBCCODEGEN_GS_BCNODES_H

#include <any>

#include "GS_BCNodeType.h"

#include "GS_BCOpcodeType.h"

namespace GSBCCodeGen {

    class GS_BCVisitor;

    class GS_BCNode {
    public:

        virtual ~GS_BCNode();

    public:

        virtual BCNodeType getNodeType() = 0;

        virtual GSVoid accept(GS_BCVisitor *visitor) = 0;
    };

    typedef GS_BCNode *GSBCNodePtr;

    typedef std::vector<GSBCNodePtr> GSBCNodePtrArray;

    class GS_BCRootNode : public GS_BCNode {
    public:

        GS_BCRootNode();

    public:

        GSBCNodePtr getNode();

        GSVoid setNode(GSBCNodePtr node);

    public:

        BCNodeType getNodeType() override;

        GSVoid accept(GS_BCVisitor *visitor) override;

    private:

        GSBCNodePtr _node;
    };

    class GS_BCBlockNode : public GS_BCNode {
    public:

        GS_BCBlockNode();

        explicit GS_BCBlockNode(GSBCNodePtrArray nodes);

    public:

        GSVoid addNode(GSBCNodePtr node);

    public:

        GSBCNodePtrArray getNodes();

    public:

        BCNodeType getNodeType() override;

        GSVoid accept(GS_BCVisitor *visitor) override;

    private:

        GSBCNodePtrArray _nodes;
    };

    class GS_BCValueNode : public GS_BCNode {
    public:

        explicit GS_BCValueNode(GSInt value);

        explicit GS_BCValueNode(GSString value);

    public:

        template<typename T>
        T getValue() {
            return std::any_cast<T>(_value);
        }

        GSString getType();

    public:

        BCNodeType getNodeType() override;

        GSVoid accept(GS_BCVisitor *visitor) override;

    private:

        std::any _value;

        GSString _type;
    };

    class GS_BCInstructionNode : public GS_BCNode {
    public:

        explicit GS_BCInstructionNode(BCOpcodeType opcode);

    public:

        BCOpcodeType getOpcode();

    public:

        BCNodeType getNodeType() override;

        GSVoid accept(GS_BCVisitor *visitor) override;

    private:

        BCOpcodeType _opcode;
    };

    class GS_BCInstructionWithOperandNode : public GS_BCInstructionNode {
    public:

        GS_BCInstructionWithOperandNode(BCOpcodeType opcode, GS_BCValueNode valueNode);

    public:

        GS_BCValueNode getValueNode();

    public:

        BCNodeType getNodeType() override;

        GSVoid accept(GS_BCVisitor *visitor) override;

    public:

        GS_BCValueNode _valueNode;
    };

    class GS_BCInstructionWithTwoOperandsNode : public GS_BCInstructionNode {
    public:

        GS_BCInstructionWithTwoOperandsNode(BCOpcodeType opcode,
                                            GS_BCValueNode firstValueNode,
                                            GS_BCValueNode secondValueNode);

    public:

        GS_BCValueNode getFirstValueNode();

        GS_BCValueNode getSecondValueNode();

    public:

        BCNodeType getNodeType() override;

        GSVoid accept(GS_BCVisitor *visitor) override;

    private:

        GS_BCValueNode _firstValueNode, _secondValueNode;
    };

}

#endif //GSBCCODEGEN_GS_BCNODES_H
