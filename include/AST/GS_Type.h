#ifndef GSLANGUAGE_GS_TYPE_H
#define GSLANGUAGE_GS_TYPE_H

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for all types in language
     */
    class GS_Type {
    public:

        /**
         * Constructor for type
         * @param name Type name
         */
        explicit GS_Type(UString name);

    public:

        /**
         * Creating type ptr
         * @param name Name
         * @return Type ptr
         */
        static SharedPtr<GS_Type> Create(UString name);

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
     * Type ptr type
     */
    using GSTypePtr = SharedPtr<GS_Type>;

    /**
     * Builtin void type
     */
    class GS_VoidType : public GS_Type {
    public:

        /**
         * Constructor for void type
         */
        GS_VoidType();

    public:

        /**
         * Creating Void type ptr
         * @return Void type ptr
         */
        static SharedPtr<GS_VoidType> Create();
    };

    /**
     * Builtin I32 type
     */
    class GS_I32Type : public GS_Type {
    public:

        /**
         * Constructor for I32 type
         */
        GS_I32Type();

    public:

        /**
         * Creating I32 type ptr
         * @return I32 type ptr
         */
        static SharedPtr<GS_I32Type> Create();
    };

    /**
     * Builtin String type
     */
    class GS_StringType : public GS_Type {
    public:

        /**
         * Constructor for String type
         */
        GS_StringType();

    public:

        /**
         * Creating String type ptr
         * @return String type ptr
         */
        static SharedPtr<GS_StringType> Create();
    };

    /**
     * Function for check is base type
     * @param type Type ptr
     * @return Is base input type
     */
    Bool IsBaseType(GSTypePtr type);

}

#endif //GSLANGUAGE_GS_TYPE_H
