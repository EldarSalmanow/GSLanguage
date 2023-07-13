#ifndef GSLANGUAGE_GS_MODULEDECLARATION_H
#define GSLANGUAGE_GS_MODULEDECLARATION_H

#include <AST/GS_Declaration.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for module declaration in language grammar
     */
    class GS_ModuleDeclaration : public GS_Declaration {
    public:

        /*
         *
         * GS_ModuleDeclaration PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for module declaration
         * @param name Name
         * @param body Body
         */
        GS_ModuleDeclaration(UString name,
                             GSDeclarationPtrArray body);

    public:

        /*
         *
         * GS_ModuleDeclaration PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating module declaration
         * @param name Name
         * @param body Body
         * @return Module declaration ptr
         */
        static std::shared_ptr<GS_ModuleDeclaration> Create(UString name,
                                                            GSDeclarationPtrArray body);

        /**
         * Creating module declaration
         * @param name Name
         * @return Module declaration ptr
         */
        static std::shared_ptr<GS_ModuleDeclaration> Create(UString name);

    public:

        /*
         *
         * GS_ModuleDeclaration PUBLIC METHODS
         *
         */

        /**
         * Adding declaration to module body
         * @param declaration Declaration
         * @return Declaration
         */
        LRef<GSDeclarationPtr> AddDeclaration(GSDeclarationPtr declaration);

        /**
         * Creating and adding new declaration to module body and return it
         * @tparam DeclarationT Type of declaration for creating
         * @tparam DeclarationArgs Argument types for creating declaration
         * @param args Arguments for creating declaration
         * @return Created declaration
         */
        template<typename DeclarationT,
                 typename... DeclarationArgs>
        inline auto AddDeclaration(DeclarationArgs... args) {
            static_assert(std::is_base_of_v<GS_Declaration, DeclarationT>,
                          "Type for creating must be inherited from GS_Declaration!");

            auto declaration = DeclarationT::Create(args...);

            auto declarationRef = AddDeclaration(declaration);

            return declarationRef;
        }

    public:

        /*
         *
         * GS_ModuleDeclaration PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for name
         * @return Name
         */
        LRef<UString> GetName();

        /**
         * Getter for body
         * @return Body
         */
        LRef<GSDeclarationPtrArray> GetBody();

    public:

        /*
         *
         * GS_ModuleDeclaration PUBLIC OVERRIDE METHODS
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
         * GS_ModuleDeclaration PRIVATE FIELDS
         *
         */

        /**
         * Name
         */
        UString _name;

        /**
         * Body
         */
        GSDeclarationPtrArray _body;
    };

}

#endif //GSLANGUAGE_GS_MODULEDECLARATION_H
