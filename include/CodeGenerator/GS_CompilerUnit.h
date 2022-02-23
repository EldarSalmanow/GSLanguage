#ifndef GSLANGUAGE_GS_COMPILERUNIT_H
#define GSLANGUAGE_GS_COMPILERUNIT_H

#include <GSCrossPlatform/GS_CrossPlatform.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     *
     */
    class GS_CompilerUnit {
    public:

        /**
         *
         */
        virtual ~GS_CompilerUnit() = default;

    public:

        /**
         *
         * @param name
         * @return
         */
        virtual Bool write(UString name) = 0;
    };

    /**
     *
     */
    using GSCompilerUnitPtr = SharedPtr<GS_CompilerUnit>;

}

#endif //GSLANGUAGE_GS_COMPILERUNIT_H
