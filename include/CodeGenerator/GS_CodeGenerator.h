#ifndef GSLANGUAGE_GS_CODEGENERATOR_H
#define GSLANGUAGE_GS_CODEGENERATOR_H

#include <Parser/GS_Parser.h>

#include <CodeGenerator/GS_CodeGenVisitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     *
     */
    class GS_CodeGenerator {
    public:

        /**
         *
         * @param nodes
         */
        explicit GS_CodeGenerator(Parser::GSNodePtr nodes);

    public:

        /**
         *
         * @return
         */
        GSByteCode codegen();

    private:

        /**
         *
         */
        Parser::GSNodePtr _nodes;
    };

}

#endif //GSLANGUAGE_GS_CODEGENERATOR_H
