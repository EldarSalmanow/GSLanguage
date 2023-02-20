#ifndef GSLANGUAGE_GS_TRANSLATIONUNITDECLARATION_H
#define GSLANGUAGE_GS_TRANSLATIONUNITDECLARATION_H

#include <AST/GS_Declaration.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for translation units
     */
    class GS_TranslationUnitDeclaration : public GS_Declaration {
    public:

        /*
         *
         * GS_TranslationUnitDeclaration PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for translation unit declaration
         * @param name Name
         * @param nodes Nodes
         */
        GS_TranslationUnitDeclaration(UString name,
                                      GSNodePtrArray nodes);

    public:

        /*
         *
         * GS_TranslationUnitDeclaration PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating translation unit declaration
         * @param name Name
         * @param nodes Nodes
         * @return Translation unit declaration ptr
         */
        static std::shared_ptr<GS_TranslationUnitDeclaration> Create(UString name,
                                                                     GSNodePtrArray nodes);

        /**
         * Creating translation unit declaration
         * @param name Name
         * @return Translation unit declaration ptr
         */
        static std::shared_ptr<GS_TranslationUnitDeclaration> Create(UString name);

    public:

        /*
         *
         * GS_TranslationUnitDeclaration PUBLIC METHODS
         *
         */

        /**
         * Adding node to translation unit
         * @param node Node
         * @return Node
         */
        LRef<GSNodePtr> AddNode(GSNodePtr node);

        /**
         * Creating and adding new node to nodes and return it
         * @tparam NodeT Type of node for creating
         * @tparam NodeArgs Argument types for creating node
         * @param args Arguments for creating node
         * @return Created node
         */
        template<typename NodeT, typename... NodeArgs>
        inline auto AddNode(NodeArgs... args) {
            static_assert(std::is_base_of_v<GS_Node, NodeT>,
                          "Type for creating must be inherited from GS_Node!");

            auto node = NodeT::Create(args...);

            auto nodeRef = AddNode(node);

            return nodeRef;
        }

    public:

        /*
         *
         * GS_TranslationUnitDeclaration PUBLIC GETTER METHODS
         *
         */

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

        /*
         *
         * GS_TranslationUnitDeclaration PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for declaration type
         * @return Declaration type
         */
        DeclarationType GetDeclarationType() const override;

    private:

        /*
         *
         * GS_TranslationUnitDeclaration PRIVATE FIELDS
         *
         */

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
    using GSTranslationUnitDeclarationPtr = std::shared_ptr<GS_TranslationUnitDeclaration>;

    /**
     * Translation unit ptr array type
     */
    using GSTranslationUnitDeclarationPtrArray = std::vector<GSTranslationUnitDeclarationPtr>;

}

#endif //GSLANGUAGE_GS_TRANSLATIONUNITDECLARATION_H
