#ifndef GSLANGUAGE_GS_STATEMENT_H
#define GSLANGUAGE_GS_STATEMENT_H

#include <string>
#include <memory>
#include <vector>

#include <Parser/Statements/GS_StatementTypes.h>

namespace GSLanguageCompiler::Parser {

    /**
     * Base class for statements
     */
    class GS_Statement {
    public:

        /**
         *
         */
        virtual ~GS_Statement() = default;

    public:

        /**
         *
         * @return
         */
        virtual StatementType getStatementType() = 0;

        /**
         *
         * @return
         */
        virtual std::string generateCode() = 0;

        /**
         *
         * @return
         */
        virtual std::string toStringForDebug() = 0;
    };

    typedef std::shared_ptr<GS_Statement> GSStatementPointer;
    typedef std::vector<GSStatementPointer> GSStatementPointerArray;

}

#endif //GSLANGUAGE_GS_STATEMENT_H
