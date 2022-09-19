#include <GS_Context.h>

namespace GSLanguageCompiler::Driver {

//    GS_Context::GS_Context(IO::GSInStreamPtr    standardIn,
//                           IO::GSOutStreamPtr   standardOut,
//                           IO::GSOutStreamPtr   standardErr,
//                           IO::GSOutStreamPtr   standardLog,
//                           IO::GSSourcePtrArray inputSources,
//                           IO::GSOutStreamPtr   outputStream,
//                           AST::GSASTContextPtr astContext)
//            : _standardIn(std::move(standardIn)),
//              _standardOut(std::move(standardOut)),
//              _standardErr(std::move(standardErr)),
//              _standardLog(std::move(standardLog)),
//              _inputSources(std::move(inputSources)),
//              _outputStream(std::move(outputStream)),
//              _astContext(std::move(astContext)) {}

//    std::shared_ptr<GS_Context> GS_Context::Create(IO::GSInStreamPtr    standardIn,
//                                                   IO::GSOutStreamPtr   standardOut,
//                                                   IO::GSOutStreamPtr   standardErr,
//                                                   IO::GSOutStreamPtr   standardLog,
//                                                   IO::GSSourcePtrArray inputSources,
//                                                   IO::GSOutStreamPtr   outputStream,
//                                                   AST::GSASTContextPtr astContext) {
//        return std::make_shared<GS_Context>(std::move(standardIn),
//                                            std::move(standardOut),
//                                            std::move(standardErr),
//                                            std::move(standardLog),
//                                            std::move(inputSources),
//                                            std::move(outputStream),
//                                            std::move(astContext));
//    }
//
//    std::shared_ptr<GS_Context> GS_Context::Create(IO::GSSourcePtrArray inputSources,
//                                                   IO::GSOutStreamPtr   outputStream,
//                                                   AST::GSASTContextPtr astContext) {
//        return GS_Context::Create(IO::GS_InConsoleStream::CreateCIn(),
//                                  IO::GS_OutConsoleStream::CreateCOut(),
//                                  IO::GS_OutConsoleStream::CreateCErr(),
//                                  IO::GS_OutConsoleStream::CreateCLog(),
//                                  std::move(inputSources),
//                                  std::move(outputStream),
//                                  std::move(astContext));
//    }
//
//    std::shared_ptr<GS_Context> GS_Context::Create(IO::GSSourcePtrArray inputSources,
//                                                   IO::GSOutStreamPtr   outputStream) {
//        return GS_Context::Create(std::move(inputSources),
//                                  std::move(outputStream),
//                                  AST::GS_ASTContext::Create());
//    }
//
//    std::shared_ptr<GS_Context> GS_Context::Create() {
//        return GS_Context::Create(IO::GSSourcePtrArray(),
//                                  IO::GSOutStreamPtr());
//    }

    std::shared_ptr<GS_Context> GS_Context::Create(GS_Arguments arguments) {
        auto inputFileNames = arguments.GetInputFileNames();
        auto outputFileName = arguments.GetOutputFileName();

        auto               sourceManager = IO::GS_SourceManager::Create();
        IO::GSOutStreamPtr outputStream;

        for (auto &inputFileName : inputFileNames) {
            auto inputSource = IO::GS_Source::CreateFile(inputFileName);

            sourceManager->AddSource(inputSource);
        }

        outputStream = IO::GS_OutFileStream::CreateOutFile(outputFileName);

        return GS_Context::Create(sourceManager, outputStream);
    }

//    Void GS_Context::In(LRef<UString> string) {
//        _standardIn->GetInStream() >> string;
//    }
//
//    Void GS_Context::Out(ConstLRef<UString> string) {
//        _standardOut->GetOutStream() << string;
//    }
//
//    Void GS_Context::Err(ConstLRef<UString> string) {
//        _standardErr->GetOutStream() << string;
//    }
//
//    Void GS_Context::Log(ConstLRef<UString> string) {
//        _standardLog->GetOutStream() << string;
//    }

    U64 GS_Context::AddInputSource(IO::GSSourcePtr inputSource) {
        return _sourceManager->AddSource(std::move(inputSource));
    }

    IO::GSSourcePtr GS_Context::GetInputSource(U64 inputSourceHash) const {
        return _sourceManager->GetSource(inputSourceHash);
    }

    IO::GSSourcePtr GS_Context::GetInputSource(IO::GS_SourceName inputSourceName) const {
        return _sourceManager->GetSource(std::move(inputSourceName));
    }

//    IO::GSSourcePtrArray GS_Context::GetInputSources() const {
//        return _inputSources;
//    }

    IO::GSOutStreamPtr GS_Context::GetOutputStream() const {
        return _outputStream;
    }

    AST::GSASTContextPtr GS_Context::GetASTContext() const {
        return _astContext;
    }

}
