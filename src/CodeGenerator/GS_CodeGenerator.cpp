#include <GS_CodeGenerator.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CodeGenerator::GS_CodeGenerator(LRef<Driver::GS_Session> session,
                                       GSBackendPtr backend)
            : _session(session),
              _backend(std::move(backend)) {}

    GS_CodeGenerator GS_CodeGenerator::Create(LRef<Driver::GS_Session> session,
                                              GSBackendPtr backend) {
        return GS_CodeGenerator(session,
                                std::move(backend));
    }

    GSCodeHolderPtr GS_CodeGenerator::Generate(AST::GSNodePtr node) {
        auto codeHolder = _backend->Generate(_session,
                                             std::move(node));

        return codeHolder;
    }

}
