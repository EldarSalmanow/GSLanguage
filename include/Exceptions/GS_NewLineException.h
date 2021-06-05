#ifndef GSLANGUAGE_GS_NEWLINEEXCEPTION_H
#define GSLANGUAGE_GS_NEWLINEEXCEPTION_H

#include "GS_Exception.h"

namespace GSLanguageCompiler::Exceptions {

    /**
     * Special class error for throwing a newline token to the parser at the moment of meeting
     */
    class GS_NewLineException : public _GS_Exception {
    public:

        GS_NewLineException() = default;
    };

}

#endif //GSLANGUAGE_GS_NEWLINEEXCEPTION_H
