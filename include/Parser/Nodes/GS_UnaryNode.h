#ifndef GSLANGUAGE_GS_UNARYNODE_H
#define GSLANGUAGE_GS_UNARYNODE_H

#include <map>

#include <Parser/Nodes/GS_Node.h>

namespace GSLanguageCompiler::Parser {

    /**
     *
     */
    enum class UnaryOperation {
        MINUS
    };

    /**
     *
     */
    extern std::map<UnaryOperation, GSString> unaryOperationToString;

    /**
     *
     */
    class GS_UnaryNode : public GS_Node {
    public:

        /**
         *
         * @param operation
         * @param node
         */
        GS_UnaryNode(UnaryOperation operation, GSNodePtr node);

    public:

        /**
         *
         * @return
         */
        UnaryOperation getUnaryOperation();

        /**
         *
         * @return
         */
        GSNodePtr getNode();

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
        UnaryOperation _operation;

        /**
         *
         */
        GSNodePtr _node;
    };

}

#endif //GSLANGUAGE_GS_UNARYNODE_H
