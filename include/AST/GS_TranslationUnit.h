#ifndef GSLANGUAGE_GS_TRANSLATIONUNIT_H
#define GSLANGUAGE_GS_TRANSLATIONUNIT_H

#include <AST/GS_Scope.h>

namespace GSLanguageCompiler::AST {

    /**
     *
     */
    class GS_TranslationUnit {
    public:

        /**
         *
         * @param nodes
         * @param scope
         */
        GS_TranslationUnit(GSNodePtrArray nodes, GSScopePtr scope);

    public:

        /**
         *
         * @return
         */
        GSNodePtrArray getNodes() const;

        /**
         *
         * @return
         */
        GSScopePtr getScope() const;

    private:

        /**
         *
         */
        GSNodePtrArray _nodes;

        /**
         *
         */
        GSScopePtr _globalScope;
    };

    /**
     *
     */
    using GSTranslationUnitPtr = SharedPtr<GS_TranslationUnit>;

    /**
     *
     */
    using GSTranslationUnitPtrArray = Vector<GSTranslationUnitPtr>;

}

#endif //GSLANGUAGE_GS_TRANSLATIONUNIT_H
