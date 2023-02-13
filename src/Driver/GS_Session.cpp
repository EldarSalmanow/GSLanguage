#include <Parser/Parser.h>

#include <Optimizer/Optimizer.h>

#include <Semantic/Semantic.h>

#include <Debug/Debug.h>

#include <GS_Session.h>

namespace GSLanguageCompiler::Driver {

    Result ToResult(CompilingResult compilingResult) {
        switch (compilingResult) {
            case CompilingResult::Success:
                return Result::Ok;
            case CompilingResult::Failure:
                return Result::Err;
        }
    }

    I32 ToExitCode(CompilingResult compilingResult) {
        return StaticCast<I32>(compilingResult);
    }

    GS_Session::GS_Session(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                           IO::GSSourceManagerPtr sourceManager,
                           IO::GSMessageStreamsManagerPtr messageStreamsManager,
                           AST::GSASTContextPtr astContext,
                           Semantic::GSTableOfSymbolsPtr tableOfSymbols)
            : _stdIOStreamsManager(std::move(stdIOStreamsManager)),
              _sourceManager(std::move(sourceManager)),
              _messageStreamsManager(std::move(messageStreamsManager)),
              _astContext(std::move(astContext)),
              _tableOfSymbols(std::move(tableOfSymbols)) {}

    std::unique_ptr<GS_Session> GS_Session::Create(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                                                   IO::GSSourceManagerPtr sourceManager,
                                                   IO::GSMessageStreamsManagerPtr messageStreamsManager,
                                                   AST::GSASTContextPtr astContext,
                                                   Semantic::GSTableOfSymbolsPtr tableOfSymbols) {
        return std::make_unique<GS_Session>(std::move(stdIOStreamsManager),
                                            std::move(sourceManager),
                                            std::move(messageStreamsManager),
                                            std::move(astContext),
                                            std::move(tableOfSymbols));
    }

    std::unique_ptr<GS_Session> GS_Session::Create() {
        auto stdIOStreamsManager = IO::GS_StdIOStreamsManager::Create();
        auto sourceManager = IO::GS_SourceManager::Create();
        auto messageStreamsManager = IO::GS_MessageStreamsManager::Create(*stdIOStreamsManager,
                                                                          *sourceManager);
        auto astContext = AST::GS_ASTContext::Create();
        auto tableOfSymbols = Semantic::GS_TableOfSymbols::Create();

        return GS_Session::Create(std::move(stdIOStreamsManager),
                                  std::move(sourceManager),
                                  std::move(messageStreamsManager),
                                  std::move(astContext),
                                  std::move(tableOfSymbols));
    }

    std::unique_ptr<GS_Session> GS_Session::Create(GS_Arguments arguments) {
        auto movedArguments = std::move(arguments);

        auto &inputFileNames = movedArguments.GetInputFileNames();
        auto &outputFileName = movedArguments.GetOutputFileName();

        auto session = GS_Session::Create();

        for (auto &inputFileName : inputFileNames) {
            session->AddFileSource(inputFileName);
        }

        return session;
    }

    CompilingResult GS_Session::Run() {
        auto &sources = GetSources();

        AST::GSTranslationUnitDeclarationPtrArray translationUnitDeclarations;

        auto optimizingPasses = {
                Optimizer::CreateConstantFoldingPass()
        };

        for (auto &source : sources) {
            auto translationUnitDeclaration = Parser::ParseProgram(*this, *source);

            Semantic::CreateSymbolsPlaceholderPass()->Run(translationUnitDeclaration, *this);

            for (auto &optimizingPass : optimizingPasses) {
                optimizingPass->Run(translationUnitDeclaration, *this);
            }

            Debug::DumpTableOfSymbols(_tableOfSymbols);

            Debug::DumpAST(translationUnitDeclaration, *this);

            translationUnitDeclarations.emplace_back(translationUnitDeclaration);
        }

        return CompilingResult::Success;
    }

    LRef<std::istream> GS_Session::StdIn() {
        return _stdIOStreamsManager->In();
    }

    LRef<std::ostream> GS_Session::StdOut() {
        return _stdIOStreamsManager->Out();
    }

    LRef<std::ostream> GS_Session::StdErr() {
        return _stdIOStreamsManager->Err();
    }

    LRef<std::ostream> GS_Session::StdLog() {
        return _stdIOStreamsManager->Log();
    }

