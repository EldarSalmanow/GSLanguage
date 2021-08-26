#ifndef GSLANGUAGE_GS_VALUENODE_H
#define GSLANGUAGE_GS_VALUENODE_H

#include <Parser/Nodes/GS_Node.h>

#include <Exceptions/GS_ErrorHandler.h>

namespace GSLanguageCompiler::Parser {

    /**
     * Node for containing values
     */
    class GS_ValueNode : public GS_Node {
    public:

        /**
         * Constructor for value node
         * @param value Value ptr
         */
        explicit GS_ValueNode(GSValuePtr value);

    public:

        /**
         * Getter for value ptr
         * @return Value ptr
         */
        GSValuePtr getValue();

    public:

        /**
         * Getter for node type
         * @return Node type
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
         * Value
         */
        GSValuePtr _value;
    };

}

#endif //GSLANGUAGE_GS_VALUENODE_H
