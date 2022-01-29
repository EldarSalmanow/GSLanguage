#ifndef GSLANGUAGE_GS_TRANSLATIONUNITDECLARATION_H
#define GSLANGUAGE_GS_TRANSLATIONUNITDECLARATION_H

#include <AST/GS_Declaration.h>

#include <AST/GS_Scope.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for translation units
     */
    class GS_TranslationUnitDeclaration : public GS_Declaration {
    public:

        /**
         * Constructor for translation unit
         * @param nodes Nodes
         * @param scope Global scope
         */
        GS_TranslationUnitDeclaration(GSNodePtrArray nodes, GSScopePtr scope);

    public:

        /**
         * Getter for nodes
         * @return Nodes
         */
        LRef<GSNodePtrArray> getNodes();

        /**
         * Getter for global scope
         * @return Global scope
         */
        LRef<GSScopePtr> getGlobalScope();

    public:

        /**
         * Getter for declaration type
         * @return Declaration type
         */
        DeclarationType getDeclarationType() const override;

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
    using GSTranslationUnitPtr = SharedPtr<GS_TranslationUnitDeclaration>;

    /**
     * Translation unit ptr array type
     */
    using GSTranslationUnitPtrArray = Vector<GSTranslationUnitPtr>;

}

#endif //GSLANGUAGE_GS_TRANSLATIONUNITDECLARATION_H