    ConstLRef<IO::GS_Source> GS_Session::AddSource(IO::GSSourcePtr source) {
        return _sourceManager->AddSource(std::move(source));
    }

    ConstLRef<IO::GS_Source> GS_Session::AddFileSource(UString name) {
        return _sourceManager->AddFileSource(std::move(name));
    }

    ConstLRef<IO::GS_Source> GS_Session::AddStringSource(UString source) {
        return _sourceManager->AddStringSource(std::move(source));
    }

    ConstLRef<IO::GS_Source> GS_Session::AddCustomSource(UString source, UString name) {
        return _sourceManager->AddCustomSource(std::move(source),
                                               std::move(name));
    }

    std::optional<IO::GS_Source> GS_Session::GetSource(U64 sourceHash) const {
        return _sourceManager->GetSource(sourceHash);
    }

    std::optional<IO::GS_Source> GS_Session::GetSource(IO::GS_SourceName sourceName) const {
        return _sourceManager->GetSource(std::move(sourceName));
    }

    std::optional<IO::GS_Source> GS_Session::GetFileSource(UString fileName) const {
        return _sourceManager->GetFileSource(std::move(fileName));
    }

    std::optional<IO::GS_Source> GS_Session::GetCustomSource(UString sourceName) const {
        return _sourceManager->GetCustomSource(std::move(sourceName));
    }

    ConstLRef<IO::GSSourcePtrArray> GS_Session::GetSources() const {
        return _sourceManager->GetSources();
    }

    LRef<IO::GS_MessageStream> GS_Session::Out() {
        return _messageStreamsManager->Out();
    }

    LRef<IO::GS_MessageStream> GS_Session::Err() {
        return _messageStreamsManager->Err();
    }

    LRef<IO::GS_MessageStream> GS_Session::Log() {
        return _messageStreamsManager->Log();
    }

    IO::GS_MessageBuilder GS_Session::Message(UString messageText,
                                              IO::MessageLevel messageLevel,
                                              std::optional<IO::GSByteSourceRange> messageLocationRange) const {
        return IO::GS_MessageBuilder::Create(std::move(messageText),
                                             messageLevel,
                                             messageLocationRange);
    }

    IO::GS_MessageBuilder GS_Session::Message(UString messageText,
                                              IO::MessageLevel messageLevel,
                                              IO::GSByteSourceRange messageLocationRange) const {
        return IO::GS_MessageBuilder::Create(std::move(messageText),
                                             messageLevel,
                                             messageLocationRange);
    }

    IO::GS_MessageBuilder GS_Session::Message(UString messageText,
                                              IO::MessageLevel messageLevel,
                                              IO::GS_ByteSourceLocation messageSourceLocation) const {
        return IO::GS_MessageBuilder::Create(std::move(messageText),
                                             messageLevel,
                                             messageSourceLocation);
    }

    IO::GS_MessageBuilder GS_Session::Message(UString messageText,
                                              IO::MessageLevel messageLevel) const {
        return IO::GS_MessageBuilder::Create(std::move(messageText),
                                             messageLevel);
    }

    IO::GS_MessageBuilder GS_Session::Message() const {
        return IO::GS_MessageBuilder::Create();
    }

    IO::GS_MessageBuilder GS_Session::NoteMessage() const {
        return IO::GS_MessageBuilder::Create().Note();
    }

    IO::GS_MessageBuilder GS_Session::WarningMessage() const {
        return IO::GS_MessageBuilder::Create().Warning();
    }

    IO::GS_MessageBuilder GS_Session::ErrorMessage() const {
        return IO::GS_MessageBuilder::Create().Error();
    }

    IO::GS_MessageBuilder GS_Session::FatalMessage() const {
        return IO::GS_MessageBuilder::Create().Fatal();
    }

    LRef<IO::GS_StdIOStreamsManager> GS_Session::GetStdIOStreamsManager() {
        return *_stdIOStreamsManager;
    }

    LRef<IO::GS_SourceManager> GS_Session::GetSourceManager() {
        return *_sourceManager;
    }

    LRef<IO::GS_MessageStreamsManager> GS_Session::GetMessageStreamsManager() {
        return *_messageStreamsManager;
    }

    LRef<AST::GS_ASTContext> GS_Session::GetASTContext() {
        return *_astContext;
    }

    LRef<Semantic::GS_TableOfSymbols> GS_Session::GetTableOfSymbols() {
        return *_tableOfSymbols;
    }

}
