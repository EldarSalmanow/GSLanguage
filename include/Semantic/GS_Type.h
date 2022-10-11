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
     * Custom type ptr type for any type
     */
    template<typename T>
    using TypePtr = std::shared_ptr<T>;

    /**
     * Custom type ptr left value type for any type
     */
    template<typename T>
    using TypePtrLRef = LRef<TypePtr<T>>;

    /**
     * Custom type ptr left value type for any type
     */
    template<typename T>
    using TypePtrRRef = RRef<TypePtr<T>>;

    /**
     * Custom type ptr array type for any type
     */
    template<typename T>
    using TypePtrArray = std::vector<TypePtr<T>>;

    /**
     * Type ptr type
     */
    using GSTypePtr = TypePtr<GS_Type>;

    /**
     * Type ptr array type
     */
    using GSTypePtrArray = std::vector<GSTypePtr>;

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
        static std::shared_ptr<GS_VoidType> Create();
    };

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
     * Builtin Char type
     */
    class GS_CharType : public GS_LiteralType {
    public:

        /**
         * Constructor for Char type ptr
         */
        GS_CharType();

    public:

        /**
         * Creating Char type ptr
         * @return Char type ptr
         */
        static std::shared_ptr<GS_CharType> Create();
    };

    /**
     * Builtin I* type
     */
//    class GS_IType : public GS_LiteralType {
//    public:
//
//        /**
//         * Constructor for I* type
//         * @param name Type name
//         * @param byteSize Type byte size
//         */
//        GS_IType(UString name, U64 byteSize);
//
//    public:
//
//        /**
//         * Creating I* type ptr
//         * @param name Type name
//         * @param byteSize Type byte size
//         * @return
//         */
//        static std::shared_ptr<GS_IType> Create(UString name, U64 byteSize);
//
//    public:
//
//
//
//    private:
//
//        U64 _byteSize;
//    };

    /**
     * Builtin I8 type
     */
    class GS_I8Type : public GS_LiteralType {
    public:

        /**
         * Constructor for I8 type
         */
        GS_I8Type();

    public:

        /**
         * Creating I8 type ptr
         * @return I8 type ptr
         */
        static std::shared_ptr<GS_I8Type> Create();
    };

    /**
     * Builtin I16 type
     */
    class GS_I16Type : public GS_LiteralType {
    public:

        /**
         * Constructor for I16 type
         */
        GS_I16Type();

    public:

        /**
         * Creating I16 type ptr
         * @return I16 type ptr
         */
        static std::shared_ptr<GS_I16Type> Create();
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
     * Builtin I64 type
     */
    class GS_I64Type : public GS_LiteralType {
    public:

        /**
         * Constructor for I64 type
         */
        GS_I64Type();

    public:

        /**
         * Creating I64 type ptr
         * @return I64 type ptr
         */
        static std::shared_ptr<GS_I64Type> Create();
    };

    /**
     * Builtin U8 type
     */
    class GS_U8Type : public GS_LiteralType {
    public:

        /**
         * Constructor for U8 type
         */
        GS_U8Type();

    public:

        /**
         * Creating U8 type ptr
         * @return U8 type ptr
         */
        static std::shared_ptr<GS_U8Type> Create();
    };

    /**
     * Builtin U16 type
     */
    class GS_U16Type : public GS_LiteralType {
    public:

        /**
         * Constructor for U16 type
         */
        GS_U16Type();

    public:

        /**
         * Creating U16 type ptr
         * @return U16 type ptr
         */
        static std::shared_ptr<GS_U16Type> Create();
    };

    /**
     * Builtin U32 type
     */
    class GS_U32Type : public GS_LiteralType {
    public:

        /**
         * Constructor for U32 type
         */
        GS_U32Type();

    public:

        /**
         * Creating U32 type ptr
         * @return U32 type ptr
         */
        static std::shared_ptr<GS_U32Type> Create();
    };

    /**
     * Builtin U64 type
     */
    class GS_U64Type : public GS_LiteralType {
    public:

        /**
         * Constructor for U64 type
         */
        GS_U64Type();

    public:

        /**
         * Creating U64 type ptr
         * @return U64 type ptr
         */
        static std::shared_ptr<GS_U64Type> Create();
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

    class GS_ArrayType : public GS_Type {
    public:

        GS_ArrayType(GSTypePtr type, U64 size);

    public:

        static std::shared_ptr<GS_ArrayType> Create(GSTypePtr type, U64 size);

    public:

        GSTypePtr GetType() const;

        U64 GetSize() const;

    private:

        GSTypePtr _type;

        U64 _size;
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
        TypePtr<GS_VoidType> GetVoidType() const;

        /**
         * Getter for default Char type
         * @return Char type
         */
        TypePtr<GS_CharType> GetCharType() const;

        /**
         * Getter for default I8 type
         * @return I8 type
         */
        TypePtr<GS_I8Type> GetI8Type() const;

        /**
         * Getter for default I16 type
         * @return I16 type
         */
        TypePtr<GS_I16Type> GetI16Type() const;

        /**
         * Getter for default I32 type
         * @return I32 type
         */
        TypePtr<GS_I32Type> GetI32Type() const;

        /**
         * Getter for default I64 type
         * @return I64 type
         */
        TypePtr<GS_I64Type> GetI64Type() const;

        /**
         * Getter for default U8 type
         * @return U8 type
         */
        TypePtr<GS_U8Type> GetU8Type() const;

        /**
         * Getter for default U16 type
         * @return U16 type
         */
        TypePtr<GS_U16Type> GetU16Type() const;

        /**
         * Getter for default U32 type
         * @return U32 type
         */
        TypePtr<GS_U32Type> GetU32Type() const;

        /**
         * Getter for default U64 type
         * @return U64 type
         */
        TypePtr<GS_U64Type> GetU64Type() const;

        /**
         * Getter for default String type
         * @return String type
         */
        TypePtr<GS_StringType> GetStringType() const;

    private:

        /**
         * Void type
         */
        TypePtr<GS_VoidType> _voidType;

        /**
         * Char type
         */
        TypePtr<GS_CharType> _charType;

        /**
         * I8 type
         */
        TypePtr<GS_I8Type> _i8Type;

        /**
         * I16 type
         */
        TypePtr<GS_I16Type> _i16Type;

        /**
         * I32 type
         */
        TypePtr<GS_I32Type> _i32Type;

        /**
         * I64 type
         */
        TypePtr<GS_I64Type> _i64Type;

        /**
         * U8 type
         */
        TypePtr<GS_U8Type> _u8Type;

        /**
         * U16 type
         */
        TypePtr<GS_U16Type> _u16Type;

        /**
         * U32 type
         */
        TypePtr<GS_U32Type> _u32Type;

        /**
         * U64 type
         */
        TypePtr<GS_U64Type> _u64Type;

        /**
         * String type
         */
        TypePtr<GS_StringType> _stringType;
    };

    /**
     * Type context ptr type
     */
    using GSTypeContextPtr = std::shared_ptr<GS_TypeContext>;

}

#endif //GSLANGUAGE_GS_TYPE_H
