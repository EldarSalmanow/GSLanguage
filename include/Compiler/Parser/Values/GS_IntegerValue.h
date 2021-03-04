#ifndef GSLANGUAGE_GS_INTEGERVALUE_H
#define GSLANGUAGE_GS_INTEGERVALUE_H

#include "GS_Value.h"

namespace GSLanguageCompiler::Values {

    /**
     *
     */
    class GS_IntegerValue : public GS_Value {
    public:

        GS_IntegerValue() {
            this->_type = Literal::LITERAL_NULL;
        }

        /**
         *
         * @param number
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
        Literal getLiteralType() override {
            return _type;
        }

    public:

        /**
         *
         * @return
         */
        int getNumber() {
            return this->_number;
        }

    private:

        Literal _type;

        /**
         *
         */
        int _number;
    };

}

#endif //GSLANGUAGE_GS_INTEGERVALUE_H
