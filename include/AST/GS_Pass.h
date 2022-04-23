#ifndef GSLANGUAGE_GS_PASS_H
#define GSLANGUAGE_GS_PASS_H

#include <AST/GS_Visitor.h>

namespace GSLanguageCompiler::AST {

    // TODO comment all and add context with data for visitors and passes

    class GS_Pass {
    public:

        virtual ~GS_Pass();

    public:

        virtual Void Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration);

        virtual Void Run(LRef<GSNodePtrArray> nodes);

        virtual Void Run(LRef<GSDeclarationPtrArray> declarations);

        virtual Void Run(LRef<GSStatementPtrArray> statements);

        virtual Void Run(LRef<GSExpressionPtrArray> expressions);
    };

    using GSPassPtr = SharedPtr<GS_Pass>;

    using GSPassPtrArray = Vector<GSPassPtr>;

    template<typename T>
    class GS_VisitPass : public GS_Pass {
    public:

        Void Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration) override {
            T visitor;

            visitor.VisitTranslationUnitDeclaration(translationUnitDeclaration);
        }

        Void Run(LRef<GSNodePtrArray> nodes) override {
            T visitor;

            for (auto &node : nodes) {
                visitor.VisitNode(node);
            }
        }

        Void Run(LRef<GSDeclarationPtrArray> declarations) override {
            T visitor;

            for (auto &declaration : declarations) {
                visitor.VisitDeclaration(declaration);
            }
        }

        Void Run(LRef<GSStatementPtrArray> statements) override {
            T visitor;

            for (auto &statement : statements) {
                visitor.VisitStatement(statement);
            }
        }

        Void Run(LRef<GSExpressionPtrArray> expressions) override {
            T visitor;

            for (auto &expression : expressions) {
                visitor.VisitExpression(expression);
            }
        }
    };

    template<typename T>
    class GS_TransformPass : public GS_Pass {
    public:

        Void Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration) override {
            T transformer;

            translationUnitDeclaration = ToDeclaration<GS_TranslationUnitDeclaration>(transformer.TransformTranslationUnitDeclaration(translationUnitDeclaration));
        }

        Void Run(LRef<GSNodePtrArray> nodes) override {
            T transformer;

            for (auto &node : nodes) {
                node = transformer.TransformNode(node);
            }
        }

        Void Run(LRef<GSDeclarationPtrArray> declarations) override {
            T transformer;

            for (auto &declaration : declarations) {
                declaration = ToDeclaration(transformer.TransformDeclaration(declaration));
            }
        }

        Void Run(LRef<GSStatementPtrArray> statements) override {
            T transformer;

            for (auto &statement : statements) {
                statement = ToStatement(transformer.TransformStatement(statement));
            }
        }

        Void Run(LRef<GSExpressionPtrArray> expressions) override {
            T transformer;

            for (auto &expression : expressions) {
                expression = ToExpression(transformer.TransformExpression(expression));
            }
        }
    };

    class GS_PassManager {
    public:

        explicit GS_PassManager(GSPassPtrArray passes);

    public:

        static SharedPtr<GS_PassManager> Create(GSPassPtrArray passes);

        static SharedPtr<GS_PassManager> Create();

    public:

        Void Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration);

        Void Run(LRef<GSNodePtrArray> nodes);

        Void Run(LRef<GSDeclarationPtrArray> declarations);

        Void Run(LRef<GSStatementPtrArray> statements);

        Void Run(LRef<GSExpressionPtrArray> expressions);

        Void AddPass(GSPassPtr pass);

    public:

        GSPassPtrArray GetPasses() const;

    private:

        GSPassPtrArray _passes;
    };

    using GSPassManagerPtr = SharedPtr<GS_PassManager>;

}

#endif //GSLANGUAGE_GS_PASS_H
