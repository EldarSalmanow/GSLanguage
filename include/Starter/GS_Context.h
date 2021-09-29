#ifndef GSLANGUAGE_GS_CONTEXT_H
#define GSLANGUAGE_GS_CONTEXT_H

#include <Reader/GS_Code.h>
#include <Lexer/GS_Token.h>

namespace llvm {

    class LLVMContext;

    class Module;

}

namespace GSLanguageCompiler {

    namespace Lexer {

        class GS_Token;

        typedef std::vector<GS_Token> GSTokenArray;

    }

    namespace Parser {

        class GS_Node;

        typedef std::shared_ptr<GS_Node> GSNodePtr;

    }

    namespace Semantic {

        class GS_SemanticPass;

        typedef std::shared_ptr<GS_SemanticPass> GSSemanticPassPtr;

        typedef std::vector<GSSemanticPassPtr> GSSemanticPassPtrArray;

        class GS_TableOfVariables;

        typedef std::shared_ptr<GS_TableOfVariables> GSTableOfVariablesPtr;

    }

    namespace Optimizer {

        class GS_OptimizerPass;

        typedef std::shared_ptr<GS_OptimizerPass> GSOptimizerPassPtr;

        typedef std::vector<GSOptimizerPassPtr> GSOptimizerPassPtrArray;

    }

    namespace Starter {

        /**
         * Class for containing argument values
         */
        class GS_Arguments {
        public:

            /**
             * Default constructor for arguments
             */
            GS_Arguments();

        public:

            /**
             * Getter for input filename
             * @return
             */
            GSString getInputFilename();

            /**
             * Setter for input filename
             * @param inputFilename Input filename
             * @return
             */
            GSVoid setInputFilename(GSString inputFilename);

        private:

            /**
             * Input filename
             */
            GSString _inputFilename;
        };

        typedef std::shared_ptr<GS_Arguments> GSArgumentsPtr;

        /**
         * Compiler context
         */
        class GS_Context {
        public:

            /**
             * Default constructor for context
             */
            GS_Context();

        public:

            /**
             * Getter for arguments ptr
             * @return Arguments ptr
             */
            GSArgumentsPtr getArguments();

            /**
             * Setter for arguments ptr
             * @param arguments Arguments ptr
             * @return
             */
            GSVoid setArguments(GSArgumentsPtr arguments);

            /**
             * Getter for input code
             * @return Input code
             */
            Reader::GS_Code getInputCode();

            /**
             * Setter for input text
             * @param inputText Input code
             * @return
             */
            GSVoid setInputCode(Reader::GS_Code inputText);

            /**
             * Getter for lexer tokens
             * @return Lexer tokens
             */
            Lexer::GSTokenArray getTokens();

            /**
             * Setter fpr lexer tokens
             * @param tokens Lexer tokens
             * @return
             */
            GSVoid setTokens(Lexer::GSTokenArray tokens);

            /**
             * Getter for parser AST root node
             * @return Parser AST root node
             */
            Parser::GSNodePtr getRootNode();

            /**
             * Setter for parser AST root node
             * @param rootNode Parser AST root node
             * @return
             */
            GSVoid setRootNode(Parser::GSNodePtr rootNode);

            /**
             * Getter for semantic passes
             * @return Semantic passes
             */
            Semantic::GSSemanticPassPtrArray getSemanticPasses();

            /**
             * Setter for semantic passes
             * @param semanticPasses Semantic passes
             * @return
             */
            GSVoid setSemanticPasses(Semantic::GSSemanticPassPtrArray semanticPasses);

            /**
             * Getter for table of variables ptr
             * @return Table of variables ptr
             */
            Semantic::GSTableOfVariablesPtr getTableOfVariables();

            /**
             * Setter for table of variables ptr
             * @param tableOfVariables Table of variables ptr
             * @return
             */
            GSVoid setTableOfVariables(Semantic::GSTableOfVariablesPtr tableOfVariables);

            /**
             * Getter for optimizer passes
             * @return Optimizer passes
             */
            Optimizer::GSOptimizerPassPtrArray getOptimizerPasses();

            /**
             * Setter for optimizer passes
             * @param optimizerPasses Optimizer passes
             * @return
             */
            GSVoid setOptimizerPasses(Optimizer::GSOptimizerPassPtrArray optimizerPasses);

            /**
             * Getter for optimized AST root node
             * @return Optimized AST root node
             */
            Parser::GSNodePtr getOptimizedRootNode();

            /**
             * Setter for optimized AST root node
             * @param optimizedRootNode Optimized AST root node
             * @return
             */
            GSVoid setOptimizedRootNode(Parser::GSNodePtr optimizedRootNode);

            /**
             * Getter for LLVM context
             * @return LLVM context
             */
            std::shared_ptr<llvm::LLVMContext> getLLVMContext();

            /**
             * Setter for LLVM context
             * @param llvmContext LLVM context
             * @return
             */
            GSVoid setLLVMContext(std::shared_ptr<llvm::LLVMContext> llvmContext);

            /**
             * Getter for LLVM module
             * @return LLVM module
             */
            std::shared_ptr<llvm::Module> getLLVMModule();

            /**
             * Setter for LLVM module
             * @param llvmModule LLVM module
             * @return
             */
            GSVoid setLLVMModule(std::shared_ptr<llvm::Module> llvmModule);

        private:

            /**
             * Arguments ptr
             */
            GSArgumentsPtr _arguments;

            /**
             * Input text
             */
            Reader::GS_Code _inputText;

            /**
             * Lexer tokens
             */
            Lexer::GSTokenArray _tokens;

            /**
             * Parser AST root node
             */
            Parser::GSNodePtr _rootNode;

            /**
             * Semantic passes
             */
            Semantic::GSSemanticPassPtrArray _semanticPasses;

            /**
             * Table of variables ptr
             */
            Semantic::GSTableOfVariablesPtr _tableOfVariables;

            /**
             * Optimizer passes
             */
            Optimizer::GSOptimizerPassPtrArray _optimizerPasses;

            /**
             * Optimized parser AST root node
             */
            Parser::GSNodePtr _optimizedRootNode;

            /**
             * LLVM context
             */
            std::shared_ptr<llvm::LLVMContext> _llvmContext;

            /**
             * LLVM module
             */
            std::shared_ptr<llvm::Module> _llvmModule;
        };

        typedef std::shared_ptr<GS_Context> GSContextPtr;

    }

}

#endif //GSLANGUAGE_GS_CONTEXT_H
