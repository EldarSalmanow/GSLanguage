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
         *
         * @return
         */
        GSVoid _generateValueNode();

        /**
         *
         * @return
         */
        GSVoid _generateUnaryNode();

        /**
         *
         * @return
         */
        GSVoid _generateBinaryNode();

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
        GS_VMImageEncoder _vmImage;
    };

}

#endif //GSLANGUAGE_GS_CODEGENERATOR_H
