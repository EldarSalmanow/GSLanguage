#ifndef GSLANGUAGE_GS_VARIABLENODE_H
#define GSLANGUAGE_GS_VARIABLENODE_H

#include <Parser/Nodes/GS_Node.h>

#include <Interpreter/GS_TableOfSymbols.h>

#include <Exceptions/GS_Exception.h>

#include <CrossPlatform/GS_ClassUtilities.h>

namespace GSLanguageCompiler::Parser {

    /**
     *
     */
    class GS_VariableNode : public GS_Node {
    public:

        /**
         *
         */
        GS_VariableNode();

        /**
         *
         * @param name
         */
        explicit GS_VariableNode(GSString name);

        /**
         *
         * @param name
         * @param type
         */
        GS_VariableNode(GSString name, GSString type);

        /**
         *
         * @param name
         * @param node
         */
        GS_VariableNode(GSString name, GSNodePtr node);

        /**
         *
         * @param name
         * @param type
         * @param node
         */
        GS_VariableNode(GSString name, GSString type, GSNodePtr node);

    public:

        /**
         *
         * @return
         */
        GETTER(GSString, name, Name);

        /**
         *
         * @return
         */
        GETTER(GSString, type, Type);

        /**
         *
         * @return
         */
        GETTER(GSNodePtr, node, Node);

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
         * @return
         */
        GSString toString() override;

        /**
         *
         * @param visitor
         * @return
         */
        GSVoid accept(GS_Visitor *visitor) override;

    private:

        /**
         *
         */
        GSString _name;

        /**
         *
         */
        GSString _type;

        /**
         *
         */
        GSNodePtr _node;
    };

}

#endif //GSLANGUAGE_GS_VARIABLENODE_H
