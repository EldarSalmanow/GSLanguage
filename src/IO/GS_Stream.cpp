#include <GS_Stream.h>

namespace GSLanguageCompiler::IO {

    GS_StreamInfo::GS_StreamInfo(UString streamName)
            : _streamName(std::move(streamName)) {}

    std::shared_ptr<GS_StreamInfo> GS_StreamInfo::Create(UString streamName) {
        return std::make_shared<GS_StreamInfo>(std::move(streamName));
    }

    std::shared_ptr<GS_StreamInfo> GS_StreamInfo::CreateFileInfo(UString streamName) {
        return GS_StreamInfo::Create(std::move(streamName));
    }

    std::shared_ptr<GS_StreamInfo> GS_StreamInfo::CreateConsoleInfo() {
        return GS_StreamInfo::Create("<console>");
    }

    std::shared_ptr<GS_StreamInfo> GS_StreamInfo::CreateStringInfo() {
        return GS_StreamInfo::Create("<string>");
    }

    Bool GS_StreamInfo::IsFile() const {
        return !IsConsole() && !IsString();
    }

    Bool GS_StreamInfo::IsConsole() const {
        return _streamName == "<console>";
    }

    Bool GS_StreamInfo::IsString() const {
        return _streamName == "<string>";
    }

    UString GS_StreamInfo::GetStreamName() const {
        return _streamName;
    }

    GS_Stream::GS_Stream(GSStreamInfoPtr streamInfo)
            : _streamInfo(std::move(streamInfo)) {}

    GSStreamInfoPtr GS_Stream::GetStreamInfo() const {
        return _streamInfo;
    }

    Bool GS_Stream::IsInStream() const {
        return false;
    }

    Bool GS_Stream::IsOutStream() const {
        return false;
    }

    GS_InStream::GS_InStream(GSStreamInfoPtr streamInfo)
            : GS_Stream(std::move(streamInfo)) {}

    Bool GS_InStream::IsInStream() const {
        return true;
    }

    GS_InFileStream::GS_InFileStream(std::ifstream stream,
                                     GSStreamInfoPtr streamInfo)
            : _stream(std::move(stream)),
              GS_InStream(std::move(streamInfo)) {}

    std::shared_ptr<GS_InFileStream> GS_InFileStream::Create(std::ifstream stream,
                                                             GSStreamInfoPtr streamInfo) {
        return std::make_shared<GS_InFileStream>(std::move(stream),
                                                 std::move(streamInfo));
    }

    std::shared_ptr<GS_InFileStream> GS_InFileStream::CreateInFile(UString name) {
        return GS_InFileStream::Create(std::ifstream(name.AsUTF8()),
                                       GS_StreamInfo::CreateFileInfo(name));
    }

    LRef<std::istream> GS_InFileStream::GetInStream() {
        return _stream;
    }

    GS_InConsoleStream::GS_InConsoleStream(LRef<std::istream> stream,
                                           GSStreamInfoPtr streamInfo)
            : _stream(stream),
              GS_InStream(std::move(streamInfo)) {}

    std::shared_ptr<GS_InConsoleStream> GS_InConsoleStream::Create(LRef<std::istream> stream,
                                                                   GSStreamInfoPtr streamInfo) {
        return std::make_shared<GS_InConsoleStream>(stream,
                                                    std::move(streamInfo));
    }

    std::shared_ptr<GS_InConsoleStream> GS_InConsoleStream::CreateCIn() {
        return GS_InConsoleStream::Create(std::cin,
                                          GS_StreamInfo::CreateConsoleInfo());
    }

    LRef<std::istream> GS_InConsoleStream::GetInStream() {
        return _stream;
    }

    GS_InStringStream::GS_InStringStream(std::istringstream stream, GSStreamInfoPtr streamInfo)
            : _stream(std::move(stream)),
              GS_InStream(std::move(streamInfo)) {}

    std::shared_ptr<GS_InStringStream> GS_InStringStream::Create(std::istringstream stream) {
        return std::make_shared<GS_InStringStream>(std::move(stream),
                                                   GS_StreamInfo::CreateStringInfo());
    }

    std::shared_ptr<GS_InStringStream> GS_InStringStream::Create(UString string) {
        return GS_InStringStream::Create(std::istringstream(string.AsUTF8()));
    }

    LRef<std::istream> GS_InStringStream::GetInStream() {
        return _stream;
    }

