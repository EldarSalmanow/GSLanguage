#ifndef GSLANGUAGE_GS_GLOBALCONTEXT_H
#define GSLANGUAGE_GS_GLOBALCONTEXT_H

#include <IO/IO.h>

namespace GSLanguageCompiler::Driver {

    class GS_GlobalContext {
    public:

        GS_GlobalContext() = delete;

    public:

        static I32 InitializeIO(IO::GSInStreamPtr  standardIn,
                                IO::GSOutStreamPtr standardOut,
                                IO::GSOutStreamPtr standardErr,
                                IO::GSOutStreamPtr standardLog);

        static I32 Initialize(IO::GSInStreamPtr  standardIn,
                              IO::GSOutStreamPtr standardOut,
                              IO::GSOutStreamPtr standardErr,
                              IO::GSOutStreamPtr standardLog);

        static I32 Initialize();

    public:

        static Void In(LRef<UString> string);

        static Void Out(ConstLRef<UString> string);

        static Void Err(ConstLRef<UString> string);

        static Void Log(ConstLRef<UString> string);

    private:

        inline static IO::GSInStreamPtr _standardIn   = nullptr;

        inline static IO::GSOutStreamPtr _standardOut = nullptr;

        inline static IO::GSOutStreamPtr _standardErr = nullptr;

        inline static IO::GSOutStreamPtr _standardLog = nullptr;
    };

}

#endif //GSLANGUAGE_GS_GLOBALCONTEXT_H
