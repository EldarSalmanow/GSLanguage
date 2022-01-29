#ifndef GSLANGUAGE_GS_TRANSLATIONUNITDECLARATION_H
#define GSLANGUAGE_GS_TRANSLATIONUNIT_H

#include <GSCrossPlatform/GS_CrossPlatform.h>

namespace GSLanguageCompiler::Driver {

    class GS_TranslationUnitDeclaration {
    public:

        explicit GS_TranslationUnitDeclaration(UString name);

    public:

        I32 compile();

    public:

        UString getName() const;

    private:

        UString _name;
    };

}

#endif //GSLANGUAGE_GS_TRANSLATIONUNITDECLARATION_H
