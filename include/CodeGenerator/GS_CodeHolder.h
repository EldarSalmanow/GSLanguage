#ifndef GSLANGUAGE_GS_CODEHOLDER_H
#define GSLANGUAGE_GS_CODEHOLDER_H

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::CodeGenerator {

    class GS_CodeHolder {
    public:

        virtual ~GS_CodeHolder();
    };

    using GSCodeHolderPtr = SharedPtr<GS_CodeHolder>;

}

#endif //GSLANGUAGE_GS_CODEHOLDER_H
