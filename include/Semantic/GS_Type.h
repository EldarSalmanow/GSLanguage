#ifndef GSLANGUAGE_GS_TYPE_H
#define GSLANGUAGE_GS_TYPE_H

#include <vector>

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::Semantic {

    /**
     * Type of type
     */
    enum class TypeType {
        Void,

        Char,
        Integer,
        UInteger,
        String,

        Array,

        User
    };

    /**
     * Class for all types in language
     */
    class GS_Type {
    public:

        /*
         *
         * GS_Type PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for type
         * @param name Type name
         */
        explicit GS_Type(UString name);

    public:

        /*
         *
         * GS_Type PUBLIC DESTRUCTORS
         *
         */

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Type();

    public:

        /*
         *
         * GS_Type PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating type
         * @param name Name
         * @return Type ptr
         */
        static std::shared_ptr<GS_Type> Create(UString name);

    public:

        /*
         *
         * GS_Type PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for type name
         * @return Type name
         */
        ConstLRef<UString> GetName() const;

    public:

        /*
         *
         * GS_Type PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Getter for type of type
         * @return Type of type
         */
        virtual TypeType GetType() const;

    private:

        /*
         *
         * GS_Type PRIVATE FIELDS
         *
         */

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
     * Builtin Void type
     */
    class GS_VoidType : public GS_Type {
    public:

        /*
         *
         * GS_VoidType PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for Void type
         */
        GS_VoidType();

    public:

        /*
         *
         * GS_VoidType PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating Void type
         * @return Void type ptr
         */
        static std::shared_ptr<GS_VoidType> Create();

    public:

        /*
         *
         * GS_VoidType PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for type of type
         * @return Type of type
         */
        TypeType GetType() const override;
    };

    /**
     * Builtin Char type
     */
    class GS_CharType : public GS_Type {
    public:

        /*
         *
         * GS_CharType PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for Char type
         */
        GS_CharType();

    public:

        /*
         *
         * GS_CharType PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating Char type
         * @return Char type ptr
         */
        static std::shared_ptr<GS_CharType> Create();

    public:

        /*
         *
         * GS_CharType PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for type of type
         * @return Type of type
         */
        TypeType GetType() const override;
    };

    /**
     * Integer type
     */
    enum class IntegerType {
        I8,
        I16,
        I32,
        I64,

        User
    };

    /**
     * Builtin integer type
     */
    class GS_IntegerType : public GS_Type {
    public:

        /*
         *
         * GS_IntegerType PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for integer type
         * @param name Type name
         */
        explicit GS_IntegerType(UString name);

    public:

        /*
         *
         * GS_IntegerType PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating integer type
         * @param name Type name
         * @return Integer type ptr
         */
        static std::shared_ptr<GS_IntegerType> Create(UString name);

    public:

        /*
         *
         * GS_IntegerType PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for type of type
         * @return Type of type
         */
        TypeType GetType() const override;

    public:

        /*
         *
         * GS_IntegerType PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Getter for integer type
         * @return Integer type
         */
        virtual IntegerType GetIntegerType() const;
    };

    // TODO add (U)Integer ptr type

    /**
     * Builtin I8 type
     */
    class GS_I8Type : public GS_IntegerType {
    public:

        /*
         *
         * GS_I8Type PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for I8 type
         */
        GS_I8Type();

    public:

        /*
         *
         * GS_I8Type PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating I8 type
         * @return I8 type ptr
         */
        static std::shared_ptr<GS_I8Type> Create();

    public:

        /*
         *
         * GS_I8Type PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for integer type
         * @return Integer type
         */
        IntegerType GetIntegerType() const override;
    };

    /**
     * Builtin I16 type
     */
    class GS_I16Type : public GS_IntegerType {
    public:

        /*
         *
         * GS_I16Type PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for I16 type
         */
        GS_I16Type();

    public:

        /*
         *
         * GS_I16Type PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating I16 type
         * @return I16 type ptr
         */
        static std::shared_ptr<GS_I16Type> Create();

    public:

        /*
         *
         * GS_I16Type PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for integer type
         * @return Integer type
         */
        IntegerType GetIntegerType() const override;
    };

    /**
     * Builtin I32 type
     */
    class GS_I32Type : public GS_IntegerType {
    public:

        /*
         *
         * GS_I32Type PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for I32 type
         */
        GS_I32Type();

    public:

        /*
         *
         * GS_I32Type PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating I32 type
         * @return I32 type ptr
         */
        static std::shared_ptr<GS_I32Type> Create();

    public:

        /*
         *
         * GS_I32Type PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for integer type
         * @return Integer type
         */
        IntegerType GetIntegerType() const override;
    };

    /**
     * Builtin I64 type
     */
    class GS_I64Type : public GS_IntegerType {
    public:

        /*
         *
         * GS_I64Type PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for I64 type
         */
        GS_I64Type();

    public:

        /*
         *
         * GS_I64Type PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating I64 type
         * @return I64 type ptr
         */
        static std::shared_ptr<GS_I64Type> Create();

    public:

        /*
         *
         * GS_I64Type PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for integer type
         * @return Integer type
         */
        IntegerType GetIntegerType() const override;
    };

    /**
     * Unsigned integer type
     */
    enum class UIntegerType {
        U8,
        U16,
        U32,
        U64,

        User
    };

    /**
     * Builtin unsigned integer type
     */
    class GS_UIntegerType : public GS_Type {
    public:

        /*
         *
         * GS_UIntegerType PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for unsigned integer type
         * @param name Type name
         */
        explicit GS_UIntegerType(UString name);

    public:

        /*
         *
         * GS_UIntegerType PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating unsigned integer type
         * @param name Type name
         * @return Unsigned integer type ptr
         */
        static std::shared_ptr<GS_UIntegerType> Create(UString name);

    public:

        /*
         *
         * GS_UIntegerType PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for type of type
         * @return Type of type
         */
        TypeType GetType() const override;

    public:

        /*
         *
         * GS_UIntegerType PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Getter for unsigned integer type
         * @return Unsigned integer type
         */
        virtual UIntegerType GetUIntegerType() const;
    };

    /**
     * Builtin U8 type
     */
    class GS_U8Type : public GS_UIntegerType {
    public:

        /*
         *
         * GS_U8Type PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for U8 type
         */
        GS_U8Type();

    public:

        /*
         *
         * GS_U8Type PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating U8 type
         * @return U8 type ptr
         */
        static std::shared_ptr<GS_U8Type> Create();

    public:

        /*
         *
         * GS_U8Type PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for unsigned integer type
         * @return Unsigned integer type
         */
        UIntegerType GetUIntegerType() const override;
    };

    /**
     * Builtin U16 type
     */
    class GS_U16Type : public GS_UIntegerType {
    public:

        /*
         *
         * GS_U16Type PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for U16 type
         */
        GS_U16Type();

    public:

        /*
         *
         * GS_U16Type PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating U16 type
         * @return U16 type ptr
         */
        static std::shared_ptr<GS_U16Type> Create();

    public:

        /*
         *
         * GS_U16Type PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for unsigned integer type
         * @return Unsigned integer type
         */
        UIntegerType GetUIntegerType() const override;
    };

    /**
     * Builtin U32 type
     */
    class GS_U32Type : public GS_UIntegerType {
    public:

        /*
         *
         * GS_U32Type PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for U32 type
         */
        GS_U32Type();

    public:

        /*
         *
         * GS_U32Type PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating U32 type
         * @return U32 type ptr
         */
        static std::shared_ptr<GS_U32Type> Create();

    public:

        /*
         *
         * GS_U32Type PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for unsigned integer type
         * @return Unsigned integer type
         */
        UIntegerType GetUIntegerType() const override;
    };

    /**
     * Builtin U64 type
     */
    class GS_U64Type : public GS_UIntegerType {
    public:

        /*
         *
         * GS_U64Type PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for U64 type
         */
        GS_U64Type();

    public:

        /*
         *
         * GS_U64Type PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating U64 type
         * @return U64 type ptr
         */
        static std::shared_ptr<GS_U64Type> Create();

    public:

        /*
         *
         * GS_U64Type PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for unsigned integer type
         * @return Unsigned integer type
         */
        UIntegerType GetUIntegerType() const override;
    };

    /**
     * Builtin String type
     */
    class GS_StringType : public GS_Type {
    public:

        /*
         *
         * GS_StringType PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for String type
         */
        GS_StringType();

    public:

        /*
         *
         * GS_StringType PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating String type
         * @return String type ptr
         */
        static std::shared_ptr<GS_StringType> Create();

    public:

        /*
         *
         * GS_StringType PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for type of type
         * @return Type of type
         */
        TypeType GetType() const override;
    };

    /**
     * Builtin Array type
     */
    class GS_ArrayType : public GS_Type {
    public:

        /*
         *
         * GS_ArrayType PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for Array type
         * @param elementsType Type of array elements
         * @param size Size of array
         * @todo Check
         */
        GS_ArrayType(GSTypePtr elementsType,
                     U64 size);

    public:

        /*
         *
         * GS_ArrayType PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Constructor for Array type
         * @param elementsType Type of array elements
         * @param size Size of array
         * @return Array type ptr
         */
        static std::shared_ptr<GS_ArrayType> Create(GSTypePtr elementsType,
                                                    U64 size);

    public:

        /*
         *
         * GS_ArrayType PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for type of array elements
         * @return Type of array elements
         */
        ConstLRef<GSTypePtr> GetElementsType() const;

        /**
         * Getter for size of array
         * @return Size of array
         */
        U64 GetSize() const;

    public:

        /*
         *
         * GS_ArrayType PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for type of type
         * @return Type of type
         */
        TypeType GetType() const override;

    private:

        /*
         *
         * GS_ArrayType PRIVATE FIELDS
         *
         */

        /**
         * Type of array elements
         */
        GSTypePtr _elementsType;

        /**
         * Size of array
         */
        U64 _size;
    };

    // TODO add type casting function?

    /**
     * Context for containing information about types
     * @todo Caching default types and any types?
     */
    class GS_TypeContext {
    public:

        /*
         *
         * GS_TypeContext PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for type context
         */
        GS_TypeContext();

    public:

        /*
         *
         * GS_TypeContext PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating type context
         * @return Type context ptr
         */
        static std::unique_ptr<GS_TypeContext> Create();

    public:

        /*
         *
         * GS_TypeContext PUBLIC TODO METHODS
         *
         */

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

        /**
         * Getter for Array type
         * @param type Type of array elements
         * @param size Size of array
         * @return Array type
         */
        TypePtr<GS_ArrayType> GetArrayType(GSTypePtr type,
                                           U64 size) const;
    };

    /**
     * Type context ptr type
     */
    using GSTypeContextPtr = std::unique_ptr<GS_TypeContext>;

}

#endif //GSLANGUAGE_GS_TYPE_H
