#ifndef GSLANGUAGE_GS_PRINTNODE_H
#define GSLANGUAGE_GS_PRINTNODE_H

#include <Parser/Nodes/GS_StringValue.h>

#include <Parser/Nodes/GS_Node.h>

namespace GSLanguageCompiler::Parser {

    /**
     *
     */
    class GS_PrintNode : public GS_Node {
    public:

        /**
         *
         * @param stringValue
         */
        GS_PrintNode(GS_StringValue &stringValue);

    public:

        GETTER(GS_StringValue, string, String)

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
        GSString toString() override;

    private:

        /**
         *
         */
        GS_StringValue _string;
    };

}

#endif //GSLANGUAGE_GS_PRINTNODE_H
