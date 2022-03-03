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
         * @param scope Declaration scope
         */
        explicit GS_Declaration(GSScopePtr scope);

    public:

        /**
         * Is declaration
         * @return Is declaration
         */
        Bool isDeclaration() const override;

    public:

        /**
         * Getter for declaration type
         * @return Declaration type
         */
        virtual DeclarationType getDeclarationType() const = 0;
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

}

#endif //GSLANGUAGE_GS_DECLARATION_H
