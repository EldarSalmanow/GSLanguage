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
         * @param context Context
         * @return
         */
        virtual Void Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration, LRef<Driver::GSContextPtr> context);

        /**
         * Run pass on nodes
         * @param nodes Nodes
         * @param context Context
         * @return
         */
        virtual Void Run(LRef<GSNodePtrArray> nodes, LRef<Driver::GSContextPtr> context);

        /**
         * Run pass on declarations
         * @param declarations Declarations
         * @param context Context
         * @return
         */
        virtual Void Run(LRef<GSDeclarationPtrArray> declarations, LRef<Driver::GSContextPtr> context);

        /**
         * Run pass on statements
         * @param statements Statements
         * @param context Context
         * @return
         */
        virtual Void Run(LRef<GSStatementPtrArray> statements, LRef<Driver::GSContextPtr> context);

        /**
         * Run pass on expressions
         * @param expressions Expressions
         * @param context Context
         * @return
         */
        virtual Void Run(LRef<GSExpressionPtrArray> expressions, LRef<Driver::GSContextPtr> context);
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
         * @param context Context
         * @return
         */
        Void Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration, LRef<Driver::GSContextPtr> context) override {
            T visitor;

            visitor.VisitTranslationUnitDeclaration(translationUnitDeclaration, context);
        }

        /**
         * Run pass on nodes
         * @param nodes Nodes
         * @param context Context
         * @return
         */
        Void Run(LRef<GSNodePtrArray> nodes, LRef<Driver::GSContextPtr> context) override {
            T visitor;

            for (auto &node : nodes) {
                visitor.VisitNode(node, context);
            }
        }

        /**
         * Run pass on declarations
         * @param declarations Declarations
         * @param context Context
         * @return
         */
        Void Run(LRef<GSDeclarationPtrArray> declarations, LRef<Driver::GSContextPtr> context) override {
            T visitor;

            for (auto &declaration : declarations) {
                visitor.VisitDeclaration(declaration, context);
            }
        }

        /**
         * Run pass on statements
         * @param statements Statements
         * @param context Context
         * @return
         */
        Void Run(LRef<GSStatementPtrArray> statements, LRef<Driver::GSContextPtr> context) override {
            T visitor;

            for (auto &statement : statements) {
                visitor.VisitStatement(statement, context);
            }
        }

        /**
         * Run pass on expressions
         * @param expressions Expressions
         * @param context Context
         * @return
         */
        Void Run(LRef<GSExpressionPtrArray> expressions, LRef<Driver::GSContextPtr> context) override {
            T visitor;

            for (auto &expression : expressions) {
                visitor.VisitExpression(expression, context);
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
         * @param context Context
         * @return
         */
        Void Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration, LRef<Driver::GSContextPtr> context) override {
            T transformer;

            translationUnitDeclaration = ToDeclaration<GS_TranslationUnitDeclaration>(
                    transformer.TransformTranslationUnitDeclaration(translationUnitDeclaration, context));
        }

        /**
         * Run pass on nodes
         * @param nodes Nodes
         * @param context Context
         * @return
         */
        Void Run(LRef<GSNodePtrArray> nodes, LRef<Driver::GSContextPtr> context) override {
            T transformer;

            for (auto &node : nodes) {
                node = transformer.TransformNode(node, context);
            }
        }

        /**
         * Run pass on declarations
         * @param declarations Declarations
         * @param context Context
         * @return
         */
        Void Run(LRef<GSDeclarationPtrArray> declarations, LRef<Driver::GSContextPtr> context) override {
            T transformer;

            for (auto &declaration : declarations) {
                declaration = ToDeclaration(transformer.TransformDeclaration(declaration, context));
            }
        }

        /**
         * Run pass on statements
         * @param statements Statements
         * @param context Context
         * @return
         */
        Void Run(LRef<GSStatementPtrArray> statements, LRef<Driver::GSContextPtr> context) override {
            T transformer;

            for (auto &statement : statements) {
                statement = ToStatement(transformer.TransformStatement(statement, context));
            }
        }

        /**
         * Run pass on expressions
         * @param expressions Expressions
         * @param context Context
         * @return
         */
        Void Run(LRef<GSExpressionPtrArray> expressions, LRef<Driver::GSContextPtr> context) override {
            T transformer;

            for (auto &expression : expressions) {
                expression = ToExpression(transformer.TransformExpression(expression, context));
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
         * @param context Context
         * @return
         */
        Void Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration, LRef<Driver::GSContextPtr> context);

        /**
         * Run pass on nodes
         * @param nodes Nodes
         * @param context Context
         * @return
         */
        Void Run(LRef<GSNodePtrArray> nodes, LRef<Driver::GSContextPtr> context);

        /**
         * Run pass on declarations
         * @param declarations Declarations
         * @param context Context
         * @return
         */
        Void Run(LRef<GSDeclarationPtrArray> declarations, LRef<Driver::GSContextPtr> context);

        /**
         * Run pass on statements
         * @param statements Statements
         * @param context Context
         * @return
         */
        Void Run(LRef<GSStatementPtrArray> statements, LRef<Driver::GSContextPtr> context);

        /**
         * Run pass on expressions
         * @param expressions Expressions
         * @param context Context
         * @return
         */
        Void Run(LRef<GSExpressionPtrArray> expressions, LRef<Driver::GSContextPtr> context);

        /**
         * Add pass to pass list
         * @param pass Pass
         * @return Pass
         */
        GSPassPtr AddPass(GSPassPtr pass);

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
