#ifndef GSLANGUAGE_GS_BINARYNODE_H
#define GSLANGUAGE_GS_BINARYNODE_H

#include <map>

#include <Parser/Nodes/GS_Node.h>

#include <Parser/Nodes/GS_IntegerValue.h>

#include <Exceptions/GS_ErrorHandler.h>

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
        GSValuePtr interpret() override;

        /**
         *
         * @param visitor
         * @return
         */
        GSVoid accept(GS_Visitor *visitor) override;

        GSNodePtr accept(Optimizer::GS_OptimizerPass *pass) override {
            return pass->visit(this);
        }

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