    GS_OutStream::GS_OutStream(GSStreamInfoPtr streamInfo)
            : GS_Stream(std::move(streamInfo)) {}

    Bool GS_OutStream::IsOutStream() const {
        return true;
    }

    GS_OutFileStream::GS_OutFileStream(std::ofstream stream,
                                       GSStreamInfoPtr streamInfo)
            : _stream(std::move(stream)),
              GS_OutStream(std::move(streamInfo)) {}

    std::shared_ptr<GS_OutFileStream> GS_OutFileStream::Create(std::ofstream stream,
                                                               GSStreamInfoPtr streamInfo) {
        return std::make_shared<GS_OutFileStream>(std::move(stream),
                                                  std::move(streamInfo));
    }

    std::shared_ptr<GS_OutFileStream> GS_OutFileStream::CreateOutFile(UString name) {
        return GS_OutFileStream::Create(std::ofstream(name.AsUTF8()),
                                        GS_StreamInfo::CreateFileInfo(name));
    }

    LRef<std::ostream> GS_OutFileStream::GetOutStream() {
        return _stream;
    }

    GS_OutConsoleStream::GS_OutConsoleStream(LRef<std::ostream> stream,
                                             GSStreamInfoPtr streamInfo)
            : _stream(stream),
              GS_OutStream(std::move(streamInfo)) {}

    std::shared_ptr<GS_OutConsoleStream> GS_OutConsoleStream::Create(LRef<std::ostream> stream,
                                                                     GSStreamInfoPtr streamInfo) {
        return std::make_shared<GS_OutConsoleStream>(stream,
                                                     std::move(streamInfo));
    }

    std::shared_ptr<GS_OutConsoleStream> GS_OutConsoleStream::CreateCOut() {
        return GS_OutConsoleStream::Create(std::cout,
                                           GS_StreamInfo::CreateConsoleInfo());
    }

    std::shared_ptr<GS_OutConsoleStream> GS_OutConsoleStream::CreateCErr() {
        return GS_OutConsoleStream::Create(std::cerr,
                                           GS_StreamInfo::CreateConsoleInfo());
    }

    std::shared_ptr<GS_OutConsoleStream> GS_OutConsoleStream::CreateCLog() {
        return GS_OutConsoleStream::Create(std::clog,
                                           GS_StreamInfo::CreateConsoleInfo());
    }

    LRef<std::ostream> GS_OutConsoleStream::GetOutStream() {
        return _stream;
    }

    GS_OutStringStream::GS_OutStringStream(std::ostringstream stream,
                                           GSStreamInfoPtr streamInfo)
            : _stream(std::move(stream)),
              GS_OutStream(std::move(streamInfo)) {}

    std::shared_ptr<GS_OutStringStream> GS_OutStringStream::Create(std::ostringstream stream) {
        return std::make_shared<GS_OutStringStream>(std::move(stream),
                                                    GS_StreamInfo::CreateStringInfo());
    }

    std::shared_ptr<GS_OutStringStream> GS_OutStringStream::Create(UString string) {
        return GS_OutStringStream::Create(std::ostringstream(string.AsUTF8()));
    }

    std::shared_ptr<GS_OutStringStream> GS_OutStringStream::Create() {
        return GS_OutStringStream::Create(std::ostringstream());
    }

    LRef<std::ostream> GS_OutStringStream::GetOutStream() {
        return _stream;
    }

    GS_StdIOStreamsManager::GS_StdIOStreamsManager(LRef<std::istream> standardIn,
                                                   LRef<std::ostream> standardOut,
                                                   LRef<std::ostream> standardErr,
                                                   LRef<std::ostream> standardLog)
            : _standardIn(standardIn),
              _standardOut(standardOut),
              _standardErr(standardErr),
              _standardLog(standardLog) {}

    std::unique_ptr<GS_StdIOStreamsManager> GS_StdIOStreamsManager::Create(LRef<std::istream> standardIn,
                                                                           LRef<std::ostream> standardOut,
                                                                           LRef<std::ostream> standardErr,
                                                                           LRef<std::ostream> standardLog) {
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

    LRef<std::istream> GS_StdIOStreamsManager::In() {
        return _standardIn;
    }

    LRef<std::ostream> GS_StdIOStreamsManager::Out() {
        return _standardOut;
    }

    LRef<std::ostream> GS_StdIOStreamsManager::Err() {
        return _standardErr;
    }

    LRef<std::ostream> GS_StdIOStreamsManager::Log() {
        return _standardLog;
    }

}
