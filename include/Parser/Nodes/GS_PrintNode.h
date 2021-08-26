#ifndef GSLANGUAGE_GS_PRINTNODE_H
#define GSLANGUAGE_GS_PRINTNODE_H

#include <iostream>

#include <Parser/Nodes/GS_StringValue.h>

#include <Parser/Nodes/GS_Node.h>

#include <Exceptions/GS_Exception.h>

namespace GSLanguageCompiler::Parser {

    /**
     *
     */
    class GS_PrintNode : public GS_Node {
    public:

        /**
         *
         * @param value
         */
        explicit GS_PrintNode(GSValuePtr value);

    public:

        GETTER(GSValuePtr, value, Value)

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
        GSValuePtr _value;
    };

}

#endif //GSLANGUAGE_GS_PRINTNODE_H
