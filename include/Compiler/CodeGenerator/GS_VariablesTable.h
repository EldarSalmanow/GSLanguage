#ifndef GSLANGUAGE_GS_VARIABLESTABLE_H
#define GSLANGUAGE_GS_VARIABLESTABLE_H

#include <map>

#include <Compiler/CodeGenerator/GS_Variable.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     *
     */
    class GS_VariablesTable {
    public:

        GS_VariablesTable() = default;

    public:

        /**
         *
         */
        std::map<size_t, GS_Variable> _table;
    };

}

#endif //GSLANGUAGE_GS_VARIABLESTABLE_H
