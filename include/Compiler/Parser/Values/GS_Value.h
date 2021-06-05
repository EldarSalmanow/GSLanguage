#ifndef GSLANGUAGE_GS_VALUE_H
#define GSLANGUAGE_GS_VALUE_H

#include <memory>
#include <any>

#include <Compiler/Parser/Values/LiteralTypes.h>

#include <Exceptions/GS_TypeCastException.h>
#include <Exceptions/GS_NotSupportedException.h>

namespace GSLanguageCompiler::Parser {

    class GS_Value;

    typedef std::shared_ptr<GS_Value> GSValuePointer;

    /**
     *
     */
    class GS_Value {
    public:

        /**
         *
         * @return
         */
        std::any getData();

        /**
         *
         * @tparam _ValueType
         * @param data
         */
        template<typename _ValueType>
        void setData(_ValueType &data) {
            this->_data = data;
        }

        /**
         *
         */
        void deleteData();

        /**
         *
         * @return
         */
        std::string getType();

        /**
         *
         * @return
         */
        bool getIsLiteralType();

        /**
         *
         * @param type
         */
        void setType(const std::string &type);

        /**
         *
         * @param isLiteralType
         */
        void setIsLiteralType(bool isLiteralType);

    public:

        /**
         *
         * @param type
         * @return
         */
        virtual GSValuePointer castTo(Literal type) = 0;

    private:

        /**
         *
         */
        std::any _data;

        /**
         *
         */
        std::string _type;

        /**
         *
         */
        bool _isLiteralType;
    };

}

#endif //GSLANGUAGE_GS_VALUE_H
