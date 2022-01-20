#ifndef GSLANGUAGE_GS_TYPE_H
#define GSLANGUAGE_GS_TYPE_H

#include <GSCrossPlatform/GS_CrossPlatform.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for all types in language
     */
    class GS_Type {
    public:

        /**
         * Constructor for GS_Type
         * @param name Type name
         */
        explicit GS_Type(UString name);

    public:

        /**
         * Getter for type name
         * @return Type name
         */
        UString getName() const;

    private:

        /**
         * Type name
         */
        UString _name;
    };

    /**
     *
     */
    class GS_VoidType : public GS_Type {
    public:

        /**
         *
         */
        GS_VoidType();
    };

    /**
     *
     */
    class GS_I32Type : public GS_Type {
    public:

        /**
         *
         */
        GS_I32Type();
    };

    /**
     *
     */
    class GS_StringType : public GS_Type {
    public:

        /**
         *
         */
        GS_StringType();
    };

    /**
     * Type ptr type
     */
    using GSTypePtr = SharedPtr<GS_Type>;

    /**
     * Function for check is base type
     * @param type Type ptr
     * @return Is base input type
     */
    Bool IsBaseType(GSTypePtr type);

}

#endif //GSLANGUAGE_GS_TYPE_H
