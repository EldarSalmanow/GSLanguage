#include <GS_Stream.h>

namespace GSLanguageCompiler::IO {

    GS_StdIOStreamManager::GS_StdIOStreamManager(LRef<InputStream> standardIn,
                                                 LRef<OutputStream> standardOut,
                                                 LRef<OutputStream> standardErr,
                                                 LRef<OutputStream> standardLog)
            : _standardIn(standardIn),
              _standardOut(standardOut),
              _standardErr(standardErr),
              _standardLog(standardLog) {}

    std::unique_ptr<GS_StdIOStreamManager> GS_StdIOStreamManager::Create(LRef<InputStream> standardIn,
                                                                         LRef<OutputStream> standardOut,
                                                                         LRef<OutputStream> standardErr,
                                                                         LRef<OutputStream> standardLog) {
        return std::make_unique<GS_StdIOStreamManager>(standardIn,
                                                       standardOut,
                                                       standardErr,
                                                       standardLog);
    }

    std::unique_ptr<GS_StdIOStreamManager> GS_StdIOStreamManager::Create() {
        return GS_StdIOStreamManager::Create(std::cin,
                                             std::cout,
                                             std::cerr,
                                             std::clog);
    }

    LRef<InputStream> GS_StdIOStreamManager::In() {
        return _standardIn;
    }

    LRef<OutputStream> GS_StdIOStreamManager::Out() {
        return _standardOut;
    }

    LRef<OutputStream> GS_StdIOStreamManager::Err() {
        return _standardErr;
    }

    LRef<OutputStream> GS_StdIOStreamManager::Log() {
        return _standardLog;
    }

}
