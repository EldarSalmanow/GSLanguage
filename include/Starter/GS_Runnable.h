#ifndef GSLANGUAGE_GS_RUNNABLE_H
#define GSLANGUAGE_GS_RUNNABLE_H

#include <Starter/GS_Context.h>

namespace GSLanguageCompiler::Starter {

    /**
     * Interface for compiler passes
     */
    class GS_Runnable {
    public:

        /**
         * Virtual destructor for support safe inheritance
         */
        virtual ~GS_Runnable();

    public:

        /**
         * Method for running compiler pass
         * @param context Compiler context
         * @return
         */
        virtual GSVoid run(GSContextPtr &context) = 0;
    };

    typedef std::shared_ptr<GS_Runnable> GSRunnablePtr;

}

#endif //GSLANGUAGE_GS_RUNNABLE_H
