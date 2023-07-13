#ifndef GSLANGUAGE_GS_IMPORTDECLARATION_H
#define GSLANGUAGE_GS_IMPORTDECLARATION_H

#include <AST/GS_Declaration.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for import declaration in language grammar
     */
    class GS_ImportDeclaration : public GS_Declaration {
    public:

        /*
         *
         * GS_ImportDeclaration PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for import declaration
         * @param path Path
         */
        explicit GS_ImportDeclaration(UString path);

    public:

        /*
         *
         * GS_ImportDeclaration PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating import declaration
         * @param path Path
         * @return Import declaration ptr
         */
        static std::shared_ptr<GS_ImportDeclaration> Create(UString path);

    public:

        /*
         *
         * GS_ImportDeclaration PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for path
         * @return Path
         */
        LRef<UString> GetPath();

    public:

        /*
         *
         * GS_ImportDeclaration PUBLIC OVERRIDE METHODS
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
         * GS_ImportDeclaration PRIVATE FIELDS
         *
         */

        /**
         * Path
         */
        UString _path;
    };

}

#endif //GSLANGUAGE_GS_IMPORTDECLARATION_H
