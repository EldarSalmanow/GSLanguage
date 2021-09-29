#include <Nodes/GS_VariableUsingNode.h>

namespace GSLanguageCompiler::Parser {

    GS_VariableUsingNode::GS_VariableUsingNode(GSString name)
            : _name(std::move(name)) {}

    GSString GS_VariableUsingNode::getName() {
        return _name;
    }

    NodeType GS_VariableUsingNode::getNodeType() {
        return NodeType::VARIABLE_USING_NODE;
    }

    llvm::Value *GS_VariableUsingNode::accept(GS_Visitor<llvm::Value*> *visitor) {
        return visitor->visit(this);
    }

    GSVoid GS_VariableUsingNode::accept(GS_Visitor<GSVoid> *visitor) {
        return visitor->visit(this);
    }

    GSNodePtr GS_VariableUsingNode::accept(GS_Visitor<GSNodePtr> *visitor) {
        return visitor->visit(this);
    }

}
