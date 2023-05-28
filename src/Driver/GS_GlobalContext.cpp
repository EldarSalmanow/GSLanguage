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

        GlobalContext().Exit(stringStream.String());
    }

    LRef<GS_GlobalContext> GS_GlobalContext::GetInstance() {
        return _context;
    }

    Result GS_GlobalContext::InitializeIO(IO::GSStdIOStreamManagerPtr stdIOStreamManager) {
        _stdIOStreamManager = std::move(stdIOStreamManager);

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

    Result GS_GlobalContext::Initialize(IO::GSStdIOStreamManagerPtr stdIOStreamManager,
                                        SignalHandlerFunctionPtr signalHandlerFunction) {
        if (InitializeIO(std::move(stdIOStreamManager)) != Result::Ok
         || InitializeSignals(signalHandlerFunction)    != Result::Ok) {
            return Result::Err;
        }

        return Result::Ok;
    }

    Result GS_GlobalContext::Initialize() {
        return Initialize(IO::GS_StdIOStreamManager::Create(),
                          DefaultSignalHandler);
    }

    LRef<std::istream> GS_GlobalContext::In() {
        return _stdIOStreamManager->In();
    }

    LRef<std::ostream> GS_GlobalContext::Out() {
        return _stdIOStreamManager->Out();
    }

    LRef<std::ostream> GS_GlobalContext::Err() {
        return _stdIOStreamManager->Err();
    }

    LRef<std::ostream> GS_GlobalContext::Log() {
        return _stdIOStreamManager->Log();
    }

    Void GS_GlobalContext::Exit(UString exitMessage,
                                I32 exitCode) {
        auto movedExitMessage = std::move(exitMessage);

        _stdIOStreamManager->Err() << " |--------------------------------------------------"_us << std::endl
                                   << "/"_us << std::endl;

        _stdIOStreamManager->Err() << "| Exiting from program!" << std::endl;
        _stdIOStreamManager->Err() << "| Exit message: " << movedExitMessage << std::endl;
        _stdIOStreamManager->Err() << "| Exit code: " << exitCode << std::endl;

        _stdIOStreamManager->Err() << "\\"_us << std::endl
                                   << " |--------------------------------------------------"_us << std::endl;

        std::exit(exitCode);
    }

    Void GS_GlobalContext::Exit(UString exitMessage) {
        Exit(std::move(exitMessage),
             ToExitCode(Result::Err));
    }

    Void GS_GlobalContext::Exit(I32 exitCode) {
        Exit("<unknown>",
             exitCode);
    }

    Void GS_GlobalContext::Exit() {
        Exit("<unknown>",
             ToExitCode(Result::Err));
    }

    GS_GlobalContext::GS_GlobalContext()
            : _stdIOStreamManager(nullptr) {}

    GS_GlobalContext GS_GlobalContext::_context = GS_GlobalContext();
    
    LRef<GS_GlobalContext> GlobalContext() {
        return GS_GlobalContext::GetInstance();
    }

}
