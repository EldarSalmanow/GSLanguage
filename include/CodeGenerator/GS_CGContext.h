#ifndef GSLANGUAGE_GS_CGCONTEXT_H
#define GSLANGUAGE_GS_CGCONTEXT_H

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     * Code generation backend
     */
    enum class CGBackend {
        LLVM
    };

    /**
     * Class for containing information about code generation
     */
    class GS_CGContext {
    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_CGContext();

    public:

        /**
         * Getter for code generation backend
         * @return Code generation backend
         */
        virtual CGBackend GetBackend() = 0;
    };

    /**
     * Code generation context ptr type
     */
    using GSCGContextPtr = SharedPtr<GS_CGContext>;

}

#endif //GSLANGUAGE_GS_CGCONTEXT_H
