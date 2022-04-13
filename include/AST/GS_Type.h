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
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Type();

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
        UString GetName() const;

    public:

        /**
         * Is literal type
         * @return Is literal type
         */
        virtual Bool IsLiteralType();

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
     * Class for literal types
     */
    class GS_LiteralType : public GS_Type {
    public:

        /**
         * Constructor for literal type
         * @param name Type name
         */
        explicit GS_LiteralType(UString name);

    public:

        /**
         * Creating literal type ptr
         * @param name Name
         * @return Literal type ptr
         */
        static SharedPtr<GS_LiteralType> Create(UString name);

    public:

        /**
         * Is literal type
         * @return Is literal type
         */
        Bool IsLiteralType() override;
    };

    /**
     * Builtin void type
     */
    class GS_VoidType : public GS_LiteralType {
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
    class GS_I32Type : public GS_LiteralType {
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
    class GS_StringType : public GS_LiteralType {
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

}

#endif //GSLANGUAGE_GS_TYPE_H
