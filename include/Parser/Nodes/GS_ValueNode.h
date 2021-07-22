#ifndef GSLANGUAGE_GS_VALUENODE_H
#define GSLANGUAGE_GS_VALUENODE_H

#include <Parser/Nodes/GS_Node.h>

#include <Parser/Nodes/GS_Value.h>

#include <Exceptions/GS_Exception.h>

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
        GS_ValueNode(GSValuePtr value);

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
         * Codegen function
         * @return Generated code
         */
//        GSString codegen() override;

        /**
         * Getter for string node data
         * @return String node data
         */
        GSString toString() override;

    private:

        /**
         * Value
         */
        GSValuePtr _value;
    };

}

#endif //GSLANGUAGE_GS_VALUENODE_H
