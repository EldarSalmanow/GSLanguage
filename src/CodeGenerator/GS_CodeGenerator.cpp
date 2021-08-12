#include <GS_CodeGenerator.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CodeGenerator::GS_CodeGenerator(Parser::GSNodePtrArray nodes)
            : _nodes(std::move(nodes)) {}

    GSByteCode GS_CodeGenerator::codegen() {
        for (auto &node : _nodes) {
            node->codegen(_builder);
        }

        return _builder.createByteCode();
    }

}