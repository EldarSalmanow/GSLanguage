#include <GS_CodeGenerator.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CodeGenerator::GS_CodeGenerator(Parser::GSNodePtr nodes)
            : _nodes(std::move(nodes)) {}

    GSByteCode GS_CodeGenerator::codegen() {
        GS_CodeGenVisitor visitor;

        _nodes->accept(&visitor);

        visitor.createBytecode();

        return visitor.getBytecode();
    }

}