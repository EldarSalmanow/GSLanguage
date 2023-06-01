#include <GS_CodeGenerator.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CodeGenerator::GS_CodeGenerator(LRef<Driver::GS_Session> session,
                                       AST::GSNodePtr node)
            : _session(session),
              _node(std::move(node)) {}

    GS_CodeGenerator GS_CodeGenerator::Create(LRef<Driver::GS_Session> session,
                                              AST::GSNodePtr node) {
        return GS_CodeGenerator(session,
                                std::move(node));
    }

    GSCodeHolderPtr GS_CodeGenerator::Generate(GSBackendPtr backend) {
        auto movedBackend = std::move(backend);

        return movedBackend->Generate(_session,
                                      _node);
    }

}
