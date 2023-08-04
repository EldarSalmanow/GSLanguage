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

        Bool,

        Char,
        Integer,
        UInteger,
        String,

        Array,
        Range,

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
     * Builtin Bool type
     */
    class GS_BoolType : public GS_Type {
    public:

        /*
         *
         * GS_BoolType PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for Bool type
         */
        GS_BoolType();

    public:

        /*
         *
         * GS_BoolType PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating Bool type
         * @return Bool type ptr
         */
        static std::shared_ptr<GS_BoolType> Create();

    public:

        /*
         *
         * GS_BoolType PUBLIC OVERRIDE METHODS
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
         * Creating Array type
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

    /**
     * Builtin Range type
     */
    class GS_RangeType : public GS_Type {
    public:

        /*
         *
         * GS_RangeType PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for Range type
         * @param elementsType Type of range elements
         */
        explicit GS_RangeType(GSTypePtr elementsType);

    public:

        /*
         *
         * GS_RangeType PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating Range type
         * @param elementsType Type of range elements
         * @return Range type ptr
         */
        static std::shared_ptr<GS_RangeType> Create(GSTypePtr elementsType);

    public:

        /*
         *
         * GS_RangeType PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for type of range elements
         * @return Type of range elements
         */
        ConstLRef<GSTypePtr> GetElementsType() const;

    public:

        /*
         *
         * GS_RangeType PUBLIC OVERRIDE METHODS
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
         * GS_RangeType PRIVATE FIELDS
         *
         */

        /**
         * Type of range elements
         */
        GSTypePtr _elementsType;
    };

    /**
     * Casting type to TypeT
     * @tparam TypeT Type of type
     * @param type Type
     * @return Type or null
     */
    template<typename TypeT>
    inline TypePtr<TypeT> ToType(ConstLRef<GSTypePtr> type) {
        static_assert(std::is_base_of_v<GS_Type, TypeT>,
                      "Type for casting must be inherited from GS_Type!");

        auto typeType = type->GetType();

        switch (typeType) {
            case TypeType::Void: {
                if constexpr (!std::is_same_v<GS_VoidType, TypeT>) {
                    return nullptr;
                }

                break;
            }
            case TypeType::Bool: {
                if constexpr (!std::is_same_v<GS_BoolType, TypeT>) {
                    return nullptr;
                }

                break;
            }
            case TypeType::Char: {
                if constexpr (!std::is_same_v<GS_CharType, TypeT>) {
                    return nullptr;
                }

                break;
            }
            case TypeType::Integer: {
                auto integerType = std::reinterpret_pointer_cast<GS_IntegerType>(type);
                auto integerTypeType = integerType->GetIntegerType();

                if constexpr (std::is_same_v<GS_IntegerType, TypeT>) {
                    break;
                }

                switch (integerTypeType) {
                    case IntegerType::I8: {
                        if constexpr (!std::is_same_v<GS_I8Type, TypeT>) {
                            return nullptr;
                        }

                        break;
                    }
                    case IntegerType::I16: {
                        if constexpr (!std::is_same_v<GS_I16Type, TypeT>) {
                            return nullptr;
                        }

                        break;
                    }
                    case IntegerType::I32: {
                        if constexpr (!std::is_same_v<GS_I32Type, TypeT>) {
                            return nullptr;
                        }

                        break;
                    }
                    case IntegerType::I64: {
                        if constexpr (!std::is_same_v<GS_I64Type, TypeT>) {
                            return nullptr;
                        }

                        break;
                    }
                    case IntegerType::User: {
                        return nullptr;
                    }
                }

                break;
            }
            case TypeType::UInteger: {
                auto uIntegerType = std::reinterpret_pointer_cast<GS_UIntegerType>(type);
                auto uIntegerTypeType = uIntegerType->GetUIntegerType();

                if constexpr (std::is_same_v<GS_UIntegerType, TypeT>) {
                    break;
                }

                switch (uIntegerTypeType) {
                    case UIntegerType::U8: {
                        if constexpr (!std::is_same_v<GS_U8Type, TypeT>) {
                            return nullptr;
                        }

                        break;
                    }
                    case UIntegerType::U16: {
                        if constexpr (!std::is_same_v<GS_U16Type, TypeT>) {
                            return nullptr;
                        }

                        break;
                    }
                    case UIntegerType::U32: {
                        if constexpr (!std::is_same_v<GS_U32Type, TypeT>) {
                            return nullptr;
                        }

                        break;
                    }
                    case UIntegerType::U64: {
                        if constexpr (!std::is_same_v<GS_U64Type, TypeT>) {
                            return nullptr;
                        }

                        break;
                    }
                    case UIntegerType::User: {
                        return nullptr;
                    }
                }

                break;
            }
            case TypeType::String: {
                if constexpr (!std::is_same_v<GS_StringType, TypeT>) {
                    return nullptr;
                }

                break;
            }
            case TypeType::Array: {
                if constexpr (!std::is_same_v<GS_ArrayType, TypeT>) {
                    return nullptr;
                }

                break;
            }
            case TypeType::Range: {
                if constexpr (!std::is_same_v<GS_RangeType, TypeT>) {
                    return nullptr;
                }

                break;
            }
            case TypeType::User: {
                return nullptr;
            }
            default: {
                return nullptr;
            }
        }

        return std::reinterpret_pointer_cast<TypeT>(type);
    }

    /**
     * Context for containing information about types
     * @todo Add caching default types and any types
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
         * GS_TypeContext PUBLIC METHODS
         *
         */

        /**
         * Getter for default Void type
         * @return Void type
         */
        TypePtr<GS_VoidType> GetVoidType() const;

        /**
         * Getter for default Bool type
         * @return Bool type
         */
        TypePtr<GS_BoolType> GetBoolType() const;

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
         * Getter for default Array type
         * @param elementsType Type of array elements
         * @param size Size of array
         * @return Array type
         */
        TypePtr<GS_ArrayType> GetArrayType(GSTypePtr elementsType,
                                           U64 size) const;

        /**
         * Getter for default Range type
         * @param elementsType Type of range elements
         * @return Range type
         */
        TypePtr<GS_RangeType> GetRangeType(GSTypePtr elementsType) const;
    };

    /**
     * Type context ptr type
     */
    using GSTypeContextPtr = std::unique_ptr<GS_TypeContext>;

}

#endif //GSLANGUAGE_GS_TYPE_H
