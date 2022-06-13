#ifndef GSLANGUAGE_GS_SOURCEMANAGER_H
#define GSLANGUAGE_GS_SOURCEMANAGER_H

#include <vector>

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::IO {

    // TODO create

    class GS_Source {
    public:

        virtual ~GS_Source() = default;
    };

    using GSSourcePtr = std::shared_ptr<GS_Source>;

    using GSSourcePtrArray = std::vector<GSSourcePtr>;

    class GS_File : public GS_Source {
    public:

        UString _name;

        std::vector<UString> _code;
    };

    class GS_SourceManager {
    public:

        explicit GS_SourceManager(GSSourcePtrArray sources)
                : _sources(std::move(sources)) {}

    public:

        static std::shared_ptr<GS_SourceManager> Create(GSSourcePtrArray sources) {
            return std::make_shared<GS_SourceManager>(std::move(sources));
        }

        static std::shared_ptr<GS_SourceManager> Create() {
            return GS_SourceManager::Create(GSSourcePtrArray());
        }

    public:



    private:

        GSSourcePtrArray _sources;
    };

}

#endif //GSLANGUAGE_GS_SOURCEMANAGER_H
