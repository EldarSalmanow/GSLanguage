#include <GS_Context.h>

namespace GSLanguageCompiler::Driver {

    GS_Context::GS_Context(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                           IO::GSSourceManagerPtr sourceManager,
                           IO::GSMessageHandlerPtr messageHandler)
            : _stdIOStreamsManager(std::move(stdIOStreamsManager)),
              _sourceManager(std::move(sourceManager)),
              _messageHandler(std::move(messageHandler)) {}

    std::shared_ptr<GS_Context> GS_Context::Create(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                                                   IO::GSSourceManagerPtr sourceManager,
                                                   IO::GSMessageHandlerPtr messageHandler) {
        return std::make_shared<GS_Context>(std::move(stdIOStreamsManager),
                                            std::move(sourceManager),
                                            std::move(messageHandler));
    }

    std::shared_ptr<GS_Context> GS_Context::Create(IO::GSSourceManagerPtr sourceManager) {
        auto stdIOStreamsManager = IO::GS_StdIOStreamsManager::Create();
        auto messageHandler = IO::GS_MessageHandler::Create(stdIOStreamsManager->GetStdOutStream(),
                                                            sourceManager);

        return GS_Context::Create(stdIOStreamsManager,
                                  std::move(sourceManager),
                                  messageHandler);
    }

    std::shared_ptr<GS_Context> GS_Context::Create() {
        auto stdIOStreamsManager = IO::GS_StdIOStreamsManager::Create();
        auto sourceManager = IO::GS_SourceManager::Create();
        auto messageHandler = IO::GS_MessageHandler::Create(stdIOStreamsManager->GetStdOutStream(),
                                                            sourceManager);

        return GS_Context::Create(stdIOStreamsManager,
                                  sourceManager,
                                  messageHandler);
    }

    std::shared_ptr<GS_Context> GS_Context::Create(GS_Arguments arguments) {
        auto inputFileNames = arguments.GetInputFileNames();
        auto outputFileName = arguments.GetOutputFileName();

        auto stdIOStreamsManager = IO::GS_StdIOStreamsManager::Create();
        auto sourceManager = IO::GS_SourceManager::Create();
        auto messageHandler = IO::GS_MessageHandler::Create(stdIOStreamsManager->GetStdOutStream(),
                                                            sourceManager);

        for (auto &inputFileName : inputFileNames) {
            auto inputSource = IO::GS_Source::CreateFile(inputFileName);

            sourceManager->AddSource(inputSource);
        }


        return GS_Context::Create(stdIOStreamsManager,
                                  sourceManager,
                                  messageHandler);
    }

    Void GS_Context::In(LRef<UString> string) {
        _stdIOStreamsManager->In(string);
    }

    Void GS_Context::Out(ConstLRef<UString> string) {
        _stdIOStreamsManager->Out(string);
    }

    Void GS_Context::Err(ConstLRef<UString> string) {
        _stdIOStreamsManager->Err(string);
    }

    Void GS_Context::Log(ConstLRef<UString> string) {
        _stdIOStreamsManager->Log(string);
    }

    IO::GSInStreamPtr GS_Context::GetStdInStream() const {
        return _stdIOStreamsManager->GetStdInStream();
    }

    IO::GSOutStreamPtr GS_Context::GetStdOutStream() const {
        return _stdIOStreamsManager->GetStdOutStream();
    }

    IO::GSOutStreamPtr GS_Context::GetStdErrStream() const {
        return _stdIOStreamsManager->GetStdErrStream();
    }

    IO::GSOutStreamPtr GS_Context::GetStdLogStream() const {
        return _stdIOStreamsManager->GetStdLogStream();
    }

    U64 GS_Context::AddSource(IO::GSSourcePtr source) {
        return _sourceManager->AddSource(std::move(source));
    }

    IO::GSSourcePtr GS_Context::GetSource(U64 sourceHash) const {
        return _sourceManager->GetSource(sourceHash);
    }

    IO::GSSourcePtr GS_Context::GetSource(IO::GS_SourceName sourceName) const {
        return _sourceManager->GetSource(std::move(sourceName));
    }

    ConstLRef<IO::GSSourcePtrArray> GS_Context::GetSources() const {
        return _sourceManager->GetSources();
    }

    Void GS_Context::Write(IO::GS_Message message) {
        _messageHandler->Write(std::move(message));
    }

    IO::GSStdIOStreamsManagerPtr GS_Context::GetStdIOStreamsManager() const {
        return _stdIOStreamsManager;
    }

    IO::GSSourceManagerPtr GS_Context::GetSourceManager() const {
        return _sourceManager;
    }

    IO::GSMessageHandlerPtr GS_Context::GetMessageHandler() const {
        return _messageHandler;
    }

}
