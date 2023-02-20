#ifndef GSLANGUAGE_GS_DECLARATION_H
#define GSLANGUAGE_GS_DECLARATION_H

#include <AST/GS_Node.h>

namespace GSLanguageCompiler::AST {

    /**
     * Declaration type
     */
    enum class DeclarationType {
        TranslationUnitDeclaration,
        FunctionDeclaration
    };

    /**
     * Class for all language grammar declarations
     */
    class GS_Declaration : public GS_Node {
    public:

        /*
         *
         * GS_Declaration PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for declaration
         */
        GS_Declaration();

    public:

        /*
         *
         * GS_Declaration PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Is declaration
         * @return Is declaration
         */
        Bool IsDeclaration() const override;

    public:

        /*
         *
         * GS_Declaration PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Getter for declaration type
         * @return Declaration type
         */
        virtual DeclarationType GetDeclarationType() const = 0;
    };

    /**
     * Declaration ptr type
     */
    using GSDeclarationPtr = std::shared_ptr<GS_Declaration>;

    /**
     * Declaration ptr array type
     */
    using GSDeclarationPtrArray = std::vector<GSDeclarationPtr>;

    /**
     * Casting node to declaration if node is declaration
     * @param node Node
     * @return Declaration or null
     */
    GSDeclarationPtr ToDeclaration(ConstLRef<GSNodePtr> node);

    /**
     * Declaring declarations for cast function
     */
    class GS_TranslationUnitDeclaration;
    class GS_FunctionDeclaration;

    /**
     * Casting node to DeclarationT if node is declaration
     * @tparam DeclarationT Type of declaration
     * @param node Node
     * @return Declaration or null
     */
    template<typename DeclarationT>
    inline NodePtr<DeclarationT> ToDeclaration(ConstLRef<GSNodePtr> node) {
        static_assert(std::is_base_of_v<GS_Declaration, DeclarationT>,
                      "Type for casting must be inherited from GS_Declaration!");

        auto declaration = ToDeclaration(node);

        if (!declaration) {
            return nullptr;
        }

        switch (declaration->GetDeclarationType()) {
            case DeclarationType::TranslationUnitDeclaration:
                if constexpr (!std::is_same_v<GS_TranslationUnitDeclaration, DeclarationT>) {
                    return nullptr;
                }

                break;
            case DeclarationType::FunctionDeclaration:
                if constexpr (!std::is_same_v<GS_FunctionDeclaration, DeclarationT>) {
                    return nullptr;
                }

                break;
        }

        return std::reinterpret_pointer_cast<DeclarationT>(declaration);
    }

}

#endif //GSLANGUAGE_GS_DECLARATION_H
