#include <GS_CodeGenerator.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CodeGenerator::GS_CodeGenerator(LRef<Driver::GS_Session> session,
                                       AST::GSTranslationUnitDeclarationPtr unit)
            : _session(session),
              _unit(std::move(unit)) {}

    GS_CodeGenerator GS_CodeGenerator::Create(LRef<Driver::GS_Session> session,
                                              AST::GSTranslationUnitDeclarationPtr unit) {
        return GS_CodeGenerator(session,
                                std::move(unit));
    }

    GSCodeHolderPtr GS_CodeGenerator::Generate(GSCGBackendPtr backend) {
        auto movedBackend = std::move(backend);

        return movedBackend->Generate(_session,
                                      _unit);
    }

    Void GS_Writer::Write(UString fileName,
                          GSCodeHolderPtr codeHolder) {
        _backend->Write(_session,
                        std::move(fileName),
                        std::move(codeHolder));
    }

}
