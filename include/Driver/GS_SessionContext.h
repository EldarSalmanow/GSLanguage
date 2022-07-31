#ifndef GSLANGUAGE_GS_SESSIONCONTEXT_H
#define GSLANGUAGE_GS_SESSIONCONTEXT_H

#include <vector>

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler {

    namespace IO {

        class GS_IOContext;

    }

    namespace AST {

        class GS_ASTContext;

    }

    namespace Driver {

        class GS_SessionContext {
        public:

            GS_SessionContext(std::shared_ptr<IO::GS_IOContext> ioContext, std::shared_ptr<AST::GS_ASTContext> astContext);

        public:

            static std::shared_ptr<GS_SessionContext> Create(std::shared_ptr<IO::GS_IOContext> ioContext, std::shared_ptr<AST::GS_ASTContext> astContext);

            static std::shared_ptr<GS_SessionContext> Create(I32 argc, Ptr<Ptr<C>> argv);

        public:

            std::shared_ptr<IO::GS_IOContext> GetIOContext() const;

            std::shared_ptr<AST::GS_ASTContext> GetASTContext() const;

        private:

            std::shared_ptr<IO::GS_IOContext> _ioContext;

            std::shared_ptr<AST::GS_ASTContext> _astContext;
        };

        using GSSessionContextPtr = std::shared_ptr<GS_SessionContext>;

        using GSSessionContextPtrArray = std::vector<GSSessionContextPtr>;

    }

}

#endif //GSLANGUAGE_GS_SESSIONCONTEXT_H
