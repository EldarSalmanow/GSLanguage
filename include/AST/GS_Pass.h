#ifndef GSLANGUAGE_GS_PASS_H
#define GSLANGUAGE_GS_PASS_H

#include <AST/GS_Visitor.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for run visitor on any nodes
     */
    class GS_Pass {
    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Pass();

    public:

        /**
         * Run pass on translation unit declaration ptr
         * @param translationUnitDeclaration Translation unit declaration ptr
         * @param session Session
         * @return
         */
        virtual Void Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration,
                         LRef<Driver::GS_Session> session);

        /**
         * Run pass on node ptr
         * @param node Node ptr
         * @param session Session
         * @return
         */
        virtual Void Run(LRef<GSNodePtr> node,
                         LRef<Driver::GS_Session> session);

        /**
         * Run pass on nodes
         * @param nodes Nodes
         * @param session Session
         * @return
         */
        virtual Void Run(LRef<GSNodePtrArray> nodes,
                         LRef<Driver::GS_Session> session);

        /**
         * Run pass on declarations
         * @param declarations Declarations
         * @param session Session
         * @return
         */
        virtual Void Run(LRef<GSDeclarationPtrArray> declarations,
                         LRef<Driver::GS_Session> session);

        /**
         * Run pass on statements
         * @param statements Statements
         * @param session Session
         * @return
         */
        virtual Void Run(LRef<GSStatementPtrArray> statements,
                         LRef<Driver::GS_Session> session);

        /**
         * Run pass on expressions
         * @param expressions Expressions
         * @param session Session
         * @return
         */
        virtual Void Run(LRef<GSExpressionPtrArray> expressions,
                         LRef<Driver::GS_Session> session);
    };

    /**
     * Pass ptr type
     */
    using GSPassPtr = std::shared_ptr<GS_Pass>;

    /**
     * Pass ptr array type
     */
    using GSPassPtrArray = std::vector<GSPassPtr>;

    /**
     * Class for generating default pass for visitor
     * @tparam T Type of visitor
     */
    template<typename T>
    class GS_VisitPass : public GS_Pass {
    public:

        /**
         * Run pass on translation unit declaration ptr
         * @param translationUnitDeclaration Translation unit declaration ptr
         * @param session Session
         * @return
         */
        Void Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration,
                 LRef<Driver::GS_Session> session) override {
            T visitor;

            visitor.VisitTranslationUnitDeclaration(translationUnitDeclaration, session);
        }

        /**
         * Run pass on node ptr
         * @param node Node ptr
         * @param session Session
         * @return
         */
        Void Run(LRef<GSNodePtr> node,
                 LRef<Driver::GS_Session> session) override {
            T visitor;

            visitor.VisitNode(node, session);
        }

        /**
         * Run pass on nodes
         * @param nodes Nodes
         * @param session Session
         * @return
         */
        Void Run(LRef<GSNodePtrArray> nodes,
                 LRef<Driver::GS_Session> session) override {
            T visitor;

            for (auto &node : nodes) {
                visitor.VisitNode(node, session);
            }
        }

        /**
         * Run pass on declarations
         * @param declarations Declarations
         * @param session Session
         * @return
         */
        Void Run(LRef<GSDeclarationPtrArray> declarations,
                 LRef<Driver::GS_Session> session) override {
            T visitor;

            for (auto &declaration : declarations) {
                visitor.VisitDeclaration(declaration, session);
            }
        }

        /**
         * Run pass on statements
         * @param statements Statements
         * @param session Session
         * @return
         */
        Void Run(LRef<GSStatementPtrArray> statements,
                 LRef<Driver::GS_Session> session) override {
            T visitor;

            for (auto &statement : statements) {
                visitor.VisitStatement(statement, session);
            }
        }

        /**
         * Run pass on expressions
         * @param expressions Expressions
         * @param session Session
         * @return
         */
        Void Run(LRef<GSExpressionPtrArray> expressions,
                 LRef<Driver::GS_Session> session) override {
            T visitor;

            for (auto &expression : expressions) {
                visitor.VisitExpression(expression, session);
            }
        }
    };

    /**
     * Class for generating default pass for transformer
     * @tparam T Type of transformer
     */
    template<typename T>
    class GS_TransformPass : public GS_Pass {
    public:

        /**
         * Run pass on translation unit declaration ptr
         * @param translationUnitDeclaration Translation unit declaration ptr
         * @param session Session
         * @return
         */
        Void Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration,
                 LRef<Driver::GS_Session> session) override {
            T transformer;

            translationUnitDeclaration = ToDeclaration<GS_TranslationUnitDeclaration>(
                    transformer.TransformTranslationUnitDeclaration(translationUnitDeclaration, session));
        }

        /**
         * Run pass on node ptr
         * @param node Node ptr
         * @param session Session
         * @return
         */
        Void Run(LRef<GSNodePtr> node,
                 LRef<Driver::GS_Session> session) override {
            T transformer;

            node = transformer.TransformNode(node, session);
        }

        /**
         * Run pass on nodes
         * @param nodes Nodes
         * @param session Session
         * @return
         */
        Void Run(LRef<GSNodePtrArray> nodes,
                 LRef<Driver::GS_Session> session) override {
            T transformer;

            for (auto &node : nodes) {
                node = transformer.TransformNode(node, session);
            }
        }

        /**
         * Run pass on declarations
         * @param declarations Declarations
         * @param session Session
         * @return
         */
        Void Run(LRef<GSDeclarationPtrArray> declarations,
                 LRef<Driver::GS_Session> session) override {
            T transformer;

            for (auto &declaration : declarations) {
                declaration = ToDeclaration(transformer.TransformDeclaration(declaration, session));
            }
        }

        /**
         * Run pass on statements
         * @param statements Statements
         * @param session Session
         * @return
         */
        Void Run(LRef<GSStatementPtrArray> statements,
                 LRef<Driver::GS_Session> session) override {
            T transformer;

            for (auto &statement : statements) {
                statement = ToStatement(transformer.TransformStatement(statement, session));
            }
        }

        /**
         * Run pass on expressions
         * @param expressions Expressions
         * @param session Session
         * @return
         */
        Void Run(LRef<GSExpressionPtrArray> expressions,
                 LRef<Driver::GS_Session> session) override {
            T transformer;

            for (auto &expression : expressions) {
                expression = ToExpression(transformer.TransformExpression(expression, session));
            }
        }
    };

    /**
     * Class for managing and running passes
     */
    class GS_PassManager {
    public:

        /**
         * Constructor for pass manager
         * @param passes Passes
         */
        explicit GS_PassManager(GSPassPtrArray passes);

    public:

        /**
         * Creating pass manager
         * @param passes Passes
         * @return Pass manager ptr
         */
        static std::shared_ptr<GS_PassManager> Create(GSPassPtrArray passes);

        /**
         * Creating pass manager
         * @return Pass manager ptr
         */
        static std::shared_ptr<GS_PassManager> Create();

    public:

        /**
         * Run passes on translation unit declaration ptr
         * @param translationUnitDeclaration Translation unit declaration ptr
         * @param session Session
         * @return
         */
        Void Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration,
                 LRef<Driver::GS_Session> session);


        /**
         * Run passes on node ptr
         * @param node Node ptr
         * @param session Session
         * @return
         */
        Void Run(LRef<GSNodePtr> node,
                 LRef<Driver::GS_Session> session);

        /**
         * Run pass on nodes
         * @param nodes Nodes
         * @param session Session
         * @return
         */
        Void Run(LRef<GSNodePtrArray> nodes,
                 LRef<Driver::GS_Session> session);

        /**
         * Run pass on declarations
         * @param declarations Declarations
         * @param session Session
         * @return
         */
        Void Run(LRef<GSDeclarationPtrArray> declarations,
                 LRef<Driver::GS_Session> session);

        /**
         * Run pass on statements
         * @param statements Statements
         * @param session Session
         * @return
         */
        Void Run(LRef<GSStatementPtrArray> statements,
                 LRef<Driver::GS_Session> session);

        /**
         * Run pass on expressions
         * @param expressions Expressions
         * @param session Session
         * @return
         */
        Void Run(LRef<GSExpressionPtrArray> expressions,
                 LRef<Driver::GS_Session> session);

    public:

        /**
         * Add pass to pass list
         * @param pass Pass
         * @return Pass
         */
        Void AddPass(GSPassPtr pass);

    public:

        /**
         * Getter for passes
         * @return Passes
         */
        GSPassPtrArray GetPasses() const;

    private:

        /**
         * Passes
         */
        GSPassPtrArray _passes;
    };

    /**
     * Pass manager ptr type
     */
    using GSPassManagerPtr = std::shared_ptr<GS_PassManager>;

}

#endif //GSLANGUAGE_GS_PASS_H
