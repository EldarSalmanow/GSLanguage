#ifndef GSLANGUAGE_GS_INTERPRETER_H
#define GSLANGUAGE_GS_INTERPRETER_H

#include <Parser/GS_Parser.h>

namespace GSLanguageCompiler::Interpreter {

    /**
     *
     */
    class GS_Interpreter {
    public:

        /**
         *
         * @param nodes
         */
        explicit GS_Interpreter(Parser::GSNodePtrArray nodes);

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
        Parser::GSNodePtrArray _nodes;
    };

}

#endif //GSLANGUAGE_GS_INTERPRETER_H
