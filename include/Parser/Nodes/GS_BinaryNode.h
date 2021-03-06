#ifndef GSLANGUAGE_GS_BINARYNODE_H
#define GSLANGUAGE_GS_BINARYNODE_H

#include <map>

#include <Parser/Nodes/GS_Node.h>

namespace GSLanguageCompiler::Parser {

    /**
     *
     */
    enum class BinaryOperation {
        PLUS,
        MINUS,
        STAR,
        SLASH
    };

    /**
     *
     */
    extern std::map<BinaryOperation, GSString> binaryOperationToString;

    /**
     *
     */
    class GS_BinaryNode : public GS_Node {
    public:

        /**
         *
         * @param operation
         * @param firstNode
         * @param secondNode
         */
        GS_BinaryNode(BinaryOperation operation, GSNodePtr firstNode, GSNodePtr secondNode);

    public:

        /**
         *
         * @return
         */
        BinaryOperation getBinaryOperation();

        /**
         *
         * @return
         */
        GSNodePtr getFirstNode();

        /**
         *
         * @return
         */
        GSNodePtr getSecondNode();

    public:

        /**
         *
         * @return
         */
        NodeType getNodeType() override;

        /**
         *
         * @return
         */
//        GSString codegen() override;

        /**
         *
         * @return
         */
        GSString toString() override;

    private:

        /**
         *
         */
        BinaryOperation _operation;

        /**
         *
         */
        GSNodePtr _firstNode, _secondNode;
    };

}

#endif //GSLANGUAGE_GS_BINARYNODE_H
