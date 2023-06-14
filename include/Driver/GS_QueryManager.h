#ifndef GSLANGUAGE_GS_QUERYMANAGER_H
#define GSLANGUAGE_GS_QUERYMANAGER_H

//#include <GSCrossPlatform/CrossPlatform.h>

#include <Lexer/Lexer.h>

#include <AST/AST.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Defining session for query manager
     */
    class GS_Session;

    /**
     * Class for providing set of operations with data in session
     */
    class GS_QueryManager {
    public:

        /**
         * Constructor for query manager
         */
        GS_QueryManager();

    public:

        /**
         * Creating query manager
         * @return Query manager ptr
         */
        static std::unique_ptr<GS_QueryManager> Create();

    public:

        /*
         * Defining queries
         */

        #include <Driver/GS_Queries.def>
    };

    /**
     * Query manager ptr type
     */
    using GSQueryManagerPtr = std::unique_ptr<GS_QueryManager>;

}

#endif //GSLANGUAGE_GS_QUERYMANAGER_H
