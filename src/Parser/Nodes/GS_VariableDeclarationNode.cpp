#include <Nodes/GS_VariableDeclarationNode.h>

namespace GSLanguageCompiler::Parser {

    GS_VariableDeclarationNode::GS_VariableDeclarationNode(GSString name)
            : _name(std::move(name)), _type(ValueType::VOID) {}

    GS_VariableDeclarationNode::GS_VariableDeclarationNode(GSString name, ValueType type)
            : _name(std::move(name)), _type(type) {}

    NodeType GS_VariableDeclarationNode::getNodeType() {
        return NodeType::VARIABLE_DECLARATION_NODE;
    }

    GSString GS_VariableDeclarationNode::getName() {
        return _name;
    }

    ValueType GS_VariableDeclarationNode::getType() {
        return _type;
    }

    GSVoid GS_VariableDeclarationNode::setType(ValueType type) {
        _type = type;
    }

    llvm::Value *GS_VariableDeclarationNode::accept(GS_Visitor<llvm::Value*> *visitor) {
        return visitor->visit(this);
    }

    GSVoid GS_VariableDeclarationNode::accept(GS_Visitor<GSVoid> *visitor) {
        return visitor->visit(this);
    }

    GSNodePtr GS_VariableDeclarationNode::accept(GS_Visitor<GSNodePtr> *visitor) {
        return visitor->visit(this);
    }

}
