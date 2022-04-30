#ifndef GSLANGUAGE_GS_TYPE_H
#define GSLANGUAGE_GS_TYPE_H

#include <GSCrossPlatform/CrossPlatform.h>

#include <AST/GS_Statement.h>

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
        virtual Bool IsLiteralType() const;

        virtual Bool IsStructType() const {
            return false;
        }

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

    class StructureMethod {
    public:

        StructureMethod(UString name, GSStatementPtrArray body)
                : _name(std::move(name)), _body(std::move(body)) {}

    public:

        static StructureMethod Create(UString name, GSStatementPtrArray body) {
            return StructureMethod(std::move(name), std::move(body));
        }

    public:

        UString GetName() const {
            return _name;
        }

        GSStatementPtrArray GetBody() const {
            return _body;
        }

    private:

        UString _name;

        GSStatementPtrArray _body;
    };

    class StructureField {
    public:

        StructureField(UString name, GSTypePtr type)
                : _name(std::move(name)), _type(std::move(type)) {}

    public:

        static StructureField Create(UString name, GSTypePtr type) {
            return StructureField(std::move(name), std::move(type));
        }

    public:

        UString GetName() const {
            return _name;
        }

        GSTypePtr GetType() const {
            return _type;
        }

    private:

        UString _name;

        GSTypePtr _type;
    };

#include <optional>

    class StructType : public GS_Type {
    public:

        StructType(UString name, Vector<StructureMethod> methods, Vector<StructureField> fields)
                : _name(std::move(name)), _methods(std::move(methods)), _fields(std::move(fields)), GS_Type(_name) {}

    public:

        static SharedPtr<StructType> Create(UString name, Vector<StructureMethod> methods, Vector<StructureField> fields) {
            return std::make_shared<StructType>(std::move(name), std::move(methods), std::move(fields));
        }

    public:

        std::optional<StructureMethod> FindMethod(UString name) {
            for (auto &method : _methods) {
                if (method.GetName() == name) {
                    return std::make_optional(method);
                }
            }

            return std::nullopt;
        }

    public:

        UString GetName() const {
            return _name;
        }

        Vector<StructureMethod> GetMethods() const {
            return _methods;
        }

        Vector<StructureField> GetFields() const {
            return _fields;
        }

    public:

        Bool IsStructType() const override {
            return true;
        }

    private:

        UString _name;

        Vector<StructureMethod> _methods;

        Vector<StructureField> _fields;
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
        static SharedPtr<GS_LiteralType> Create(UString name);

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
