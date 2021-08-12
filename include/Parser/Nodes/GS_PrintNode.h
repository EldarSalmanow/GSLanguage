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
         * @param builder
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
        GSValuePtr _value;
    };

}

#endif //GSLANGUAGE_GS_PRINTNODE_H
