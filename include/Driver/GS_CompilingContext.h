#ifndef GSLANGUAGE_GS_COMPILINGCONTEXT_H
#define GSLANGUAGE_GS_COMPILINGCONTEXT_H

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler {

    namespace IO {

        class GS_IOContext;

    }

    namespace AST {

        class GS_ASTContext;

    }

    namespace Driver {

        class GS_CompilingContext {
        public:

            GS_CompilingContext(std::shared_ptr<IO::GS_IOContext> ioContext, std::shared_ptr<AST::GS_ASTContext> astContext)
                    : _ioContext(std::move(ioContext)), _astContext(std::move(astContext)) {}

        public:

            static std::shared_ptr<GS_CompilingContext> Create(std::shared_ptr<IO::GS_IOContext> ioContext, std::shared_ptr<AST::GS_ASTContext> astContext) {
                return std::make_shared<GS_CompilingContext>(std::move(ioContext), std::move(astContext));
            }

        public:

            std::shared_ptr<IO::GS_IOContext> GetIOContext() const {
                return _ioContext;
            }

            std::shared_ptr<AST::GS_ASTContext> GetASTContext() const {
                return _astContext;
            }

        private:

            std::shared_ptr<IO::GS_IOContext> _ioContext;

            std::shared_ptr<AST::GS_ASTContext> _astContext;
        };

        using GSCompilingContextPtr = std::shared_ptr<GS_CompilingContext>;

    }

}

#endif //GSLANGUAGE_GS_COMPILINGCONTEXT_H
