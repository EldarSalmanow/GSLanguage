#ifndef GSLANGUAGE_GS_TRANSLATIONUNIT_H
#define GSLANGUAGE_GS_TRANSLATIONUNIT_H

#include <GSCrossPlatform/GS_CrossPlatformTypes.h>

namespace GSLanguageCompiler::Driver {

    class GS_TranslationUnit {
    public:

        explicit GS_TranslationUnit(String name);

    public:

        I32 compile();

    public:

        String getName();

    private:

        String _name;
    };

}

#endif //GSLANGUAGE_GS_TRANSLATIONUNIT_H
