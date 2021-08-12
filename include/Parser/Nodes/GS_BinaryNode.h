#ifndef GSLANGUAGE_GS_BINARYNODE_H
#define GSLANGUAGE_GS_BINARYNODE_H

#include <map>

#include <Parser/Nodes/GS_Node.h>

#include <Parser/Nodes/GS_IntegerValue.h>

#include <Exceptions/GS_Exception.h>

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
        GSVoid codegen(CodeGenerator::GS_BCBuilder &builder) override;

        /**
         *
         * @return
         */
        GSValuePtr interpret() override;

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
