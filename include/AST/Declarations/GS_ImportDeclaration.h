#ifndef GSLANGUAGE_GS_IMPORTDECLARATION_H
#define GSLANGUAGE_GS_IMPORTDECLARATION_H

#include <AST/GS_Declaration.h>

namespace GSLanguageCompiler::AST {

    class GS_ImportDeclaration : public GS_Declaration {
    public:

        explicit GS_ImportDeclaration(UString path);

    public:

        static std::shared_ptr<GS_ImportDeclaration> Create(UString path);

    public:

        LRef<UString> GetPath();

    public:

        DeclarationType GetDeclarationType() const override;

    private:

        UString _path;
    };

}

#endif //GSLANGUAGE_GS_IMPORTDECLARATION_H
