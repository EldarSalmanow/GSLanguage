#include <Parser/Parser.h>
#include <Optimizer/Optimizer.h>
#include <Semantic/Semantic.h>
#include <Debug/Debug.h>

#include <GS_Session.h>

namespace GSLanguageCompiler::Driver {

    GS_Session::GS_Session(GSContextPtr context)
            : _context(std::move(context)),
              _astContext(AST::GS_ASTContext::Create()),
              _tableOfSymbols(Semantic::GS_TableOfSymbols::Create()) {}

    std::shared_ptr<GS_Session> GS_Session::Create(GSContextPtr context) {
        return std::make_shared<GS_Session>(std::move(context));
    }

    std::shared_ptr<GS_Session> GS_Session::Create() {
        return GS_Session::Create(GS_Context::Create());
    }

    CompilingResult GS_Session::Run() {
        auto sources = GetSources();

        // TODO update

        AST::GSTranslationUnitDeclarationPtrArray translationUnitDeclarations;

        auto optimizingPasses = {
                Optimizer::CreateConstantFoldingPass()
        };

        for (auto &source : sources) {
            auto translationUnitDeclaration = Parser::RunFrontend(*this, source);

            Semantic::CreateSymbolsPlaceholderPass()->Run(translationUnitDeclaration, *this);

            for (auto &optimizingPass : optimizingPasses) {
                optimizingPass->Run(translationUnitDeclaration, *this);
            }

            Debug::DumpTableOfSymbols(_tableOfSymbols);

            // todo add flag for debug compiler mode
            Debug::DumpAST(translationUnitDeclaration, *this);

            translationUnitDeclarations.emplace_back(translationUnitDeclaration);
        }

        return CompilingResult::Success;
    }

    Void GS_Session::In(LRef<UString> string) {
        _context->In(string);
    }

    Void GS_Session::Out(ConstLRef<UString> string) {
        _context->Out(string);
    }

    Void GS_Session::Err(ConstLRef<UString> string) {
        _context->Err(string);
    }

    Void GS_Session::Log(ConstLRef<UString> string) {
        _context->Log(string);
    }

    IO::GSInStreamPtr GS_Session::GetStdInStream() const {
        return _context->GetStdInStream();
    }

    IO::GSOutStreamPtr GS_Session::GetStdOutStream() const {
        return _context->GetStdOutStream();
    }

    IO::GSOutStreamPtr GS_Session::GetStdErrStream() const {
        return _context->GetStdErrStream();
    }

    IO::GSOutStreamPtr GS_Session::GetStdLogStream() const {
        return _context->GetStdLogStream();
    }

    U64 GS_Session::AddSource(IO::GSSourcePtr source) {
        return _context->AddSource(std::move(source));
    }

    IO::GSSourcePtr GS_Session::GetSource(U64 sourceHash) const {
        return _context->GetSource(sourceHash);
    }

    IO::GSSourcePtr GS_Session::GetSource(IO::GS_SourceName sourceName) const {
        return _context->GetSource(std::move(sourceName));
    }

    IO::GSSourcePtrArray GS_Session::GetSources() const {
        return _context->GetSources();
    }

    Void GS_Session::Write(IO::GSMessagePtr message) {
        _context->Write(std::move(message));
    }

    IO::GSStdIOStreamsManagerPtr GS_Session::GetStdIOStreamsManager() const {
        return _context->GetStdIOStreamsManager();
    }

    IO::GSSourceManagerPtr GS_Session::GetSourceManager() const {
        return _context->GetSourceManager();
    }

    IO::GSMessageHandlerPtr GS_Session::GetMessageHandler() const {
        return _context->GetMessageHandler();
    }

    Semantic::GSTypeContextPtr GS_Session::GetTypeContext() const {
        return _astContext->GetTypeContext();
    }

    GSContextPtr GS_Session::GetContext() const {
        return _context;
    }

    AST::GSASTContextPtr GS_Session::GetASTContext() const {
        return _astContext;
    }

    Semantic::GSTableOfSymbolsPtr GS_Session::GetTableOfSymbols() const {
        return _tableOfSymbols;
    }

}
