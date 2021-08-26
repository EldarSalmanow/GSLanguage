#ifndef GSLANGUAGE_GS_INTERPRETER_H
#define GSLANGUAGE_GS_INTERPRETER_H

#include <Parser/GS_Parser.h>

namespace GSLanguageCompiler::Interpreter {

    // todo remove interpreter from project

    /**
     *
     */
    class GS_Interpreter {
    public:

        /**
         *
         * @param nodes
         */
        explicit GS_Interpreter(Parser::GSNodePtr nodes);

    public:

        /**
         *
         * @return
         */
        GSVoid startInterpret();

    private:

        /**
         *
         */
        Parser::GSNodePtr _nodes;
    };

}

#endif //GSLANGUAGE_GS_INTERPRETER_H
