#ifndef GSLANGUAGE_GS_BLOCKNODE_H
#define GSLANGUAGE_GS_BLOCKNODE_H

#include <Parser/Nodes/GS_Node.h>

namespace GSLanguageCompiler::Parser {

    /**
     *
     */
    class GS_BlockNode : public GS_Node {
    public:

        /**
         *
         * @param nodes
         */
        explicit GS_BlockNode(GSNodePtrArray nodes)
                : _nodes(std::move(nodes)) {}

    public:

        /**
         *
         * @return
         */
        GSNodePtrArray getNodes() {
            return _nodes;
        }

    public:

        NodeType getNodeType() override {
            return NodeType::BLOCK_NODE;
        }

        GSVoid accept(GS_Visitor *visitor) override {
            visitor->visit(this);
        }

        GSNodePtr accept(Optimizer::GS_OptimizerPass *pass) override {
            return pass->visit(this);
        }

        GSValuePtr interpret() override {

        }

    private:

        /**
         *
         */
        GSNodePtrArray _nodes;
    };

}

#endif //GSLANGUAGE_GS_BLOCKNODE_H
