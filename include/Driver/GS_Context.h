#ifndef GSLANGUAGE_GS_CONTEXT_H
#define GSLANGUAGE_GS_CONTEXT_H

#include <IO/IO.h>

#include <AST/AST.h>

#include <Driver/GS_Arguments.h>

namespace GSLanguageCompiler::Driver {

    // TODO
    class GS_Context {
    public:

        GS_Context(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                   IO::GSSourceManagerPtr       sourceManager,
                   IO::GSOutStreamPtr           outputStream,
                   AST::GSASTContextPtr         astContext);

    public:

        static std::shared_ptr<GS_Context> Create(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                                                  IO::GSSourceManagerPtr       sourceManager,
                                                  IO::GSOutStreamPtr           outputStream,
                                                  AST::GSASTContextPtr         astContext);

        static std::shared_ptr<GS_Context> Create(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                                                  IO::GSSourceManagerPtr       sourceManager,
                                                  IO::GSOutStreamPtr           outputStream);

        static std::shared_ptr<GS_Context> Create(IO::GSSourceManagerPtr sourceManager,
                                                  IO::GSOutStreamPtr     outputStream,
                                                  AST::GSASTContextPtr   astContext);

        static std::shared_ptr<GS_Context> Create(IO::GSSourceManagerPtr sourceManager,
                                                  IO::GSOutStreamPtr     outputStream);

        static std::shared_ptr<GS_Context> Create();

    public:

        static std::shared_ptr<GS_Context> Create(GS_Arguments arguments);

    public:

        IO::GSStdIOStreamsManagerPtr GetStdIOStreamsManager() const;

        IO::GSSourceManagerPtr GetSourceManager() const;

        IO::GSOutStreamPtr GetOutputStream() const;

        AST::GSASTContextPtr GetASTContext() const;

    private:

        IO::GSStdIOStreamsManagerPtr _stdIOStreamsManager;

        IO::GSSourceManagerPtr _sourceManager;

        IO::GSOutStreamPtr   _outputStream;

        AST::GSASTContextPtr _astContext;
    };

    using GSContextPtr = std::shared_ptr<GS_Context>;

}

#endif //GSLANGUAGE_GS_CONTEXT_H
