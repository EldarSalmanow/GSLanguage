#ifndef GSLANGUAGE_GS_TABLEOFSYMBOLS_H
#define GSLANGUAGE_GS_TABLEOFSYMBOLS_H

#include <map>

#include <Parser/Nodes/GS_Value.h>

namespace GSLanguageCompiler::Interpreter {

    /**
     *
     */
    class GS_TableOfSymbols {
    public:

        /**
         *
         */
        GS_TableOfSymbols();

    public:

        /**
         *
         * @param name
         * @param value
         * @return
         */
        GSVoid addVariable(GSString name, Parser::GSValuePtr value);

        /**
         *
         * @param name
         * @return
         */
        Parser::GSValuePtr findVariable(GSString name);

    private:

        /**
         *
         */
        std::map<GSString, Parser::GSValuePtr> _variableNameToValue;
    };

    /**
     *
     */
    extern GS_TableOfSymbols tableOfSymbols;

}

#endif //GSLANGUAGE_GS_TABLEOFSYMBOLS_H
