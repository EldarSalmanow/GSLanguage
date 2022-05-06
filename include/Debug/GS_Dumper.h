#ifndef GSLANGUAGE_GS_DUMPER_H
#define GSLANGUAGE_GS_DUMPER_H

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::Debug {

    /**
     * Base class for all dumpers
     */
    class GS_Dumper {
    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Dumper();

    public:

        /**
         * Dump any data
         * @return
         */
        virtual Void Dump() = 0;
    };

    /**
     * Dumper ptr
     */
    using GSDumperPtr = SharedPtr<GS_Dumper>;

}

#endif //GSLANGUAGE_GS_DUMPER_H
