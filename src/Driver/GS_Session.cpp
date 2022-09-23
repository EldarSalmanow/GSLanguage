#include <Debug/Debug.h>

#include <GS_Session.h>

namespace GSLanguageCompiler::Driver {

    GS_Session::GS_Session(GSContextPtr context)
            : _context(std::move(context)) {}

    std::shared_ptr<GS_Session> GS_Session::Create(GSContextPtr context) {
        return std::make_shared<GS_Session>(std::move(context));
    }

    std::shared_ptr<GS_Session> GS_Session::Create() {
        return GS_Session::Create(GS_Context::Create());
    }

    CompilingResult GS_Session::Run() {
        auto sources = _context->GetSourceManager()->GetSources(); // temp

        // TODO

        GSCompilationUnitPtrArray compilationUnits;

        for (auto &source : sources) {
            auto compilationUnit = GS_CompilationUnit::Create(source, _context);

            compilationUnit->Compile();

            Debug::DumpAST(compilationUnit->GetNode());

            compilationUnits.emplace_back(compilationUnit);
        }

        return CompilingResult::Success;
    }

    GSContextPtr GS_Session::GetContext() const {
        return _context;
    }

}
