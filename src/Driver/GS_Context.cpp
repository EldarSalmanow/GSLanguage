#include <GS_Context.h>

namespace GSLanguageCompiler::Driver {

    GS_Context::GS_Context(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                           IO::GSSourceManagerPtr       sourceManager,
                           IO::GSOutStreamPtr           outputStream,
                           AST::GSASTContextPtr         astContext)
            : _stdIOStreamsManager(std::move(stdIOStreamsManager)),
              _sourceManager(std::move(sourceManager)),
              _outputStream(std::move(outputStream)),
              _astContext(std::move(astContext)) {}

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

    IO::GSOutStreamPtr GS_Context::GetOutputStream() const {
        return _outputStream;
    }

    AST::GSASTContextPtr GS_Context::GetASTContext() const {
        return _astContext;
    }

}
