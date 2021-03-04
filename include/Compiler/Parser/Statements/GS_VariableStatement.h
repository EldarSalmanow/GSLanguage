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
        GS_VariableStatement(std::string name, Values::GS_IntegerValue number) {
            this->_name = name;
            this->_number = number;
            this->_type = number.getLiteralType();
        }

        /**
         *
         * @param name
         * @param number
         * @param type
         */
        GS_VariableStatement(std::string name, Values::GS_IntegerValue number, Literal type) {
            this->_name = name;
            this->_number = number;
            this->_type = type;
        }

    public:

        /**
         *
         */
         std::string toString() override {
             return "GS_VariableStatement  :  "
             "Name: " +
             this->_name +
             " Value: " +
             std::to_string(this->_number.getNumber()) +
             " Type: " +
             literalToString(this->_type) +
             "\n";
         }

    private:

        /**
         *
         */
        Values::GS_IntegerValue _number;

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
