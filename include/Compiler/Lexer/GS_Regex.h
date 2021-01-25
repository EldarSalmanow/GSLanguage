#ifndef GSLANGUAGE_GS_REGEX_H
#define GSLANGUAGE_GS_REGEX_H

#include <regex>

namespace GSLanguageCompiler {

    /**
     * Type of regular expression
     * ALPHABET_... - the alphabet of a language (includes large and small characters)
     * NUMBER_...   - any numeric representations
     */
    enum RegexType {
        NUMBER_SIMPLE,      // 0..9
        ALPHABET_ENGLISH    // a..z A..Z
    };

    extern std::regex _numberExpression;

    extern std::regex _wordEnglishLowerCaseExpression;
    extern std::regex _wordEnglishUpperCaseExpression;

}

#endif //GSLANGUAGE_GS_REGEX_H
