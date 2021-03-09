#ifndef GSLANGUAGE_GS_STRINGEXPRESSION_H
#define GSLANGUAGE_GS_STRINGEXPRESSION_H

#include "GS_Expression.h"

#include "../Values/GS_StringValue.h"

namespace GSLanguageCompiler::Expressions {

    /**
     *
     */
    class GS_StringExpression : public GS_Expression {
    public:

        /**
         *
         * @param string
         */
        GS_StringExpression(std::string string) {
            this->_string = Values::GS_StringValue(string);
        }

    public:

        /**
         *
         * @return
         */
        Values::GS_StringValue getStringValue() {
            return this->_string;
        }

    public:

        /**
         *
         * @return
         */
        GSValuePointer result() override {
            return GSValuePointer(new Values::GS_StringValue(this->_string.getString()));
        }

        /**
         *
         * @return
         */
        std::string toStringForDebug() override {
            return this->_string.getString();
        }

    private:

        /**
         *
         */
        Values::GS_StringValue _string;

    };

}

#endif //GSLANGUAGE_GS_STRINGEXPRESSION_H
