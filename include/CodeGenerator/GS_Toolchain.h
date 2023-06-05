#ifndef GSLANGUAGE_GS_TOOLCHAIN_H
#define GSLANGUAGE_GS_TOOLCHAIN_H

#include <vector>

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::CodeGenerator {

    class GS_Linker {
    public:

        virtual ~GS_Linker();

    public:

        virtual Void Link(std::vector<UString> input,
                          UString output) = 0;
    };

    using GSLinkerPtr = std::shared_ptr<GS_Linker>;

    class GS_LLDLinker : public GS_Linker {
    public:

        GS_LLDLinker();

    public:

        static std::shared_ptr<GS_LLDLinker> Create();

    public:

        Void Link(std::vector<UString> input,
                  UString output) override;
    };

    class GS_Toolchain {
    public:

        explicit GS_Toolchain(GSLinkerPtr linker);

    public:

        static std::unique_ptr<GS_Toolchain> Create(GSLinkerPtr linker);

        static std::unique_ptr<GS_Toolchain> Create();

    public:

        GSLinkerPtr GetLinker();

    private:

        GSLinkerPtr _linker;
    };

    using GSToolchainPtr = std::unique_ptr<GS_Toolchain>;

}

#endif //GSLANGUAGE_GS_TOOLCHAIN_H
