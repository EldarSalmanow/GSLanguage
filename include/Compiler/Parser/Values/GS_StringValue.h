#ifndef GSLANGUAGE_GS_STRINGVALUE_H
#define GSLANGUAGE_GS_STRINGVALUE_H

#include "GS_Value.h"

namespace GSLanguageCompiler::Values {

    /**
     *
     */
    class GS_StringValue : public GS_Value {
    public:

       /**
        *
        */
       GS_StringValue() {
           this->_type = Literal::LITERAL_NULL;
       }

       /**
        *
        * @param value
        */
       GS_StringValue(std::string value) {
           this->_value = value;
           this->_type = Literal::LITERAL_STRING;
       }

    public:

        /**
         *
         * @return
         */
        int getInt() override {
            int number;
            try {
                number = std::stoi(this->_value);
            } catch (std::exception &exception) {
                throw Exceptions::GS_TypeCastException("Can not cast string value to int!");
            }
            return number;
        }

        /**
         *
         * @return
         */
        std::string getString() override {
            return this->_value;
        }

        /**
         *
         * @return
         */
        Literal getLiteralType() override {
            return this->_type;
        }

    private:

       /**
        *
        */
       Literal _type;

       /**
        *
        */
       std::string _value;
    };

}

#endif //GSLANGUAGE_GS_STRINGVALUE_H
