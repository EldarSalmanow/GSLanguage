#include <Nodes/GS_PrintNode.h>

namespace GSLanguageCompiler::Parser {

    GS_PrintNode::GS_PrintNode(GSValuePtr value)
            : _value(std::move(value)) {}

    NodeType GS_PrintNode::getNodeType() {
        return NodeType::PRINT_NODE;
    }

    GSVoid GS_PrintNode::codegen(CodeGenerator::GS_BCBuilder &builder) {
        builder.createConstant(_value->getData<GSString>(),
                tableOfConstants.getIdByValue(_value->getData<GSString>()));

        builder.createPushConstant(tableOfConstants.getIdByValue(_value->getData<GSString>()));
        builder.createToReg(1);

        builder.createPush(0);
        builder.createToReg(0);
        builder.createCall();
    }

    GSValuePtr GS_PrintNode::interpret() {
        std::cout << _value->getData<GSString>();

        return nullptr;
    }

    GSString GS_PrintNode::toString() {
        return "[ "
               + GSString("print")
               + " ("
               + " \""
               + _value->getData<GSString>()
               + "\""
               + " )"
               + " ]";
    }

}
