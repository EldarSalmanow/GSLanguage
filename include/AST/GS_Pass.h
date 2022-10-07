#ifndef GSLANGUAGE_GS_PASS_H
#define GSLANGUAGE_GS_PASS_H

#include <AST/GS_Visitor.h>

namespace GSLanguageCompiler::AST {

    // TODO comment all and add context with data for visitors and passes

    class GS_Pass {
    public:

        virtual ~GS_Pass();

    public:

        virtual Void Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration, LRef<Driver::GSContextPtr> context);

        virtual Void Run(LRef<GSNodePtrArray> nodes, LRef<Driver::GSContextPtr> context);

        virtual Void Run(LRef<GSDeclarationPtrArray> declarations, LRef<Driver::GSContextPtr> context);

        virtual Void Run(LRef<GSStatementPtrArray> statements, LRef<Driver::GSContextPtr> context);

        virtual Void Run(LRef<GSExpressionPtrArray> expressions, LRef<Driver::GSContextPtr> context);
    };

    using GSPassPtr = std::shared_ptr<GS_Pass>;

    using GSPassPtrArray = std::vector<GSPassPtr>;

    template<typename T>
    class GS_VisitPass : public GS_Pass {
    public:

        Void Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration, LRef<Driver::GSContextPtr> context) override {
            T visitor;

            visitor.VisitTranslationUnitDeclaration(translationUnitDeclaration, context);
        }

        Void Run(LRef<GSNodePtrArray> nodes, LRef<Driver::GSContextPtr> context) override {
            T visitor;

            for (auto &node : nodes) {
                visitor.VisitNode(node, context);
            }
        }

        Void Run(LRef<GSDeclarationPtrArray> declarations, LRef<Driver::GSContextPtr> context) override {
            T visitor;

            for (auto &declaration : declarations) {
                visitor.VisitDeclaration(declaration, context);
            }
        }

        Void Run(LRef<GSStatementPtrArray> statements, LRef<Driver::GSContextPtr> context) override {
            T visitor;

            for (auto &statement : statements) {
                visitor.VisitStatement(statement, context);
            }
        }

        Void Run(LRef<GSExpressionPtrArray> expressions, LRef<Driver::GSContextPtr> context) override {
            T visitor;

            for (auto &expression : expressions) {
                visitor.VisitExpression(expression, context);
            }
        }
    };

    template<typename T>
    class GS_TransformPass : public GS_Pass {
    public:

        Void Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration, LRef<Driver::GSContextPtr> context) override {
            T transformer;

            translationUnitDeclaration = ToDeclaration<GS_TranslationUnitDeclaration>(
                    transformer.TransformTranslationUnitDeclaration(translationUnitDeclaration, context));
        }

        Void Run(LRef<GSNodePtrArray> nodes, LRef<Driver::GSContextPtr> context) override {
            T transformer;

            for (auto &node : nodes) {
                node = transformer.TransformNode(node, context);
            }
        }

        Void Run(LRef<GSDeclarationPtrArray> declarations, LRef<Driver::GSContextPtr> context) override {
            T transformer;

            for (auto &declaration : declarations) {
                declaration = ToDeclaration(transformer.TransformDeclaration(declaration, context));
            }
        }

        Void Run(LRef<GSStatementPtrArray> statements, LRef<Driver::GSContextPtr> context) override {
            T transformer;

            for (auto &statement : statements) {
                statement = ToStatement(transformer.TransformStatement(statement, context));
            }
        }

        Void Run(LRef<GSExpressionPtrArray> expressions, LRef<Driver::GSContextPtr> context) override {
            T transformer;

            for (auto &expression : expressions) {
                expression = ToExpression(transformer.TransformExpression(expression, context));
            }
        }
    };

    class GS_PassManager {
    public:

        explicit GS_PassManager(GSPassPtrArray passes);

    public:

        static std::shared_ptr<GS_PassManager> Create(GSPassPtrArray passes);

        static std::shared_ptr<GS_PassManager> Create();

    public:

        Void Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration, LRef<Driver::GSContextPtr> context);

        Void Run(LRef<GSNodePtrArray> nodes, LRef<Driver::GSContextPtr> context);

        Void Run(LRef<GSDeclarationPtrArray> declarations, LRef<Driver::GSContextPtr> context);

        Void Run(LRef<GSStatementPtrArray> statements, LRef<Driver::GSContextPtr> context);

        Void Run(LRef<GSExpressionPtrArray> expressions, LRef<Driver::GSContextPtr> context);

        Void AddPass(GSPassPtr pass);

    public:

        GSPassPtrArray GetPasses() const;

    private:

        GSPassPtrArray _passes;
    };

    using GSPassManagerPtr = std::shared_ptr<GS_PassManager>;

}

#endif //GSLANGUAGE_GS_PASS_H
