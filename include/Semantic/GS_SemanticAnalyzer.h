#ifndef GSLANGUAGE_GS_SEMANTICANALYZER_H
#define GSLANGUAGE_GS_SEMANTICANALYZER_H

#include <Semantic/Passes/SemanticPasses.h>

namespace GSLanguageCompiler::Semantic {

    /**
     * Class for semantic analyzing AST
     */
    class GS_SemanticAnalyzer {
    public:

        /*
         *
         * GS_SemanticAnalyzer PUBLiC CONSTRUCTORS
         *
         */

        /**
         * Constructor for semantic analyzer
         * @param session Session
         * @param semanticPasses Semantic passes
         */
        GS_SemanticAnalyzer(LRef<Driver::GS_Session> session,
                            AST::GSPassPtrArray semanticPasses);

    public:

        /*
         *
         * GS_SemanticAnalyzer PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating semantic analyzer
         * @param session Session
         * @param optimizingPasses Semantic passes
         * @return Semantic ptr
         */
        static std::unique_ptr<GS_SemanticAnalyzer> Create(LRef<Driver::GS_Session> session,
                                                           AST::GSPassPtrArray semanticPasses);

        /**
         * Creating semantic analyzer with default semantic passes
         * @param session Session
         * @return Semantic analyzer ptr
         */
        static std::unique_ptr<GS_SemanticAnalyzer> Create(LRef<Driver::GS_Session> session);

    public:

        /*
         *
         * GS_SemanticAnalyzer PUBLIC METHODS
         *
         */

        /**
         * Run semantic passes on translation unit declaration
         * @param translationUnitDeclaration Translation unit declaration
         * @return Void return
         */
        Void Analyze(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration);


        /**
         * Run semantic passes on function declaration
         * @param functionDeclaration Function declaration
         * @return Void return
         */
        Void Analyze(AST::NodePtrLRef<AST::GS_FunctionDeclaration> functionDeclaration);

    private:

        /*
         *
         * GS_SemanticAnalyzer PRIVATE FIELDS
         *
         */

        /**
         * Session
         */
        LRef<Driver::GS_Session> _session;

        /**
         * Semantic passes
         */
        AST::GSPassPtrArray _semanticPasses;
    };

    /**
     * Semantic analyzer ptr type
     */
    using GSSemanticAnalyzerPtr = std::unique_ptr<GS_SemanticAnalyzer>;

}

#endif //GSLANGUAGE_GS_SEMANTICANALYZER_H
