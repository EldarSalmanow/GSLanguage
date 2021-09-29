#ifndef GSLANGUAGE_GS_VARIABLEDECLARATIONNODE_H
#define GSLANGUAGE_GS_VARIABLEDECLARATIONNODE_H

#include <Parser/Nodes/GS_ValueNode.h>

namespace GSLanguageCompiler::Parser {

    /**
     * AST node for variable declaration
     */
    class GS_VariableDeclarationNode : public GS_Node {
    public:

        /**
         * Constructor for variable declaration node
         * @param name Variable name
         */
        explicit GS_VariableDeclarationNode(GSString name);

        /**
         * Constructor for variable declaration node
         * @param name Variable name
         * @param type Variable type
         */
        GS_VariableDeclarationNode(GSString name, ValueType type);

    public:

        /**
         * Getter for variable name
         * @return Variable name
         */
        GSString getName();

        /**
         * Getter for variable type
         * @return Variable type
         */
        ValueType getType();

        /**
         * Setter for variable type
         * @param type Variable type
         * @return
         */
        GSVoid setType(ValueType type);

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

        /**
         * Variable type
         */
        ValueType _type;
    };

}

#endif //GSLANGUAGE_GS_VARIABLEDECLARATIONNODE_H
