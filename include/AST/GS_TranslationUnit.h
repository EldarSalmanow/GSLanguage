#ifndef GSLANGUAGE_GS_TRANSLATIONUNIT_H
#define GSLANGUAGE_GS_TRANSLATIONUNIT_H

#include <AST/GS_Scope.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for translation units
     */
    class GS_TranslationUnit {
    public:

        /**
         * Constructor for translation unit
         * @param nodes Nodes
         * @param scope Global scope
         */
        GS_TranslationUnit(GSNodePtrArray nodes, GSScopePtr scope);

    public:

        /**
         * Getter for nodes
         * @return Nodes
         */
        GSNodePtrArray getNodes() const;

        /**
         * Getter for global scope
         * @return Global scope
         */
        GSScopePtr getScope() const;

    private:

        /**
         * Nodes
         */
        GSNodePtrArray _nodes;

        /**
         * Translation unit global scope
         */
        GSScopePtr _globalScope;
    };

    /**
     * Translation unit ptr type
     */
    using GSTranslationUnitPtr = SharedPtr<GS_TranslationUnit>;

    /**
     * Translation unit ptr array type
     */
    using GSTranslationUnitPtrArray = Vector<GSTranslationUnitPtr>;

}

#endif //GSLANGUAGE_GS_TRANSLATIONUNIT_H
