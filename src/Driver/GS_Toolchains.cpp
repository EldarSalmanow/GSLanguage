#include <lld/Common/Driver.h>

#include <Driver/GS_Toolchains.h>

//class raw_unicode_ostream : public llvm::raw_ostream {
//public:
//
//    explicit raw_unicode_ostream(LRef<UString> string)
//            : _buffer(string) {}
//
//public:
//
//    bool is_displayed() const override {
//        return false;
//    }
//
//    bool has_colors() const override {
//        return false;
//    }
//
//private:
//
//    void write_impl(const char *Ptr, size_t Size) override {
//        UString string(Ptr);
//
//        _buffer += string;
//    }
//
//    uint64_t current_pos() const override {
//        return _buffer.Size();
//    }
//
//private:
//
//    LRef<UString> _buffer;
//};

namespace GSLanguageCompiler::Driver {

    /**
     *
     */
    class GS_MSVCLinker : public GS_Linker {
    public:

        /**
         *
         * @param units
         * @param librariesPaths
         * @param outputName
         * @return
         */
        Bool Link(Vector<GSTranslationUnitPtr> units, Vector<UString> librariesPaths, UString outputName) override {
            Vector<ConstPtr<C8>> command;

            for (auto &unit : units) {
                command.emplace_back((unit->GetConfig()->GetInputName().AsString() + ".o").c_str());
            }

            command.emplace_back("/entry:main");

            command.emplace_back(("/out:\"" + outputName.AsString() + "\"").c_str());

//            for (auto &path : librariesPaths) {
//                command.emplace_back(("/libpath:\"" + path.AsString() + "\"").c_str());
//            }

//            UString outString, errString;
//
//            raw_unicode_ostream outStream(outString), errStream(errString);

//            auto result = lld::coff::link(command, outStream, errStream, false, false);
            auto result = lld::coff::link(command, llvm::outs(), llvm::errs(), false, false);

//            COut() << outString << U"\n"_us << errString << U"\n"_us;

            return result;
        }
    };

    SharedPtr<GS_Linker> GS_MSVCToolchain::GetLinker() {
        return std::make_shared<GS_MSVCLinker>();
    }

}
