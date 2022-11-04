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

    GS_StdIOStreamsManager::GS_StdIOStreamsManager(GSInStreamPtr standardIn,
                                                   GSOutStreamPtr standardOut,
                                                   GSOutStreamPtr standardErr,
                                                   GSOutStreamPtr standardLog)
            : _standardIn(std::move(standardIn)),
              _standardOut(std::move(standardOut)),
              _standardErr(std::move(standardErr)),
              _standardLog(std::move(standardLog)) {}

    std::shared_ptr<GS_StdIOStreamsManager> GS_StdIOStreamsManager::Create(GSInStreamPtr standardIn,
                                                                           GSOutStreamPtr standardOut,
                                                                           GSOutStreamPtr standardErr,
                                                                           GSOutStreamPtr standardLog) {
        return std::make_shared<GS_StdIOStreamsManager>(std::move(standardIn),
                                                        std::move(standardOut),
                                                        std::move(standardErr),
                                                        std::move(standardLog));
    }

    std::shared_ptr<GS_StdIOStreamsManager> GS_StdIOStreamsManager::Create() {
        return GS_StdIOStreamsManager::Create(GS_InConsoleStream::CreateCIn(),
                                              GS_OutConsoleStream::CreateCOut(),
                                              GS_OutConsoleStream::CreateCErr(),
                                              GS_OutConsoleStream::CreateCLog());
    }

    Void GS_StdIOStreamsManager::In(LRef<UString> string) {
        _standardIn->GetInStream() >> string;
    }

    Void GS_StdIOStreamsManager::Out(ConstLRef<UString> string) {
        _standardOut->GetOutStream() << string;
    }

    Void GS_StdIOStreamsManager::Err(ConstLRef<UString> string) {
        _standardErr->GetOutStream() << string;
    }

    Void GS_StdIOStreamsManager::Log(ConstLRef<UString> string) {
        _standardLog->GetOutStream() << string;
    }

    GSInStreamPtr GS_StdIOStreamsManager::GetStdInStream() const {
        return _standardIn;
    }

    GSOutStreamPtr GS_StdIOStreamsManager::GetStdOutStream() const {
        return _standardOut;
    }

    GSOutStreamPtr GS_StdIOStreamsManager::GetStdErrStream() const {
        return _standardErr;
    }

    GSOutStreamPtr GS_StdIOStreamsManager::GetStdLogStream() const {
        return _standardLog;
    }

}
