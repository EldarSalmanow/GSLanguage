#include <GS_Context.h>

namespace GSLanguageCompiler::Driver {

    GS_Context::GS_Context(IO::GSInStreamPtr    standardIn,
                           IO::GSOutStreamPtr   standardOut,
                           IO::GSOutStreamPtr   standardErr,
                           IO::GSOutStreamPtr   standardLog,
                           IO::GSSourcePtrArray inputSources,
                           IO::GSOutStreamPtr   outputStream,
                           AST::GSASTContextPtr astContext)
            : _standardIn(std::move(standardIn)),
              _standardOut(std::move(standardOut)),
              _standardErr(std::move(standardErr)),
              _standardLog(std::move(standardLog)),
              _inputSources(std::move(inputSources)),
              _outputStream(std::move(outputStream)),
              _astContext(std::move(astContext)) {}

    std::shared_ptr<GS_Context> GS_Context::Create(IO::GSInStreamPtr    standardIn,
                                                   IO::GSOutStreamPtr   standardOut,
                                                   IO::GSOutStreamPtr   standardErr,
                                                   IO::GSOutStreamPtr   standardLog,
                                                   IO::GSSourcePtrArray inputSources,
                                                   IO::GSOutStreamPtr   outputStream,
                                                   AST::GSASTContextPtr astContext) {
        return std::make_shared<GS_Context>(std::move(standardIn),
                                            std::move(standardOut),
                                            std::move(standardErr),
                                            std::move(standardLog),
                                            std::move(inputSources),
                                            std::move(outputStream),
                                            std::move(astContext));
    }

    std::shared_ptr<GS_Context> GS_Context::Create(IO::GSSourcePtrArray inputSources,
                                                   IO::GSOutStreamPtr   outputStream,
                                                   AST::GSASTContextPtr astContext) {
        return GS_Context::Create(IO::GS_InConsoleStream::CreateCIn(),
                                  IO::GS_OutConsoleStream::CreateCOut(),
                                  IO::GS_OutConsoleStream::CreateCErr(),
                                  IO::GS_OutConsoleStream::CreateCLog(),
                                  std::move(inputSources),
                                  std::move(outputStream),
                                  std::move(astContext));
    }

    std::shared_ptr<GS_Context> GS_Context::Create(IO::GSSourcePtrArray inputSources,
                                                   IO::GSOutStreamPtr   outputStream) {
        return GS_Context::Create(std::move(inputSources),
                                  std::move(outputStream),
                                  AST::GS_ASTContext::Create());
    }

    std::shared_ptr<GS_Context> GS_Context::Create() {
        return GS_Context::Create(IO::GSSourcePtrArray(),
                                  IO::GSOutStreamPtr());
    }

    std::shared_ptr<GS_Context> GS_Context::Create(GS_Arguments arguments) {
        auto inputFileNames = arguments.GetInputFileNames();
        auto outputFileName = arguments.GetOutputFileName();

        IO::GSSourcePtrArray inputSources;
        IO::GSOutStreamPtr   outputStream;

        for (auto &inputFileName : inputFileNames) {
            auto inputSource = IO::GS_Source::CreateFile(inputFileName);

            inputSources.emplace_back(inputSource);
        }

        outputStream = IO::GS_OutFileStream::CreateOutFile(outputFileName);

        return GS_Context::Create(inputSources, outputStream);
    }

    Void GS_Context::In(LRef<UString> string) {
        _standardIn->GetInStream() >> string;
    }

    Void GS_Context::Out(ConstLRef<UString> string) {
        _standardOut->GetOutStream() << string;
    }

    Void GS_Context::Err(ConstLRef<UString> string) {
        _standardErr->GetOutStream() << string;
    }

    Void GS_Context::Log(ConstLRef<UString> string) {
        _standardLog->GetOutStream() << string;
    }

    Void GS_Context::AddInputSource(IO::GSSourcePtr inputSource) {
        _inputSources.emplace_back(std::move(inputSource));
    }

    IO::GSSourcePtr GS_Context::GetInputSource(U64 inputSourceHash) const {
        for (auto &inputSource : _inputSources) {
            if (inputSource->GetHash() == inputSourceHash) {
                return inputSource;
            }
        }

        return nullptr;
    }

    IO::GSSourcePtr GS_Context::GetInputSource(IO::GS_SourceName inputSourceName) const {
        for (auto &inputSource : _inputSources) {
            if (inputSource->GetName() == inputSourceName) {
                return inputSource;
            }
        }

        return nullptr;
    }

    Void GS_Context::Message(UString message, IO::MessageLevel messageLevel) const {

    }

    Void GS_Context::Message(UString message, IO::MessageLevel messageLevel, IO::GS_SourceLocation sourceLocation, UString text) const {

    }

    Void GS_Context::Message(UString message, IO::MessageLevel messageLevel, std::vector<IO::GS_SourceLocation> sourceLocations, std::vector<UString> texts) const {

    }

    IO::GSSourcePtrArray GS_Context::GetInputSources() const {
        return _inputSources;
    }

    IO::GSOutStreamPtr GS_Context::GetOutputStream() const {
        return _outputStream;
    }

    AST::GSASTContextPtr GS_Context::GetASTContext() const {
        return _astContext;
    }

}
