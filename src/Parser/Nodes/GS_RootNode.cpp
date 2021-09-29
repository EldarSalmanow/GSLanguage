#include <Nodes/GS_RootNode.h>

namespace GSLanguageCompiler::Parser {

    GS_RootNode::GS_RootNode(GSNodePtr node)
            : _node(std::move(node)) {}

    GSNodePtr GS_RootNode::getNode() {
        return _node;
    }

    NodeType GS_RootNode::getNodeType() {
        return NodeType::ROOT_NODE;
    }

    llvm::Value *GS_RootNode::accept(GS_Visitor<llvm::Value*> *visitor) {
        return visitor->visit(this);
    }

    GSVoid GS_RootNode::accept(GS_Visitor<GSVoid> *visitor) {
        return visitor->visit(this);
    }

    GSNodePtr GS_RootNode::accept(GS_Visitor<GSNodePtr> *visitor) {
        return visitor->visit(this);
    }

}
