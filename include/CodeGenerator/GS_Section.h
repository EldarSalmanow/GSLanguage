#ifndef GSLANGUAGE_GS_SECTION_H
#define GSLANGUAGE_GS_SECTION_H

#include <string>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     *
     */
    class GS_Section {
    public:

        /**
         *
         */
        GS_Section() = default;

    public:

        /**
         *
         * @param line
         */
        void addLineToSection(const std::string &line);

    public:

        /**
         *
         * @return
         */
        std::string getSectionCode();

    private:

        /**
         *
         */
        std::string _sectionCode;
    };

}

#endif //GSLANGUAGE_GS_SECTION_H
