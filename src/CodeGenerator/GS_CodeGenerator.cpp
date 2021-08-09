#include <GS_CodeGenerator.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CodeGenerator::GS_CodeGenerator(Parser::GSNodePtrArray nodes)
            : _nodes(std::move(nodes)) {}

    GSByteCode GS_CodeGenerator::codegen() {
        GSByteCode bytecode;

        for (auto &node : _nodes) {
            for (auto &byte : node->codegen()) {
                bytecode.emplace_back(byte);
            }
        }

        return bytecode;
    }

}