#include <Reader/GS_Reader.h>

namespace GSLanguageCompiler::Reader {

    GS_Reader::GS_Reader(LRef<UniquePtr<File>> file)
            : _file(std::move(file)) {}

    UString GS_Reader::ReadText() {
        return _file->ReadInput();
    }

}