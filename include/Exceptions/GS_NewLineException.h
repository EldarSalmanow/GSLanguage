#ifndef GSLANGUAGE_GS_NEWLINEEXCEPTION_H
#define GSLANGUAGE_GS_NEWLINEEXCEPTION_H

#include "GS_Exception.h"

namespace GSLanguageCompiler::Exceptions {

    /**
     *
     */
    class GS_NewLineException : public _GS_Exception {
    public:

        GS_NewLineException() = default;
    };

}

#endif //GSLANGUAGE_GS_NEWLINEEXCEPTION_H
