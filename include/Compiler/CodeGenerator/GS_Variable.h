#ifndef GSLANGUAGE_GS_VARIABLE_H
#define GSLANGUAGE_GS_VARIABLE_H

#include <any>
#include <string>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     *
     */
    class GS_Variable {
    public:

        /**
         *
         */
        GS_Variable() = default;

        /**
         *
         * @param name
         * @param data
         */
        GS_Variable(const std::string &name, const std::string &type, std::any &data);

    public:

        /**
         *
         * @return
         */
        std::string getName();

        /**
         *
         * @return
         */
        std::string getType();

        /**
         *
         * @return
         */
        std::any getData();

    private:

        /**
         *
         */
        std::string _name;

        /**
         *
         */
        std::string _type;

        /**
         *
         */
        std::any _data;
    };

}

#endif //GSLANGUAGE_GS_VARIABLE_H
