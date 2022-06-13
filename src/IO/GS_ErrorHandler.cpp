#include <rang.hpp>

#include <GS_ErrorHandler.h>

namespace GSLanguageCompiler::IO {

    GS_ErrorHandler::GS_ErrorHandler() = default;

    std::shared_ptr<GS_ErrorHandler> GS_ErrorHandler::Create() {
        return std::make_shared<GS_ErrorHandler>();
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

    Void GS_ErrorHandler::Note(UString note, IO::GSOutStreamPtr stream) {
        Print("Note: "_us + note, std::move(stream), rang::style::bold, rang::fg::blue);
    }

    Void GS_ErrorHandler::Warning(UString warning, IO::GSOutStreamPtr stream) {
        Print("Warning: "_us + warning, std::move(stream), rang::style::bold, rang::fg::yellow);
    }

    Void GS_ErrorHandler::Error(UString error, IO::GSOutStreamPtr stream) {
        Print("Error: "_us + error, std::move(stream), rang::style::bold, rang::fg::red);
    }

    Void GS_ErrorHandler::StdNote(UString note) {
        Note(std::move(note), IO::GS_OutConsoleStream::CreateCErr());
    }

    Void GS_ErrorHandler::StdWarning(UString warning) {
        Warning(std::move(warning), IO::GS_OutConsoleStream::CreateCErr());
    }

    Void GS_ErrorHandler::StdError(UString error) {
        Error(std::move(error), IO::GS_OutConsoleStream::CreateCErr());
    }

}
