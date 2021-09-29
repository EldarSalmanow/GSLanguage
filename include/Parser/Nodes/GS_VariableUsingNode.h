#ifndef GSLANGUAGE_GS_VARIABLEUSINGNODE_H
#define GSLANGUAGE_GS_VARIABLEUSINGNODE_H

#include <Parser/Nodes/GS_Node.h>

namespace GSLanguageCompiler::Parser {

    /**
     * Class for variable using AST node
     */
    class GS_VariableUsingNode : public GS_Node {
    public:

        /**
         * Constructor for variable using node
         * @param name Variable name
         */
        explicit GS_VariableUsingNode(GSString name);

    public:

        /**
         * Getter for variable name
         * @return Variable name
         */
        GSString getName();

    public:

        /**
         * Getter for node type
         * @return Node type
         */
        NodeType getNodeType() override;

        /**
         * Acceptor for code generation visitors
         * @param visitor Codegen visitor
         * @return LLVM IR instructions
         */
        llvm::Value *accept(GS_Visitor<llvm::Value*> *visitor) override;

        /**
         * Acceptor for semantic visitors
         * @param visitor Semantic visitor
         * @return
         */
        GSVoid accept(GS_Visitor<GSVoid> *visitor) override;

        /**
         * Acceptor for optimizer visitors
         * @param visitor Optimizing visitor
         * @return Optimized node
         */
        GSNodePtr accept(GS_Visitor<GSNodePtr> *visitor) override;

    private:

        /**
         * Variable name
         */
        GSString _name;
    };

}

#endif //GSLANGUAGE_GS_VARIABLEUSINGNODE_H
