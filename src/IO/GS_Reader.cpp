#include <GS_TextStream.h>

#include <GS_Reader.h>

namespace GSLanguageCompiler::IO {

    GS_Reader::GS_Reader(LRef<UniquePtr<File>> file)
            : _file(std::move(file)) {}

    GS_Reader GS_Reader::Create(LRef<UniquePtr<File>> file) {
        return GS_Reader(file);
    }

    GS_Reader GS_Reader::Create(UString name) {
        auto file = File::Create(name, InMode);

        return GS_Reader::Create(file);
    }

    UString GS_Reader::ReadText() {
        return _file->ReadInput();
    }

    GS_TextStream GS_Reader::CreateStream() {
        return GS_TextStream::Create(*this);
    }

}