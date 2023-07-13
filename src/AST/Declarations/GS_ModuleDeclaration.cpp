#include <Declarations/GS_ModuleDeclaration.h>

namespace GSLanguageCompiler::AST {

    GS_ModuleDeclaration::GS_ModuleDeclaration(UString name,
                                               GSDeclarationPtrArray body)
            : _name(std::move(name)),
              _body(std::move(body)) {}

    std::shared_ptr<GS_ModuleDeclaration> GS_ModuleDeclaration::Create(UString name,
                                                                       GSDeclarationPtrArray body) {
        return std::make_shared<GS_ModuleDeclaration>(std::move(name),
                                                      std::move(body));
    }

    std::shared_ptr<GS_ModuleDeclaration> GS_ModuleDeclaration::Create(UString name) {
        return GS_ModuleDeclaration::Create(std::move(name),
                                            GSDeclarationPtrArray());
    }

    LRef<GSDeclarationPtr> GS_ModuleDeclaration::AddDeclaration(GSDeclarationPtr declaration) {
        _body.emplace_back(std::move(declaration));

        return _body[_body.size() - 1];
    }

    LRef<UString> GS_ModuleDeclaration::GetName() {
        return _name;
    }

    LRef<GSDeclarationPtrArray> GS_ModuleDeclaration::GetBody() {
        return _body;
    }

    DeclarationType GS_ModuleDeclaration::GetDeclarationType() const {
        return DeclarationType::ModuleDeclaration;
    }

}
