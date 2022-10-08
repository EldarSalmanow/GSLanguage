#ifndef GSLANGUAGE_GS_ASTDUMPER_H
#define GSLANGUAGE_GS_ASTDUMPER_H

#include <AST/AST.h>

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
         * @param context Context
         */
        GS_ASTDumper(AST::GSNodePtr node, LRef<Driver::GSContextPtr> context);

    public:

        /**
         * Creating AST dumper
         * @param node Node
         * @param context Context
         * @return AST dumper ptr
         */
        static std::shared_ptr<GS_ASTDumper> Create(AST::GSNodePtr node, LRef<Driver::GSContextPtr> context);

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

        /**
         * Context
         */
        LRef<Driver::GSContextPtr> _context;
    };

    /**
     * Dump AST
     * @param node Node
     * @param context Context
     * @return
     */
    Void DumpAST(AST::GSNodePtr node, LRef<Driver::GSContextPtr> context);

}

#endif //GSLANGUAGE_GS_ASTDUMPER_H
