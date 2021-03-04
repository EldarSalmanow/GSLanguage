#ifndef GSLANGUAGE_GS_STATEMENT_H
#define GSLANGUAGE_GS_STATEMENT_H

namespace GSLanguageCompiler {

    /**
     * Base class for statements
     */
    class GS_Statement {
    public:

        /**
         *
         * @return
         */
        virtual std::string toString() = 0;
    };

    typedef std::shared_ptr<GS_Statement> GSStatementPointer;
    typedef std::vector<GSStatementPointer> GSStatementPointerArray;

}

#endif //GSLANGUAGE_GS_STATEMENT_H
