#include <Nodes/GS_BlockNode.h>

namespace GSLanguageCompiler::Parser {

    GS_BlockNode::GS_BlockNode(GSNodePtrArray nodes)
            : _nodes(std::move(nodes)) {}

    GSNodePtrArray GS_BlockNode::getNodes() {
        return _nodes;
    }

    NodeType GS_BlockNode::getNodeType() {
        return NodeType::BLOCK_NODE;
    }

    llvm::Value *GS_BlockNode::accept(GS_Visitor<llvm::Value*> *visitor) {
        return visitor->visit(this);
    }

    GSVoid GS_BlockNode::accept(GS_Visitor<GSVoid> *visitor) {
        return visitor->visit(this);
    }

    GSNodePtr GS_BlockNode::accept(GS_Visitor<GSNodePtr> *visitor) {
        return visitor->visit(this);
    }

}
