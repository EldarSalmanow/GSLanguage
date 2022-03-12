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
         * Constructor for translation unit declaration
         * @param name Name
         * @param nodes Nodes
         * @param scope Global scope
         */
        GS_TranslationUnitDeclaration(UString name, GSNodePtrArray nodes, GSScopePtr scope);

    public:

        /**
         * Creating translation unit declaration ptr
         * @param name Name
         * @param nodes Nodes
         * @param scope Global scope
         * @return Translation unit declaration ptr
         */
        static SharedPtr<GS_TranslationUnitDeclaration> Create(UString name, GSNodePtrArray nodes, GSScopePtr scope);

        /**
         * Creating translation unit declaration ptr
         * @param name Name
         * @param scope Global scope
         * @return Translation unit declaration ptr
         */
        static SharedPtr<GS_TranslationUnitDeclaration> Create(UString name, GSScopePtr scope);

        /**
         * Creating translation unit ptr
         * @param name Name
         * @return Translation unit declaration ptr
         */
        static SharedPtr<GS_TranslationUnitDeclaration> Create(UString name);

    public:

        /**
         * Creating new node in scope and return it
         * @tparam T Type of node for creating
         * @tparam Args Argument types for creating node
         * @param args Arguments for creating node
         * @return Created node
         */
        template<typename T, typename... Args>
        inline auto createNode(Args... args) {
            static_assert(std::is_base_of_v<GS_Node, T>, "Element for creating must be a node!");

            return T::Create(args..., _globalScope);
        }

        /**
         * Adding node to translation unit
         * @param node Node
         * @return
         */
        Void addNode(GSNodePtr node);

        /**
         * Creating and adding new node to scope and return it
         * @tparam T Type of node for creating
         * @tparam Args Argument types for creating node
         * @param args Arguments for creating node
         * @return Created node
         */
        template<typename T, typename... Args>
        inline auto addNode(Args... args) {
            static_assert(std::is_base_of_v<GS_Node, T>, "Element for creating must be node!");

            auto node = createNode<T>(args...);

            addNode(node);

            return node;
        }

    public:

        /**
         * Getter for name
         * @return Name
         */
        LRef<UString> getName();

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
         * Name
         */
        UString _name;

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
