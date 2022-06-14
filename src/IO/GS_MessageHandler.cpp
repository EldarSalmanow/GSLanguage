#include <GSCrossPlatform/Defines.h>

#if defined(GS_OS_WINDOWS)

    /**
     * Can`t include in rang.hpp io.h standard header because preprocessor include IO.h project header.
     * Including low-level I/O functions manually from corecrt_io.h
     */
    #include <corecrt_io.h>

#endif

#include <rang.hpp>

#include <GS_MessageHandler.h>

namespace GSLanguageCompiler::IO {

    GS_MessageHandler::GS_MessageHandler(IO::GSSourceManagerPtr sourceManager)
            : _sourceManager(std::move(sourceManager)) {}

    std::shared_ptr<GS_MessageHandler> GS_MessageHandler::Create(IO::GSSourceManagerPtr sourceManager) {
        return std::make_shared<GS_MessageHandler>(std::move(sourceManager));
    }

    std::shared_ptr<GS_MessageHandler> GS_MessageHandler::Create() {
        return GS_MessageHandler::Create(IO::GS_SourceManager::Create());
    }

    Void Print(UString message, IO::GSOutStreamPtr stream, rang::style style, rang::fg color) {
        auto BeginPrintLine = [style] (LRef<IO::GSOutStreamPtr> stream) {
            stream->GetOutStream() << rang::style::reset << rang::fg::reset << style << "|> "_us;
        };

        auto EndPrintLine = [] (LRef<IO::GSOutStreamPtr> stream) {
            stream->GetOutStream() << rang::style::reset << rang::fg::reset << std::endl;
        };

        BeginPrintLine(stream);

        stream->GetOutStream() << color << message;

        EndPrintLine(stream);

        BeginPrintLine(stream);

        EndPrintLine(stream);
    }

    Void GS_MessageHandler::Note(UString note, IO::GSOutStreamPtr stream) {
        Print("Note: "_us + note, std::move(stream), rang::style::bold, rang::fg::blue);
    }

    Void GS_MessageHandler::Warning(UString warning, IO::GSOutStreamPtr stream) {
        Print("Warning: "_us + warning, std::move(stream), rang::style::bold, rang::fg::yellow);
    }

    Void GS_MessageHandler::Error(UString error, IO::GSOutStreamPtr stream) {
        Print("Error: "_us + error, std::move(stream), rang::style::bold, rang::fg::red);
    }

    Void GS_MessageHandler::StdNote(UString note) {
        Note(std::move(note), IO::GS_OutConsoleStream::CreateCErr());
    }

    Void GS_MessageHandler::StdWarning(UString warning) {
        Warning(std::move(warning), IO::GS_OutConsoleStream::CreateCErr());
    }

    Void GS_MessageHandler::StdError(UString error) {
        Error(std::move(error), IO::GS_OutConsoleStream::CreateCErr());
    }

    Void Print(UString message, Lexer::GS_TokenLocation tokenLocation, IO::GSOutStreamPtr stream, rang::style style, rang::fg color, IO::GSSourceManagerPtr sourceManager) {
        auto BeginPrintLine = [style] (LRef<IO::GSOutStreamPtr> stream) {
            stream->GetOutStream() << rang::style::reset << rang::fg::reset << style << "|> "_us;
        };

        auto EndPrintLine = [] (LRef<IO::GSOutStreamPtr> stream) {
            stream->GetOutStream() << rang::style::reset << rang::fg::reset << std::endl;
        };

        auto startSymbolLocation = tokenLocation.GetStartLocation();
        auto endSymbolLocation = tokenLocation.GetEndLocation();

        BeginPrintLine(stream);

        auto file = sourceManager->FindFile(startSymbolLocation.GetSourceName());

        auto code = file->FindLine(startSymbolLocation.GetLine());

        stream->GetOutStream() << color << startSymbolLocation.GetSourceName() << " " << startSymbolLocation.GetLine() << ": >> " << code;

        EndPrintLine(stream);

        BeginPrintLine(stream);

        stream->GetOutStream() << color;

        auto aligning = startSymbolLocation.GetSourceName().Size() + std::to_string(startSymbolLocation.GetLine()).size() + 6;

        for (U64 i = 1; i < startSymbolLocation.GetColumn() + aligning; ++i) {
            stream->GetOutStream() << " ";
        }

        for (U64 i = startSymbolLocation.GetColumn() + aligning; i <= endSymbolLocation.GetColumn() + aligning; ++i) {
            stream->GetOutStream() << "^";
        }

        EndPrintLine(stream);

        BeginPrintLine(stream);

        stream->GetOutStream() << color << message;

        EndPrintLine(stream);

        BeginPrintLine(stream);

        EndPrintLine(stream);
    }

    Void GS_MessageHandler::Note(UString note, Lexer::GS_TokenLocation tokenLocation, IO::GSOutStreamPtr stream) {
        Print("Note: "_us + note, std::move(tokenLocation), std::move(stream), rang::style::bold, rang::fg::blue, _sourceManager);
    }

    Void GS_MessageHandler::Warning(UString warning, Lexer::GS_TokenLocation tokenLocation, IO::GSOutStreamPtr stream) {
        Print("Warning: "_us + warning, std::move(tokenLocation), std::move(stream), rang::style::bold, rang::fg::yellow, _sourceManager);
    }

    Void GS_MessageHandler::Error(UString error, Lexer::GS_TokenLocation tokenLocation, IO::GSOutStreamPtr stream) {
        Print("Error: "_us + error, std::move(tokenLocation), std::move(stream), rang::style::bold, rang::fg::red, _sourceManager);
    }

    Void GS_MessageHandler::StdNote(UString note, Lexer::GS_TokenLocation tokenLocation) {
        Note(std::move(note), std::move(tokenLocation), _sourceManager->GetConsoleErr());
    }

    Void GS_MessageHandler::StdWarning(UString warning, Lexer::GS_TokenLocation tokenLocation) {
        Warning(std::move(warning), std::move(tokenLocation), _sourceManager->GetConsoleErr());
    }

    Void GS_MessageHandler::StdError(UString error, Lexer::GS_TokenLocation tokenLocation) {
        Error(std::move(error), std::move(tokenLocation), _sourceManager->GetConsoleErr());
    }

}
