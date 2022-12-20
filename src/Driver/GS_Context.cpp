#include <GS_Context.h>

namespace GSLanguageCompiler::Driver {

    GS_Context::GS_Context(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                           IO::GSSourceManagerPtr sourceManager,
                           IO::GSMessageHandlerPtr messageHandler)
            : _stdIOStreamsManager(std::move(stdIOStreamsManager)),
              _sourceManager(std::move(sourceManager)),
              _messageHandler(std::move(messageHandler)) {}

    std::unique_ptr<GS_Context> GS_Context::Create(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                                                   IO::GSSourceManagerPtr sourceManager,
                                                   IO::GSMessageHandlerPtr messageHandler) {
        return std::make_unique<GS_Context>(std::move(stdIOStreamsManager),
                                            std::move(sourceManager),
                                            std::move(messageHandler));
    }

    std::unique_ptr<GS_Context> GS_Context::Create(IO::GSSourceManagerPtr sourceManager) {
        auto stdIOStreamsManager = IO::GS_StdIOStreamsManager::Create();
        auto messageHandler = IO::GS_MessageHandler::Create(stdIOStreamsManager->Out(),
                                                            *sourceManager);

        return GS_Context::Create(std::move(stdIOStreamsManager),
                                  std::move(sourceManager),
                                  std::move(messageHandler));
    }

    std::unique_ptr<GS_Context> GS_Context::Create() {
        auto stdIOStreamsManager = IO::GS_StdIOStreamsManager::Create();
        auto sourceManager = IO::GS_SourceManager::Create();
        auto messageHandler = IO::GS_MessageHandler::Create(stdIOStreamsManager->Out(),
                                                            *sourceManager);

        return GS_Context::Create(std::move(stdIOStreamsManager),
                                  std::move(sourceManager),
                                  std::move(messageHandler));
    }

    std::unique_ptr<GS_Context> GS_Context::Create(GS_Arguments arguments) {
        auto movedArguments = std::move(arguments);

        auto inputFileNames = movedArguments.GetInputFileNames();
        auto &outputFileName = movedArguments.GetOutputFileName();

        auto stdIOStreamsManager = IO::GS_StdIOStreamsManager::Create();
        auto sourceManager = IO::GS_SourceManager::Create();
        auto messageHandler = IO::GS_MessageHandler::Create(stdIOStreamsManager->Out(),
                                                            *sourceManager);

        for (auto &inputFileName : inputFileNames) {
            sourceManager->AddFileSource(inputFileName);
        }

        return GS_Context::Create(std::move(stdIOStreamsManager),
                                  std::move(sourceManager),
                                  std::move(messageHandler));
    }

    LRef<std::istream> GS_Context::In() {
        return _stdIOStreamsManager->In();
    }

    LRef<std::ostream> GS_Context::Out() {
        return _stdIOStreamsManager->Out();
    }

    LRef<std::ostream> GS_Context::Err() {
        return _stdIOStreamsManager->Err();
    }

    LRef<std::ostream> GS_Context::Log() {
        return _stdIOStreamsManager->Log();
    }

    ConstLRef<IO::GS_Source> GS_Context::AddSource(IO::GSSourcePtr source) {
        return _sourceManager->AddSource(std::move(source));
    }

    ConstLRef<IO::GS_Source> GS_Context::AddFileSource(UString name) {
        return _sourceManager->AddFileSource(std::move(name));
    }

    ConstLRef<IO::GS_Source> GS_Context::AddStringSource(UString source) {
        return _sourceManager->AddStringSource(std::move(source));
    }

    ConstLRef<IO::GS_Source> GS_Context::AddCustomSource(UString source, UString name) {
        return _sourceManager->AddCustomSource(std::move(source), std::move(name));
    }

    std::optional<IO::GS_Source> GS_Context::GetSource(U64 sourceHash) const {
        return _sourceManager->GetSource(sourceHash);
    }

    std::optional<IO::GS_Source> GS_Context::GetSource(IO::GS_SourceName sourceName) const {
        return _sourceManager->GetSource(std::move(sourceName));
    }

    std::optional<IO::GS_Source> GS_Context::GetFileSource(UString fileName) const {
        return _sourceManager->GetFileSource(std::move(fileName));
    }

    std::optional<IO::GS_Source> GS_Context::GetCustomSource(UString sourceName) const {
        return _sourceManager->GetCustomSource(std::move(sourceName));
    }

    ConstLRef<IO::GSSourcePtrArray> GS_Context::GetSources() const {
        return _sourceManager->GetSources();
    }

    Void GS_Context::Write(IO::GS_Message message) {
        _messageHandler->Write(std::move(message));
    }

    LRef<IO::GS_StdIOStreamsManager> GS_Context::GetStdIOStreamsManager() {
        return *_stdIOStreamsManager;
    }

    LRef<IO::GS_SourceManager> GS_Context::GetSourceManager() {
        return *_sourceManager;
    }

    LRef<IO::GS_MessageHandler> GS_Context::GetMessageHandler() {
        return *_messageHandler;
    }

}
