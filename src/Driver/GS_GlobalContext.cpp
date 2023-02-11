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

        // TODO add ErrAndExit (?) function
        GlobalContext().Err() << stringStream.String();

        GlobalContext().Exit();
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

    LRef<std::istream> GS_GlobalContext::In() {
        return _stdIOStreamsManager->In();
    }

    LRef<std::ostream> GS_GlobalContext::Out() {
        return _stdIOStreamsManager->Out();
    }

    LRef<std::ostream> GS_GlobalContext::Err() {
        return _stdIOStreamsManager->Err();
    }

    LRef<std::ostream> GS_GlobalContext::Log() {
        return _stdIOStreamsManager->Log();
    }

    Void GS_GlobalContext::Exit(I32 exitCode) {
        std::exit(exitCode);
    }

    Void GS_GlobalContext::Exit() {
        auto exitCode = StaticCast<I32>(Result::Err);

        Exit(exitCode);
    }

    GS_GlobalContext::GS_GlobalContext()
            : _stdIOStreamsManager(nullptr) {}

    GS_GlobalContext GS_GlobalContext::_context = GS_GlobalContext();
    
    LRef<GS_GlobalContext> GlobalContext() {
        return GS_GlobalContext::GetInstance();
    }

}
