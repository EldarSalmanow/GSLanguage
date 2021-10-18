#ifndef GSLANGUAGE_GS_TYPE_H
#define GSLANGUAGE_GS_TYPE_H

#include <GSCrossPlatform/GS_CrossPlatformTypes.h>

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
        explicit GS_Type(String name);

    public:

        /**
         * Getter for type name
         * @return Type name
         */
        String getName();

    private:

        /**
         * Type name
         */
        String _name;
    };

    class GS_I32Type : public GS_Type {
    public:

        GS_I32Type();
    };

    class GS_StringType : public GS_Type {
    public:

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
    Bool isBaseType(GSTypePtr type);

}

#endif //GSLANGUAGE_GS_TYPE_H
