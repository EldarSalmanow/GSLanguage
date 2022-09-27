#include <GS_GlobalContext.h>

namespace GSLanguageCompiler::Driver {

    I32 GS_GlobalContext::InitializeIO(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager) {
        _stdIOStreamsManager = std::move(stdIOStreamsManager);

        return 0;
    }

    I32 GS_GlobalContext::Initialize(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager) {
        if (InitializeIO(std::move(stdIOStreamsManager))) {
            return 1;
        }

        return 0;
    }

    I32 GS_GlobalContext::Initialize() {
        return Initialize(IO::GS_StdIOStreamsManager::Create());
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
