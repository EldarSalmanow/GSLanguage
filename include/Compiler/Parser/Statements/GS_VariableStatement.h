#ifndef GSLANGUAGE_GS_VARIABLESTATEMENT_H
#define GSLANGUAGE_GS_VARIABLESTATEMENT_H

#include "GS_Statement.h"
#include "../Values/GS_IntegerValue.h"

namespace GSLanguageCompiler::Statements {

    /**
     *
     */
    class GS_VariableStatement : public GS_Statement {
    public:

        /**
         *
         * @param name
         * @param number
         */
        GS_VariableStatement(std::string name, GSValuePointer value) {
            this->_name = name;
            this->_value = value;
            this->_type = value->getLiteralType();
        }

        /**
         *
         * @param name
         * @param number
         * @param type
         */
        GS_VariableStatement(std::string name, GSValuePointer value, Literal type) {
            this->_name = name;
            this->_value = value;
            this->_type = type;
        }

    public:

        /**
         *
         */
         std::string toString() override {
             return "[ "
             + this->_name
             + ": "
             + literalToString(this->_type)
             + " = "
             + this->_value->getString()
             + " ]";
         }

    private:

        /**
         *
         */
        GSValuePointer _value;

        /**
         *
         */
        std::string _name;

        /**
         *
         */
        Literal _type;
    };

}

#endif //GSLANGUAGE_GS_VARIABLESTATEMENT_H
