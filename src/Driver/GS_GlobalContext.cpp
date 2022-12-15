#include <csignal>

#include <GS_GlobalContext.h>

namespace GSLanguageCompiler::Driver {

    Void DefaultSignalHandler(I32 signal) {
        UStringStream stringStream;

        if (signal == SIGINT) {
            stringStream << "Signal: SIGINT"_us;
        } else if (signal == SIGILL) {
            stringStream << "Signal: SIGILL"_us;
        } else if (signal == SIGFPE) {
            stringStream << "Signal: SIGFPE"_us;
        } else if (signal == SIGSEGV) {
            stringStream << "Signal: SIGSEGV"_us;
        } else if (signal == SIGTERM) {
            stringStream << "Signal: SIGTERM"_us;
        } else if (signal == SIGBREAK) {
            stringStream << "Signal: SIGBREAK"_us;
        } else if (signal == SIGABRT) {
            stringStream << "Signal: SIGABRT"_us;
        } else if (signal == SIGABRT_COMPAT) {
            stringStream << "Signal: SIGABRT_COMPAT"_us;
        } else {
            stringStream << "Not default signal: "_us
                         << signal;
        }

        stringStream << "\n"_us;

        GlobalContext().Err(stringStream.String());

        GlobalContext().Exit(StaticCast<I32>(Result::Err));
    }

    LRef<GS_GlobalContext> GS_GlobalContext::GetInstance() {
        return _context;
    }

    Result GS_GlobalContext::InitializeIO(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager) {
        _stdIOStreamsManager = std::move(stdIOStreamsManager);

        return Result::Ok;
    }

    Result GS_GlobalContext::InitializeSignals(SignalHandlerFunctionPtr signalHandlerFunction) {
        if (signal(SIGINT,         signalHandlerFunction) == SIG_ERR
         || signal(SIGILL,         signalHandlerFunction) == SIG_ERR
         || signal(SIGFPE,         signalHandlerFunction) == SIG_ERR
         || signal(SIGSEGV,        signalHandlerFunction) == SIG_ERR
         || signal(SIGTERM,        signalHandlerFunction) == SIG_ERR
         || signal(SIGBREAK,       signalHandlerFunction) == SIG_ERR
         || signal(SIGABRT,        signalHandlerFunction) == SIG_ERR
         || signal(SIGABRT_COMPAT, signalHandlerFunction) == SIG_ERR) {
            return Result::Err;
        }

        return Result::Ok;
    }

    Result GS_GlobalContext::Initialize(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                                        SignalHandlerFunctionPtr signalHandlerFunction) {
        if (InitializeIO(std::move(stdIOStreamsManager)) != Result::Ok
         || InitializeSignals(signalHandlerFunction)     != Result::Ok) {
            return Result::Err;
        }

        return Result::Ok;
    }

    Result GS_GlobalContext::Initialize() {
        return Initialize(IO::GS_StdIOStreamsManager::Create(),
                          DefaultSignalHandler);
    }

    Void GS_GlobalContext::In(LRef<UString> string) {
        _stdIOStreamsManager->In(string);
    }

    Void GS_GlobalContext::Out(ConstLRef<UString> string) {
        _stdIOStreamsManager->Out(string);
    }

    Void GS_GlobalContext::Err(ConstLRef<UString> string) {
        _stdIOStreamsManager->Err(string);
    }

    Void GS_GlobalContext::Log(ConstLRef<UString> string) {
        _stdIOStreamsManager->Log(string);
    }

    Void GS_GlobalContext::Exit(I32 exitCode) {
        // TODO add cleanup ?

        std::exit(exitCode);
    }

    Void GS_GlobalContext::ErrAndExit(ConstLRef<UString> string, I32 exitCode) {
        Err(string);

        Exit(exitCode);
    }

    Void GS_GlobalContext::ErrAndExit(ConstLRef<UString> string) {
        ErrAndExit(string,
                   StaticCast<I32>(Result::Err));
    }

    IO::GSInStreamPtr GS_GlobalContext::GetStdInStream() const {
        return _stdIOStreamsManager->GetStdInStream();
    }

    IO::GSOutStreamPtr GS_GlobalContext::GetStdOutStream() const {
        return _stdIOStreamsManager->GetStdOutStream();
    }

    IO::GSOutStreamPtr GS_GlobalContext::GetStdErrStream() const {
        return _stdIOStreamsManager->GetStdErrStream();
    }

    IO::GSOutStreamPtr GS_GlobalContext::GetStdLogStream() const {
        return _stdIOStreamsManager->GetStdLogStream();
    }

    GS_GlobalContext::GS_GlobalContext()
            : _stdIOStreamsManager(nullptr) {}

    LRef<GS_GlobalContext> GlobalContext() {
        return GS_GlobalContext::GetInstance();
    }

}
