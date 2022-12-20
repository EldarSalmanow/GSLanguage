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

    std::unique_ptr<GS_Session> GS_Session::Create(GSContextPtr context) {
        return std::make_unique<GS_Session>(std::move(context));
    }

    std::unique_ptr<GS_Session> GS_Session::Create() {
        return GS_Session::Create(GS_Context::Create());
    }

    CompilingResult GS_Session::Run() {
        auto &sources = GetSources();

        // TODO update

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

            // todo add flag for debug compiler mode
            Debug::DumpAST(translationUnitDeclaration, *this);

            translationUnitDeclarations.emplace_back(translationUnitDeclaration);
        }

        return CompilingResult::Success;
    }

    LRef<std::istream> GS_Session::In() {
        return _context->In();
    }

    LRef<std::ostream> GS_Session::Out() {
        return _context->Out();
    }

    LRef<std::ostream> GS_Session::Err() {
        return _context->Err();
    }

    LRef<std::ostream> GS_Session::Log() {
        return _context->Log();
    }

    ConstLRef<IO::GS_Source> GS_Session::AddSource(IO::GSSourcePtr source) {
        return _context->AddSource(std::move(source));
    }

    ConstLRef<IO::GS_Source> GS_Session::AddFileSource(UString name) {
        return _context->AddFileSource(std::move(name));
    }

    ConstLRef<IO::GS_Source> GS_Session::AddStringSource(UString source) {
        return _context->AddStringSource(std::move(source));
    }

    ConstLRef<IO::GS_Source> GS_Session::AddCustomSource(UString source, UString name) {
        return _context->AddCustomSource(std::move(source),
                                         std::move(name));
    }

    std::optional<IO::GS_Source> GS_Session::GetSource(U64 sourceHash) const {
        return _context->GetSource(sourceHash);
    }

    std::optional<IO::GS_Source> GS_Session::GetSource(IO::GS_SourceName sourceName) const {
        return _context->GetSource(std::move(sourceName));
    }

    std::optional<IO::GS_Source> GS_Session::GetFileSource(UString fileName) const {
        return _context->GetFileSource(std::move(fileName));
    }

    std::optional<IO::GS_Source> GS_Session::GetCustomSource(UString sourceName) const {
        return _context->GetCustomSource(std::move(sourceName));
    }

    ConstLRef<IO::GSSourcePtrArray> GS_Session::GetSources() const {
        return _context->GetSources();
    }

    Void GS_Session::Write(IO::GS_Message message) {
        _context->Write(std::move(message));
    }

    LRef<IO::GS_StdIOStreamsManager> GS_Session::GetStdIOStreamsManager() {
        return _context->GetStdIOStreamsManager();
    }

    LRef<IO::GS_SourceManager> GS_Session::GetSourceManager() {
        return _context->GetSourceManager();
    }

    LRef<IO::GS_MessageHandler> GS_Session::GetMessageHandler() {
        return _context->GetMessageHandler();
    }

    LRef<GS_Context> GS_Session::GetContext() {
        return *_context;
    }

    LRef<AST::GS_ASTContext> GS_Session::GetASTContext() {
        return *_astContext;
    }

    LRef<Semantic::GS_TableOfSymbols> GS_Session::GetTableOfSymbols() {
        return *_tableOfSymbols;
    }

}
