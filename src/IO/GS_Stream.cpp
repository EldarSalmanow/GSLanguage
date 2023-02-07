#include <GS_Stream.h>

namespace GSLanguageCompiler::IO {

    GS_StdIOStreamsManager::GS_StdIOStreamsManager(LRef<InputStream> standardIn,
                                                   LRef<OutputStream> standardOut,
                                                   LRef<OutputStream> standardErr,
                                                   LRef<OutputStream> standardLog)
            : _standardIn(standardIn),
              _standardOut(standardOut),
              _standardErr(standardErr),
              _standardLog(standardLog) {}

    std::unique_ptr<GS_StdIOStreamsManager> GS_StdIOStreamsManager::Create(LRef<InputStream> standardIn,
                                                                           LRef<OutputStream> standardOut,
                                                                           LRef<OutputStream> standardErr,
                                                                           LRef<OutputStream> standardLog) {
        return std::make_unique<GS_StdIOStreamsManager>(standardIn,
                                                        standardOut,
                                                        standardErr,
                                                        standardLog);
    }

    std::unique_ptr<GS_StdIOStreamsManager> GS_StdIOStreamsManager::Create() {
        return GS_StdIOStreamsManager::Create(std::cin,
                                              std::cout,
                                              std::cerr,
                                              std::clog);
    }

    LRef<InputStream> GS_StdIOStreamsManager::In() {
        return _standardIn;
    }

    LRef<OutputStream> GS_StdIOStreamsManager::Out() {
        return _standardOut;
    }

    LRef<OutputStream> GS_StdIOStreamsManager::Err() {
        return _standardErr;
    }

    LRef<OutputStream> GS_StdIOStreamsManager::Log() {
        return _standardLog;
    }

}
