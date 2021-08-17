#include <GS_CodeGenerator.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CodeGenerator::GS_CodeGenerator(Parser::GSNodePtrArray nodes)
            : _nodes(std::move(nodes)) {}

    GSByteCode GS_CodeGenerator::codegen() {
        GS_CodeGenVisitor visitor;

        for (auto &node : _nodes) {
            node->accept(&visitor);
        }

        visitor.createBytecode();

        return visitor.getBytecode();
    }

}