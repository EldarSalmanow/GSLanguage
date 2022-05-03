#ifndef GSLANGUAGE_GS_TRANSLATIONUNITDECLARATION_H
#define GSLANGUAGE_GS_TRANSLATIONUNITDECLARATION_H

#include <AST/GS_Declaration.h>

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
         */
        GS_TranslationUnitDeclaration(UString name, GSNodePtrArray nodes);

    public:

        /**
         * Creating translation unit declaration ptr
         * @param name Name
         * @param nodes Nodes
         * @return Translation unit declaration ptr
         */
        static SharedPtr<GS_TranslationUnitDeclaration> Create(UString name, GSNodePtrArray nodes);

        /**
         * Creating translation unit declaration ptr
         * @param name Name
         * @return Translation unit declaration ptr
         */
        static SharedPtr<GS_TranslationUnitDeclaration> Create(UString name);

    public:

        /**
         * Adding node to translation unit
         * @param node Node
         * @return
         */
        Void AddNode(GSNodePtr node);

        /**
         * Creating and adding new node to nodes and return it
         * @tparam T Type of node for creating
         * @tparam Args Argument types for creating node
         * @param args Arguments for creating node
         * @return Created node
         */
        template<typename T, typename... Args>
        inline auto AddNode(Args... args) {
            static_assert(std::is_base_of_v<GS_Node, T>, "Type for creating must be inherited from GS_Node!");

            auto node = T::Create(args...);

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
