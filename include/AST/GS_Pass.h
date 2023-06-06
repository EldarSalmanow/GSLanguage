#ifndef GSLANGUAGE_GS_PASS_H
#define GSLANGUAGE_GS_PASS_H

#include <AST/GS_Visitor.h>

namespace GSLanguageCompiler::AST {

    /**
     * Class for run visitor on any nodes
     */
    class GS_Pass {
    public:

        /*
         *
         * GS_Pass PUBLIC DESTRUCTORS
         *
         */

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Pass();

    public:

        /*
         *
         * GS_Pass PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Run pass on translation unit declaration
         * @param session Session
         * @param translationUnitDeclaration Translation unit declaration
         * @return Void return
         */
        virtual Void Run(LRef<Driver::GS_Session> session,
                         LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration);

        /**
         * Run pass on function declaration
         * @param session Session
         * @param functionDeclaration Function declaration
         * @return Void return
         */
        virtual Void Run(LRef<Driver::GS_Session> session,
                         NodePtrLRef<GS_FunctionDeclaration> functionDeclaration);
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
     * @tparam VisitorT Type of visitor
     */
    template<typename VisitorT>
    class GS_VisitPass : public GS_Pass {
    public:

        /*
         *
         * GS_VisitPass PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Default constructor for visit pass
         */
        GS_VisitPass() = default;

    public:

        /*
         *
         * GS_VisitPass PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Run pass on translation unit declaration
         * @param session Session
         * @param translationUnitDeclaration Translation unit declaration
         * @return Void return
         */
        Void Run(LRef<Driver::GS_Session> session,
                 LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration) override {
            VisitorT visitor;

            visitor.VisitTranslationUnitDeclaration(session,
                                                    translationUnitDeclaration);
        }

        /**
         * Run pass on function declaration
         * @param session Session
         * @param functionDeclaration Function declaration
         * @return Void return
         */
        Void Run(LRef<Driver::GS_Session> session,
                 NodePtrLRef<GS_FunctionDeclaration> functionDeclaration) override {
            VisitorT visitor;

            visitor.VisitFunctionDeclaration(session,
                                             functionDeclaration);
        }
    };

    /**
     * Class for generating default pass for transformer
     * @tparam TransformerT Type of transformer
     */
    template<typename TransformerT>
    class GS_TransformPass : public GS_Pass {
    public:

        /*
         *
         * GS_TransformPass PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Default constructor for transform pass
         */
        GS_TransformPass() = default;

    public:

        /*
         *
         * GS_TransformPass PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Run pass on translation unit declaration
         * @param session Session
         * @param translationUnitDeclaration Translation unit declaration
         * @return Void return
         */
        Void Run(LRef<Driver::GS_Session> session,
                 LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration) override {
            TransformerT transformer;

            translationUnitDeclaration = ToDeclaration<GS_TranslationUnitDeclaration>(transformer.TransformTranslationUnitDeclaration(session,
                                                                                                                                      translationUnitDeclaration));
        }

        /**
         * Run pass on function declaration
         * @param session Session
         * @param functionDeclaration Function declaration
         * @return Void return
         */
        Void Run(LRef<Driver::GS_Session> session,
                 NodePtrLRef<GS_FunctionDeclaration> functionDeclaration) override {
            TransformerT transformer;

            functionDeclaration = ToDeclaration<GS_FunctionDeclaration>(transformer.TransformFunctionDeclaration(session,
                                                                                                                 functionDeclaration));
        }
    };

    /**
     * Class for managing and running passes
     */
    class GS_PassManager {
    public:

        /*
         *
         * GS_PassManager PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for pass manager
         * @param passes Passes
         */
        explicit GS_PassManager(GSPassPtrArray passes);

    public:

        /*
         *
         * GS_PassManager PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating pass manager
         * @param passes Passes
         * @return Pass manager ptr
         */
        static std::unique_ptr<GS_PassManager> Create(GSPassPtrArray passes);

        /**
         * Creating pass manager
         * @return Pass manager ptr
         */
        static std::unique_ptr<GS_PassManager> Create();

    public:

        /*
         *
         * GS_PassManager PUBLIC METHODS
         *
         */

        /**
         * Run passes on translation unit declaration
         * @param session Session
         * @param translationUnitDeclaration Translation unit declaration
         * @return Void return
         */
        Void Run(LRef<Driver::GS_Session> session,
                 LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration);


        /**
         * Run passes on function declaration
         * @param session Session
         * @param functionDeclaration Function declaration
         * @return Void return
         */
        Void Run(LRef<Driver::GS_Session> session,
                 NodePtrLRef<GS_FunctionDeclaration> functionDeclaration);

        /**
         * Add pass to pass list
         * @param pass Pass
         * @return Pass
         */
        ConstLRef<GSPassPtr> AddPass(GSPassPtr pass);

    public:

        /*
         *
         * GS_PassManager PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for passes
         * @return Passes
         */
        ConstLRef<GSPassPtrArray> GetPasses() const;

    private:

        /*
         *
         * GS_PassManager PRIVATE FIELDS
         *
         */

        /**
         * Passes
         */
        GSPassPtrArray _passes;
    };

    /**
     * Pass manager ptr type
     */
    using GSPassManagerPtr = std::unique_ptr<GS_PassManager>;

}

#endif //GSLANGUAGE_GS_PASS_H
