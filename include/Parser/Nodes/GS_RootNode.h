#ifndef GSLANGUAGE_GS_ROOTNODE_H
#define GSLANGUAGE_GS_ROOTNODE_H

#include <Parser/Nodes/GS_Node.h>

namespace GSLanguageCompiler::Parser {

    /**
     *
     */
    class GS_RootNode : public GS_Node {
    public:

        /**
         *
         * @param node
         */
        explicit GS_RootNode(GSNodePtr node)
                : _node(std::move(node)) {}

    public:

        /**
         *
         * @return
         */
        GSNodePtr getNode() {
            return _node;
        }

    public:

        NodeType getNodeType() override {
            return NodeType::ROOT_NODE;
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
        GSNodePtr _node;
    };

}

#endif //GSLANGUAGE_GS_ROOTNODE_H
