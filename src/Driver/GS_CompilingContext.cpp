#include <GS_CompilingContext.h>

namespace GSLanguageCompiler::Driver {

    GS_CompilingContext::GS_CompilingContext(std::shared_ptr<IO::GS_IOContext> ioContext, std::shared_ptr<AST::GS_ASTContext> astContext)
            : _ioContext(std::move(ioContext)), _astContext(std::move(astContext)) {}

    std::shared_ptr<GS_CompilingContext> GS_CompilingContext::Create(std::shared_ptr<IO::GS_IOContext> ioContext, std::shared_ptr<AST::GS_ASTContext> astContext) {
        return std::make_shared<GS_CompilingContext>(std::move(ioContext), std::move(astContext));
    }

    std::shared_ptr<IO::GS_IOContext> GS_CompilingContext::GetIOContext() const {
        return _ioContext;
    }

    std::shared_ptr<AST::GS_ASTContext> GS_CompilingContext::GetASTContext() const {
        return _astContext;
    }

}
