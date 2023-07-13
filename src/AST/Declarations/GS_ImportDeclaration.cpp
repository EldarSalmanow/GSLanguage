#include <Declarations/GS_ImportDeclaration.h>

namespace GSLanguageCompiler::AST {

    GS_ImportDeclaration::GS_ImportDeclaration(UString path)
            : _path(std::move(path)) {}

    std::shared_ptr<GS_ImportDeclaration> GS_ImportDeclaration::Create(UString path) {
        return std::make_shared<GS_ImportDeclaration>(std::move(path));
    }

    LRef<UString> GS_ImportDeclaration::GetPath() {
        return _path;
    }

    DeclarationType GS_ImportDeclaration::GetDeclarationType() const {
        return DeclarationType::ImportDeclaration;
    }

}
