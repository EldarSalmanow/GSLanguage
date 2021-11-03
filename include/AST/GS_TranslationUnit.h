#ifndef GSLANGUAGE_GS_TRANSLATIONUNIT_H
#define GSLANGUAGE_GS_TRANSLATIONUNIT_H

#include <AST/GS_Scope.h>

namespace GSLanguageCompiler::AST {

    class GS_TranslationUnit {
    public:

        GS_TranslationUnit(GSNodePtrArray nodes, GSScopePtr scope);

    public:

        GSNodePtrArray getNodes();

        GSScopePtr getScope();

    private:

        GSNodePtrArray _nodes;

        GSScopePtr _globalScope;
    };

}

#endif //GSLANGUAGE_GS_TRANSLATIONUNIT_H
