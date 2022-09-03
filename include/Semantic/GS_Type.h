#ifndef GSLANGUAGE_GS_TYPE_H
#define GSLANGUAGE_GS_TYPE_H

#include <vector>

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::Semantic {

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
        static std::shared_ptr<GS_Type> Create(UString name);

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
        virtual Bool IsLiteralType() const;

    private:

        /**
         * Type name
         */
        UString _name;
    };

    /**
     * Type ptr type
     */
    using GSTypePtr = std::shared_ptr<GS_Type>;

    /**
     * Type ptr array type
     */
    using GSTypePtrArray = std::vector<GSTypePtr>;

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
        static std::shared_ptr<GS_LiteralType> Create(UString name);

    public:

        /**
         * Is literal type
         * @return Is literal type
         */
        Bool IsLiteralType() const override;
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
        static std::shared_ptr<GS_VoidType> Create();
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
        static std::shared_ptr<GS_I32Type> Create();
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
        static std::shared_ptr<GS_StringType> Create();
    };

    /**
     * Context for containing information about types
     */
    class GS_TypeContext {
    public:

        /**
         * Constructor for type context
         */
        GS_TypeContext();

    public:

        /**
         * Creating type context
         * @return Type context ptr
         */
        static std::shared_ptr<GS_TypeContext> Create();

    public:

        /**
         * Getter for default Void type
         * @return Void type
         */
        std::shared_ptr<Semantic::GS_VoidType> GetVoidType() const;

        /**
         * Getter for default I32 type
         * @return I32 type
         */
        std::shared_ptr<Semantic::GS_I32Type> GetI32Type() const;

        /**
         * Getter for default String type
         * @return String type
         */
        std::shared_ptr<Semantic::GS_StringType> GetStringType() const;

    private:

        /**
         * Void type
         */
        std::shared_ptr<Semantic::GS_VoidType> _voidType;

        /**
         * I32 type
         */
        std::shared_ptr<Semantic::GS_I32Type> _i32Type;

        /**
         * String type
         */
        std::shared_ptr<Semantic::GS_StringType> _stringType;
    };

    /**
     * Type context ptr type
     */
    using GSTypeContextPtr = std::shared_ptr<GS_TypeContext>;

}

#endif //GSLANGUAGE_GS_TYPE_H
