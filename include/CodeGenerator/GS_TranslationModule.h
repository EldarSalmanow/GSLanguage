#ifndef GSLANGUAGE_GS_TRANSLATIONMODULE_H
#define GSLANGUAGE_GS_TRANSLATIONMODULE_H

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     *
     */
    class GS_TranslationModule {
    public:

        /**
         *
         */
        virtual ~GS_TranslationModule();
    };

    /**
     *
     */
    using GSTranlationModulePtr = SharedPtr<GS_TranslationModule>;

}

#endif //GSLANGUAGE_GS_TRANSLATIONMODULE_H
