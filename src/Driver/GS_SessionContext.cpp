#include <args.hxx>

#include <IO/IO.h>
#include <AST/AST.h>

#include <GS_SessionContext.h>

namespace GSLanguageCompiler::Driver {

    GS_SessionContext::GS_SessionContext(std::shared_ptr<IO::GS_IOContext> ioContext, std::shared_ptr<AST::GS_ASTContext> astContext)
            : _ioContext(std::move(ioContext)), _astContext(std::move(astContext)) {}

    std::shared_ptr<GS_SessionContext> GS_SessionContext::Create(std::shared_ptr<IO::GS_IOContext> ioContext, std::shared_ptr<AST::GS_ASTContext> astContext) {
        return std::make_shared<GS_SessionContext>(std::move(ioContext), std::move(astContext));
    }

    std::shared_ptr<GS_SessionContext> GS_SessionContext::Create(I32 argc, Ptr<Ptr<C>> argv) {
        args::ArgumentParser parser("GSLanguageCompiler - Compiler for GSLanguage");
        args::HelpFlag helpFlag(parser, "help", "Display help description about GSLanguageCompiler", {'h', "help"});
        args::ValueFlag<std::string> inputFile(parser, "file", "File for compiling", {'f', "file"}, args::Options::Required);
        args::ValueFlag<std::string> outputFile(parser, "output", "Output file", {'o', "out"}, args::Options::Required);

        try {
            parser.ParseCLI(argc, argv);
        } catch (LRef<args::Help> help) {
            std::cout << parser.Help();

            return nullptr;
        } catch (LRef<args::Error> error) {
            std::cout << error.what() << std::endl << std::endl;

            std::cout << parser.Help();

            return nullptr;
        }

        IO::GSSourcePtrArray inputSources;

        if (inputFile) {
            inputSources.emplace_back(IO::GS_Source::CreateFile(inputFile.Get()));
        }

        IO::GSOutStreamPtr outputStream;

        if (outputFile) {
            outputStream = IO::GS_OutFileStream::CreateOutFile(outputFile.Get());
        }

        auto ioContext = IO::GS_IOContext::Create(inputSources, outputStream);

        auto astContext = AST::GS_ASTContext::Create();

        auto compilingContext = Driver::GS_SessionContext::Create(ioContext, astContext);

        return compilingContext;
    }

    std::shared_ptr<IO::GS_IOContext> GS_SessionContext::GetIOContext() const {
        return _ioContext;
    }

    std::shared_ptr<AST::GS_ASTContext> GS_SessionContext::GetASTContext() const {
        return _astContext;
    }

}
