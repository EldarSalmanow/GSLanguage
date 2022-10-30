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
         * @param session Session
         */
        GS_ASTDumper(AST::GSNodePtr node, LRef<Driver::GS_Session> session);

    public:

        /**
         * Creating AST dumper
         * @param node Node
         * @param session Session
         * @return AST dumper ptr
         */
        static std::shared_ptr<GS_ASTDumper> Create(AST::GSNodePtr node, LRef<Driver::GS_Session> session);

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
         * Session
         */
        LRef<Driver::GS_Session> _session;
    };

    /**
     * Dump AST
     * @param node Node
     * @param session Session
     * @return
     */
    Void DumpAST(AST::GSNodePtr node, LRef<Driver::GS_Session> session);

}

#endif //GSLANGUAGE_GS_ASTDUMPER_H
