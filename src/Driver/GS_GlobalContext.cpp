#include <GS_GlobalContext.h>

namespace GSLanguageCompiler::Driver {

    I32 GS_GlobalContext::InitializeIO(IO::GSInStreamPtr  standardIn,
                                       IO::GSOutStreamPtr standardOut,
                                       IO::GSOutStreamPtr standardErr,
                                       IO::GSOutStreamPtr standardLog) {
        _standardIn  = std::move(standardIn);
        _standardOut = std::move(standardOut);
        _standardErr = std::move(standardErr);
        _standardLog = std::move(standardLog);

        return 0;
    }

    I32 GS_GlobalContext::Initialize(IO::GSInStreamPtr  standardIn,
                                       IO::GSOutStreamPtr standardOut,
                                       IO::GSOutStreamPtr standardErr,
                                       IO::GSOutStreamPtr standardLog) {
        if (!InitializeIO(std::move(standardIn),
                          std::move(standardOut),
                          std::move(standardErr),
                          std::move(standardLog))) {
            return 1;
        }

        return 0;
    }

    I32 GS_GlobalContext::Initialize() {
        return Initialize(IO::GS_InConsoleStream::CreateCIn(),
                          IO::GS_OutConsoleStream::CreateCOut(),
                          IO::GS_OutConsoleStream::CreateCErr(),
                          IO::GS_OutConsoleStream::CreateCLog());
    }

    Void GS_GlobalContext::In(LRef<UString> string) {
        _standardIn->GetInStream() >> string;
    }

    Void GS_GlobalContext::Out(ConstLRef<UString> string) {
        _standardOut->GetOutStream() << string;
    }

    Void GS_GlobalContext::Err(ConstLRef<UString> string) {
        _standardErr->GetOutStream() << string;
    }

    Void GS_GlobalContext::Log(ConstLRef<UString> string) {
        _standardLog->GetOutStream() << string;
    }

}
