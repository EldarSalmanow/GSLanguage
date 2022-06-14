#ifndef GSLANGUAGE_GS_SOURCEMANAGER_H
#define GSLANGUAGE_GS_SOURCEMANAGER_H

#include <vector>

#include <IO/GS_Stream.h>

namespace GSLanguageCompiler::IO {

    // TODO update

    class GS_File {
    public:

        explicit GS_File(GSStreamPtr stream)
                : _stream(std::move(stream)) {}

    public:

        static std::shared_ptr<GS_File> Create(GSStreamPtr stream) {
            return std::make_shared<GS_File>(std::move(stream));
        }

    public:

        UString FindLine(U64 line) const {
            return _code[line - 1];
        }

    public:

        GSStreamPtr GetStream() const {
            return _stream;
        }

        GSStreamInfoPtr GetStreamInfo() const {
            return _stream->GetStreamInfo();
        }

        UString GetName() const {
            return GetStreamInfo()->GetFileName();
        }

        Void SetCode(std::vector<UString> code) {
            _code = std::move(code);
        }

    private:

        GSStreamPtr _stream;

        std::vector<UString> _code;
    };

    using GSFilePtr = std::shared_ptr<GS_File>;

    using GSFilePtrArray = std::vector<GSFilePtr>;

    class GS_SourceManager {
    public:

        explicit GS_SourceManager(GSFilePtrArray files)
                : _files(std::move(files)),
                  _consoleIn(IO::GS_InConsoleStream::CreateCIn()),
                  _consoleOut(IO::GS_OutConsoleStream::CreateCOut()),
                  _consoleErr(IO::GS_OutConsoleStream::CreateCErr()),
                  _consoleLog(IO::GS_OutConsoleStream::CreateCLog()) {}

    public:

        static std::shared_ptr<GS_SourceManager> Create(GSFilePtrArray files) {
            return std::make_shared<GS_SourceManager>(std::move(files));
        }

        static std::shared_ptr<GS_SourceManager> Create() {
            return GS_SourceManager::Create(GSFilePtrArray());
        }

    public:

        GSFilePtr CreateInFile(UString name) {
            auto stream = GS_InFileStream::CreateInFile(std::move(name));

            auto file = GS_File::Create(stream);

            AddFile(file);

            return file;
        }

        GSFilePtr CreateOutFile(UString name) {
            auto stream = GS_OutFileStream::CreateOutFile(std::move(name));

            auto file = GS_File::Create(stream);

            AddFile(file);

            return file;
        }

        Void AddFile(GSFilePtr file) {
            _files.emplace_back(std::move(file));
        }

        GSFilePtr FindFile(UString name) {
            for (auto &file : _files) {
                if (file->GetName() == name) {
                    return file;
                }
            }

            return nullptr;
        }

    public:

        IO::GSInStreamPtr GetConsoleIn() const {
            return _consoleIn;
        }

        IO::GSOutStreamPtr GetConsoleOut() const {
            return _consoleOut;
        }

        IO::GSOutStreamPtr GetConsoleErr() const {
            return _consoleErr;
        }

        IO::GSOutStreamPtr GetConsoleLog() const {
            return _consoleLog;
        }

    private:

        GSFilePtrArray _files;

        IO::GSInStreamPtr _consoleIn;

        IO::GSOutStreamPtr _consoleOut;

        IO::GSOutStreamPtr _consoleErr;

        IO::GSOutStreamPtr _consoleLog;

    };

    using GSSourceManagerPtr = std::shared_ptr<GS_SourceManager>;

}

#endif //GSLANGUAGE_GS_SOURCEMANAGER_H
