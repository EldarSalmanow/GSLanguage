#include <GS_Context.h>

namespace GSLanguageCompiler::Driver {

    GS_Context::GS_Context(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                           IO::GSSourceManagerPtr       sourceManager,
                           IO::GSMessageHandlerPtr      messageHandler,
                           IO::GSOutStreamPtr           outputStream,
                           AST::GSASTContextPtr         astContext)
            : _stdIOStreamsManager(std::move(stdIOStreamsManager)),
              _sourceManager(std::move(sourceManager)),
              _messageHandler(std::move(messageHandler)),
              _outputStream(std::move(outputStream)),
              _astContext(std::move(astContext)) {}

    std::shared_ptr<GS_Context> GS_Context::Create(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                                                   IO::GSSourceManagerPtr       sourceManager,
                                                   IO::GSMessageHandlerPtr      messageHandler,
                                                   IO::GSOutStreamPtr           outputStream,
                                                   AST::GSASTContextPtr         astContext) {
        return std::make_shared<GS_Context>(std::move(stdIOStreamsManager),
                                            std::move(sourceManager),
                                            std::move(messageHandler),
                                            std::move(outputStream),
                                            std::move(astContext));
    }

    std::shared_ptr<GS_Context> GS_Context::Create(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                                                   IO::GSSourceManagerPtr sourceManager,
                                                   IO::GSMessageHandlerPtr messageHandler,
                                                   IO::GSOutStreamPtr outputStream) {
        auto astContext = AST::GS_ASTContext::Create();

        return GS_Context::Create(std::move(stdIOStreamsManager),
                                  std::move(sourceManager),
                                  std::move(messageHandler),
                                  std::move(outputStream),
                                  astContext);
    }

    std::shared_ptr<GS_Context> GS_Context::Create(IO::GSSourceManagerPtr sourceManager,
                                                   IO::GSOutStreamPtr outputStream,
                                                   AST::GSASTContextPtr astContext) {
        auto stdIOStreamsManager = IO::GS_StdIOStreamsManager::Create();
        auto messageHandler = IO::GS_MessageHandler::Create(stdIOStreamsManager->GetStdOutStream(), sourceManager);

        return GS_Context::Create(stdIOStreamsManager,
                                  std::move(sourceManager),
                                  messageHandler,
                                  std::move(outputStream),
                                  std::move(astContext));
    }

    std::shared_ptr<GS_Context> GS_Context::Create(IO::GSSourceManagerPtr sourceManager,
                                                   IO::GSOutStreamPtr outputStream) {
        auto stdIOStreamsManager = IO::GS_StdIOStreamsManager::Create();
        auto messageHandler = IO::GS_MessageHandler::Create(stdIOStreamsManager->GetStdOutStream(), sourceManager);
        auto astContext = AST::GS_ASTContext::Create();

        return GS_Context::Create(stdIOStreamsManager,
                                  std::move(sourceManager),
                                  messageHandler,
                                  std::move(outputStream),
                                  astContext);
    }

    std::shared_ptr<GS_Context> GS_Context::Create() {
        auto stdIOStreamsManager = IO::GS_StdIOStreamsManager::Create();
        auto sourceManager = IO::GS_SourceManager::Create();
        auto messageHandler = IO::GS_MessageHandler::Create(stdIOStreamsManager->GetStdOutStream(), sourceManager);
        auto outputStream = IO::GSOutStreamPtr();
        auto astContext = AST::GS_ASTContext::Create();

        return GS_Context::Create(stdIOStreamsManager,
                                  sourceManager,
                                  messageHandler,
                                  outputStream,
                                  astContext);
    }

    std::shared_ptr<GS_Context> GS_Context::Create(GS_Arguments arguments) {
        auto inputFileNames = arguments.GetInputFileNames();
        auto outputFileName = arguments.GetOutputFileName();

        auto stdIOStreamsManager = IO::GS_StdIOStreamsManager::Create();
        auto sourceManager = IO::GS_SourceManager::Create();
        auto messageHandler = IO::GS_MessageHandler::Create(stdIOStreamsManager->GetStdOutStream(), sourceManager);
        IO::GSOutStreamPtr outputStream;
        auto astContext = AST::GS_ASTContext::Create();

        for (auto &inputFileName : inputFileNames) {
            auto inputSource = IO::GS_Source::CreateFile(inputFileName);

            sourceManager->AddSource(inputSource);
        }


        // TODO: create container class for code holding
//        outputStream = IO::GS_OutFileStream::CreateOutFile(outputFileName);
        outputStream = nullptr;

        return GS_Context::Create(stdIOStreamsManager,
                                  sourceManager,
                                  messageHandler,
                                  outputStream,
                                  astContext);
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

    IO::GSSourcePtrArray GS_Context::GetSources() const {
        return _sourceManager->GetSources();
    }

    Void GS_Context::Write(IO::GSMessagePtr message) {
        _messageHandler->Write(std::move(message));
    }

    Semantic::GSTypeContextPtr GS_Context::GetTypeContext() const {
        return _astContext->GetTypeContext();
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

    IO::GSOutStreamPtr GS_Context::GetOutputStream() const {
        return _outputStream;
    }

    AST::GSASTContextPtr GS_Context::GetASTContext() const {
        return _astContext;
    }

}
