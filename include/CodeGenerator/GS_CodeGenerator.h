#ifndef GSLANGUAGE_GS_CODEGENERATOR_H
#define GSLANGUAGE_GS_CODEGENERATOR_H

#include <Parser/GS_Parser.h>

#include <CodeGenerator/GS_VMImageEncoder.h>

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
        GS_CodeGenerator(Parser::GSNodePtrArray &nodes);

    public:

        /**
         *
         * @return
         */
        GS_VMImageEncoder codegen();

    private:

        /**
         *
         * @param node
         * @return
         */
        GSVoid _generateNode(Parser::GSNodePtr node);

        /**
         * @param node
         * @return
         */
        GSVoid _generateValueNode(Parser::GSNodePtr node);

        /**
         * @param node
         * @return
         */
        GSVoid _generateUnaryNode(Parser::GSNodePtr node);

        /**
         * @param node
         * @return
         */
        GSVoid _generateBinaryNode(Parser::GSNodePtr node);

        /**
         * @param node
         * @return
         */
        GSVoid _generateVariableNode(Parser::GSNodePtr node);

        /**
         *
         * @param node
         * @return
         */
        GSVoid _generatePrintNode(Parser::GSNodePtr node);

    private:

        /**
         *
         */
        Parser::GSNodePtrArray _nodes;

        /**
         *
         */
        Parser::GSNodePtrArray::iterator _nodeIterator;

        /**
         *
         */
        GS_VMImageEncoder _encoder;
    };

}

#endif //GSLANGUAGE_GS_CODEGENERATOR_H
