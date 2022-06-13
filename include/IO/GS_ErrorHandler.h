#ifndef GSLANGUAGE_GS_ERROR_H
#define GSLANGUAGE_GS_ERROR_H

#include <IO/GS_Stream.h>

//#include <IO/GS_SourceManager.h>

namespace GSLanguageCompiler::IO {

    // TODO create

    class GS_ErrorHandler {
    public:

        GS_ErrorHandler();

    public:

        static std::shared_ptr<GS_ErrorHandler> Create();

    public:

        Void Note(UString note, IO::GSOutStreamPtr stream);

        Void Warning(UString warning, IO::GSOutStreamPtr stream);

        Void Error(UString error, IO::GSOutStreamPtr stream);

        Void StdNote(UString note);

        Void StdWarning(UString warning);

        Void StdError(UString error);
    };

    using GSErrorHandlerPtr = std::shared_ptr<GS_ErrorHandler>;

}

#endif //GSLANGUAGE_GS_ERROR_H
