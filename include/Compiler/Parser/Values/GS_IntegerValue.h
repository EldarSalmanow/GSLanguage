#ifndef GSLANGUAGE_GS_INTEGERVALUE_H
#define GSLANGUAGE_GS_INTEGERVALUE_H

#include "GS_Value.h"

namespace GSLanguageCompiler::Values {

    /**
     *
     */
    class GS_IntegerValue : public GS_Value {
    public:

        /**
         *
         */
        GS_IntegerValue() {
            this->_type = Literal::LITERAL_NULL;
        }

        /**
         *
         * @param value
         */
        GS_IntegerValue(int number) {
            this->_number = number;
            this->_type = Literal::LITERAL_INT;
        }

    public:

        /**
         *
         * @return
         */
        int getValue() {
            return this->_number;
        }

    public:

        /**
         *
         * @return
         */
        int getInt() override {
            return this->_number;
        }

        /**
         *
         * @return
         */
        std::string getString() override {
            return std::to_string(this->_number);
        }

        /**
         *
         * @return
         */
        Literal getLiteralType() override {
            return _type;
        }

    private:

        /**
         *
         */
        Literal _type;

        /**
         *
         */
        int _number;
    };

}

#endif //GSLANGUAGE_GS_INTEGERVALUE_H
