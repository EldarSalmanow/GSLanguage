#ifndef GSLANGUAGE_GS_CGCONTEXT_H
#define GSLANGUAGE_GS_CGCONTEXT_H

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     * Class for containing information about code generation
     */
    class GS_CGContext {
    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_CGContext();
    };

    /**
     * Code generation context ptr type
     */
    using GSCGContextPtr = SharedPtr<GS_CGContext>;

}

#endif //GSLANGUAGE_GS_CGCONTEXT_H
