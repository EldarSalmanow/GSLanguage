#ifndef GSLANGUAGE_GS_ERROR_H
#define GSLANGUAGE_GS_ERROR_H

#include <Lexer/GS_Token.h>

#include <IO/GS_Stream.h>

namespace GSLanguageCompiler::IO {

    class GS_MessageHandler {
    public:

        explicit GS_MessageHandler(IO::GSSourceManagerPtr sourceManager);

    public:

        static std::shared_ptr<GS_MessageHandler> Create(IO::GSSourceManagerPtr sourceManager);

        static std::shared_ptr<GS_MessageHandler> Create();

    public:

        Void Note(UString note, IO::GSOutStreamPtr stream);

        Void Warning(UString warning, IO::GSOutStreamPtr stream);

        Void Error(UString error, IO::GSOutStreamPtr stream);

        Void StdNote(UString note);

        Void StdWarning(UString warning);

        Void StdError(UString error);

        Void Note(UString note, Lexer::GS_TokenLocation tokenLocation, IO::GSOutStreamPtr stream);

        Void Warning(UString warning, Lexer::GS_TokenLocation tokenLocation, IO::GSOutStreamPtr stream);

        Void Error(UString error, Lexer::GS_TokenLocation tokenLocation, IO::GSOutStreamPtr stream);

        Void StdNote(UString note, Lexer::GS_TokenLocation tokenLocation);

        Void StdWarning(UString warning, Lexer::GS_TokenLocation tokenLocation);

        Void StdError(UString error, Lexer::GS_TokenLocation tokenLocation);

    private:

        IO::GSSourceManagerPtr _sourceManager;
    };

    using GSErrorHandlerPtr = std::shared_ptr<GS_MessageHandler>;

}

#endif //GSLANGUAGE_GS_ERROR_H
