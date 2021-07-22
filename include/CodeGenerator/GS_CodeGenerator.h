#ifndef GSLANGUAGE_GS_CODEGENERATOR_H
#define GSLANGUAGE_GS_CODEGENERATOR_H

#include <Parser/GS_Parser.h>

namespace GSLanguageCompiler::CodeGenerator {

    typedef unsigned char Byte;

    typedef std::vector<Byte> GSByteCode;

    enum class Opcode {
        PUSH,
        POP,

        ADD,
        SUB,

        TO_REG_1,
        FROM_REG_1,

        TO_REG_2,
        FROM_REG_2,

        TO_REG_3,
        FROM_REG_3,

        DONE
    };

    extern std::map<Opcode, Byte> opcodeToByte;

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
        GSByteCode codegen();

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
        GSByteCode _bytecode;
    };

    typedef std::shared_ptr<GS_CodeGenerator> GSCodeGeneratorPointer;

}

#endif //GSLANGUAGE_GS_CODEGENERATOR_H
