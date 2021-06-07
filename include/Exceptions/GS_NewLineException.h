#ifndef GSLANGUAGE_GS_NEWLINEEXCEPTION_H
#define GSLANGUAGE_GS_NEWLINEEXCEPTION_H

namespace GSLanguageCompiler::Exceptions {

    /**
     * Special class error for throwing a newline token to the parser at the moment of meeting
     */
    class GS_NewLineException {
    public:

        GS_NewLineException() = default;
    };

}

#endif //GSLANGUAGE_GS_NEWLINEEXCEPTION_H
