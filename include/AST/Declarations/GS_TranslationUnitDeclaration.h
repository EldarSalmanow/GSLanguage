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
        inline auto CreateNode(Args... args) {
            static_assert(std::is_base_of_v<GS_Node, T>, "Type for creating must be inherited from GS_Node!");

            return T::Create(args..., _globalScope);
        }

        /**
         * Adding node to translation unit
         * @param node Node
         * @return
         */
        Void AddNode(GSNodePtr node);

        /**
         * Creating and adding new node to scope and return it
         * @tparam T Type of node for creating
         * @tparam Args Argument types for creating node
         * @param args Arguments for creating node
         * @return Created node
         */
        template<typename T, typename... Args>
        inline auto AddNode(Args... args) {
            static_assert(std::is_base_of_v<GS_Node, T>, "Type for creating must be inherited from GS_Node!");

            auto node = CreateNode<T>(args...);

            AddNode(node);

            return node;
        }

    public:

        /**
         * Getter for name
         * @return Name
         */
        LRef<UString> GetName();

        /**
         * Getter for nodes
         * @return Nodes
         */
        LRef<GSNodePtrArray> GetNodes();

        /**
         * Getter for global scope
         * @return Global scope
         */
        LRef<GSScopePtr> GetGlobalScope();

    public:

        /**
         * Getter for declaration type
         * @return Declaration type
         */
        DeclarationType GetDeclarationType() const override;

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
    using GSTranslationUnitDeclarationPtr = SharedPtr<GS_TranslationUnitDeclaration>;

    /**
     * Translation unit ptr array type
     */
    using GSTranslationUnitDeclarationPtrArray = Vector<GSTranslationUnitDeclarationPtr>;

}

#endif //GSLANGUAGE_GS_TRANSLATIONUNITDECLARATION_H
