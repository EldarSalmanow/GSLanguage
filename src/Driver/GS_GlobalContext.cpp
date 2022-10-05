#include <csignal>

#include <GS_GlobalContext.h>

namespace GSLanguageCompiler::Driver {

    Void DefaultSignalHandler(I32 signal) {
        if (signal == SIGINT) {
            GS_GlobalContext::Err("Signal: SIGINT\n");
        } else if (signal == SIGILL) {
            GS_GlobalContext::Err("Signal: SIGILL\n");
        } else if (signal == SIGFPE) {
            GS_GlobalContext::Err("Signal: SIGFPE\n");
        } else if (signal == SIGSEGV) {
            GS_GlobalContext::Err("Signal: SIGSEGV\n");
        } else if (signal == SIGTERM) {
            GS_GlobalContext::Err("Signal: SIGTERM\n");
        } else if (signal == SIGBREAK) {
            GS_GlobalContext::Err("Signal: SIGBREAK\n");
        } else if (signal == SIGABRT) {
            GS_GlobalContext::Err("Signal: SIGABRT\n");
        } else if (signal == SIGABRT_COMPAT) {
            GS_GlobalContext::Err("Signal: SIGABRT_COMPAT\n");
        } else {
            UStringStream stringStream;

            stringStream << "Not default signal: "_us
                         << signal
                         << "\n"_us;

            GS_GlobalContext::Err(stringStream.String());
        }
    }

    I32 GS_GlobalContext::InitializeIO(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager) {
        _stdIOStreamsManager = std::move(stdIOStreamsManager);

        return 0;
    }

    I32 GS_GlobalContext::InitializeSignals(SignalHandlerFunctionPtr signalHandlerFunction) {
        if (signal(SIGINT,         signalHandlerFunction) == SIG_ERR
         || signal(SIGILL,         signalHandlerFunction) == SIG_ERR
         || signal(SIGFPE,         signalHandlerFunction) == SIG_ERR
         || signal(SIGSEGV,        signalHandlerFunction) == SIG_ERR
         || signal(SIGTERM,        signalHandlerFunction) == SIG_ERR
         || signal(SIGBREAK,       signalHandlerFunction) == SIG_ERR
         || signal(SIGABRT,        signalHandlerFunction) == SIG_ERR
         || signal(SIGABRT_COMPAT, signalHandlerFunction) == SIG_ERR) {
            return 1;
        }

        return 0;
    }

    I32 GS_GlobalContext::Initialize(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager, SignalHandlerFunctionPtr signalHandlerFunction) {
        if (InitializeIO(std::move(stdIOStreamsManager))
         || InitializeSignals(signalHandlerFunction)) {
            return 1;
        }

        return 0;
    }

    I32 GS_GlobalContext::Initialize() {
        return Initialize(IO::GS_StdIOStreamsManager::Create(), DefaultSignalHandler);
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

}
