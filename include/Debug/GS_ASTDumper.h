#ifndef GSLANGUAGE_GS_ASTDUMPER_H
#define GSLANGUAGE_GS_ASTDUMPER_H

#include <AST/GS_Node.h>

#include <Debug/GS_Dumper.h>

namespace GSLanguageCompiler::Debug {

    /**
     * Class for dumping AST
     */
    class GS_ASTDumper : public GS_Dumper {
    public:

        /**
         * Constructor for AST dumper
         * @param node Node
         */
        explicit GS_ASTDumper(AST::GSNodePtr node);

    public:

        /**
         * Creating AST dumper
         * @param node Node
         * @return AST dumper ptr
         */
        static SharedPtr<GS_ASTDumper> Create(AST::GSNodePtr node);

    public:

        /**
         * Dump AST
         * @return
         */
        Void Dump() override;

    private:

        /**
         * Node
         */
        AST::GSNodePtr _node;
    };

    /**
     * Dump AST
     * @param node Node
     * @return
     */
    Void DumpAST(AST::GSNodePtr node);

}

#endif //GSLANGUAGE_GS_ASTDUMPER_H
