#ifndef GSLANGUAGE_GS_CGBACKEND_H
#define GSLANGUAGE_GS_CGBACKEND_H

#include <Driver/GS_Session.h>

#include <AST/Declarations/GS_TranslationUnitDeclaration.h>

namespace GSLanguageCompiler::CodeGenerator {

    enum class CGBackendType {
        LLVM
    };

    class GS_CodeHolder {
    public:

        virtual CGBackendType GetBackendType() const = 0;
    };

    using GSCodeHolderPtr = std::shared_ptr<GS_CodeHolder>;

    class GS_CGBackend {
    public:

        virtual GSCodeHolderPtr Generate(LRef<Driver::GS_Session> session,
                                         AST::GSTranslationUnitDeclarationPtr unit) = 0;

        virtual Void Write(LRef<Driver::GS_Session> session,
                           UString fileName,
                           GSCodeHolderPtr codeHolder) = 0;

    public:

        virtual CGBackendType GetBackendType() const = 0;
    };

    using GSCGBackendPtr = std::shared_ptr<GS_CGBackend>;

}

#endif //GSLANGUAGE_GS_CGBACKEND_H
