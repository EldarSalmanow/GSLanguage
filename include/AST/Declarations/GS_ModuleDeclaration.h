#ifndef GSLANGUAGE_GS_MODULEDECLARATION_H
#define GSLANGUAGE_GS_MODULEDECLARATION_H

#include <AST/GS_Declaration.h>

namespace GSLanguageCompiler::AST {

    class GS_ModuleDeclaration : public GS_Declaration {
    public:

        GS_ModuleDeclaration(UString name,
                             GSDeclarationPtrArray declarations);

    public:

        static std::shared_ptr<GS_ModuleDeclaration> Create(UString name,
                                                            GSDeclarationPtrArray declarations);

        static std::shared_ptr<GS_ModuleDeclaration> Create(UString name);

    public:

        LRef<UString> GetName();

        LRef<GSDeclarationPtrArray> GetDeclarations();

    public:

        DeclarationType GetDeclarationType() const override;

    private:

        UString _name;

        GSDeclarationPtrArray _declarations;
    };

}

#endif //GSLANGUAGE_GS_MODULEDECLARATION_H
