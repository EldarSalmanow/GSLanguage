#ifndef GSLANGUAGE_GS_TABLEOFSYMBOLS_H
#define GSLANGUAGE_GS_TABLEOFSYMBOLS_H

#include <map>

#include "Values/GS_Value.h"

#include "../../Exceptions/GS_NotFoundVariableException.h"

namespace GSLanguageCompiler {

    /**
     *
     */
    class GS_TableOfSymbols {
    public:

        /**
         *
         * @param name
         * @return
         */
        static GSValuePointer get(std::string name);

        /**
         *
         * @param name
         * @param value
         */
        static void add(std::string name, GSValuePointer value);

    public:

        /**
         *
         * @return
         */
        static std::vector<std::string> getVariableNames();

    private:

        /**
         *
         */
        inline static std::vector<std::string> variableNames;

        /**
         *
         */
        inline static std::map<std::string, GSValuePointer> tableOfSymbols;
    };

}

#endif //GSLANGUAGE_GS_TABLEOFSYMBOLS_H
