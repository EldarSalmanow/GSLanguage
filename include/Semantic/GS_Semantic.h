#ifndef GSLANGUAGE_GS_SEMANTIC_H
#define GSLANGUAGE_GS_SEMANTIC_H

#include <Starter/GS_Runnable.h>

#include <Semantic/GS_TypePlaceholderPass.h>
#include <Semantic/GS_TypeCheckerPass.h>
#include <Semantic/GS_VariablesPlaceholderPass.h>

#include <Semantic/GS_TableOfVariables.h>

namespace GSLanguageCompiler::Semantic {

    /**
     * Class for semantic analyzing
     */
    class GS_Semantic : public Starter::GS_Runnable {
    public:

        /**
         * Constructor for semantic analyzer
         */
        GS_Semantic();

    public:

        /**
         *
         * @param context
         * @return
         */
        GSVoid run(Starter::GSContextPtr &context) override;
    };

}

#endif //GSLANGUAGE_GS_SEMANTIC_H
