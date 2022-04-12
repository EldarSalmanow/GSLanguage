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

        /**
         * Constructor for declaration
         * @param scope Scope
         */
        explicit GS_Declaration(GSScopePtr scope);

    public:

        /**
         * Is declaration
         * @return Is declaration
         */
        Bool IsDeclaration() const override;

    public:

        /**
         * Getter for declaration type
         * @return Declaration type
         */
        virtual DeclarationType GetDeclarationType() const = 0;
    };

    /**
     * Declaration ptr type
     */
    using GSDeclarationPtr = SharedPtr<GS_Declaration>;

    /**
     * Declaration ptr array type
     */
    using GSDeclarationPtrArray = Vector<GSDeclarationPtr>;

    /**
     * Casting node to declaration if node is declaration
     * @param node Node
     * @return Declaration or nullptr
     */
    GSDeclarationPtr ToDeclaration(GSNodePtr node);

    /**
     * Casting node to any type of declaration if node is declaration
     * @tparam T Type of declaration
     * @param node Node
     * @return Declaration or nullptr
     */
    template<typename T>
    SharedPtr<T> ToDeclaration(GSNodePtr node) {
        static_assert(std::is_base_of_v<GS_Declaration, T>, "Type for casting must be inherited from GS_Declaration!");

        auto declaration = ToDeclaration(node);

        if (!declaration) {
            return nullptr;
        }

        auto castedDeclaration = std::reinterpret_pointer_cast<T>(declaration);

        return castedDeclaration;
    }

}

#endif //GSLANGUAGE_GS_DECLARATION_H
