#ifndef GSLANGUAGE_GS_CGBACKEND_H
#define GSLANGUAGE_GS_CGBACKEND_H

#include <Driver/GS_Session.h>

#include <AST/Declarations/GS_TranslationUnitDeclaration.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     * Code generation backend type
     */
    enum class CGBackendType {
        LLVM
    };

    /**
     * Class for containing generated code
     */
    class GS_CodeHolder {
    public:

        /*
         *
         * GS_CodeHolder PUBLIC DESTRUCTORS
         *
         */

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_CodeHolder();

    public:

        /*
         *
         * GS_CodeHolder PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Getter for code holder backend type
         * @return Code holder backend type
         */
        virtual CGBackendType GetBackendType() const = 0;
    };

    /**
     * Code holder ptr type
     */
    using GSCodeHolderPtr = std::shared_ptr<GS_CodeHolder>;

    /**
     * Class for translating AST to any programming language
     */
    class GS_CodeGenerator {
    public:

        /*
         *
         * GS_CodeGenerator PUBLIC DESTRUCTORS
         *
         */

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_CodeGenerator();

    public:

        /*
         *
         * GS_CodeGenerator PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Translating translation unit declaration to any programming language code and returning it in code holder
         * @param session Session
         * @param unit Translation unit declaration
         * @return Code holder
         */
        virtual GSCodeHolderPtr Generate(LRef<Driver::GS_Session> session,
                                         AST::GSTranslationUnitDeclarationPtr unit) = 0;

    public:

        /*
         *
         * GS_CodeGenerator PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Getter for code generator backend type
         * @return Code generator backend type
         */
        virtual CGBackendType GetBackendType() const = 0;
    };

    /**
     * Code generator ptr type
     */
    using GSCodeGeneratorPtr = std::shared_ptr<GS_CodeGenerator>;

    /**
     * Class for writing code holder to file
     */
    class GS_CodeWriter {
    public:

        /*
         *
         * GS_CodeWriter PUBLIC DESTRUCTORS
         *
         */

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_CodeWriter();

    public:

        /*
         *
         * GS_CodeWriter PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Writing code holder to file
         * @param session Session
         * @param fileName File name
         * @param codeHolder Code holder
         * @return Void return
         */
        virtual Void Write(LRef<Driver::GS_Session> session,
                           UString fileName,
                           GSCodeHolderPtr codeHolder) = 0;

    public:

        /*
         *
         * GS_CodeWriter PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Getter for code writer backend type
         * @return Code writer backend type
         */
        virtual CGBackendType GetBackendType() const = 0;
    };

    /**
     * Code writer ptr type
     */
    using GSCodeWriterPtr = std::shared_ptr<GS_CodeWriter>;

    /**
     * Class for containing set of operations with code generation
     */
    class GS_CGBackend {
    public:

        /*
         *
         * GS_CGBackend PUBLIC DESTRUCTORS
         *
         */

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_CGBackend();

    public:

        /*
         *
         * GS_CGBackend PUBLIC METHODS
         *
         */

        /**
         * Translating translation unit declaration to any programming language code and returning it in code holder
         * @param session Session
         * @param unit Translation unit declaration
         * @return Code holder
         */
        GSCodeHolderPtr Generate(LRef<Driver::GS_Session> session,
                                 AST::GSTranslationUnitDeclarationPtr unit);

        /**
         * Writing code holder to file
         * @param session Session
         * @param fileName File name
         * @param codeHolder Code holder
         * @return Void return
         */
        Void Write(LRef<Driver::GS_Session> session,
                   UString fileName,
                   GSCodeHolderPtr codeHolder);

    public:

        /*
         *
         * GS_CGBackend PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Getter for code generator
         * @return Code generator
         */
        virtual GSCodeGeneratorPtr GetCodeGenerator() = 0;

        /**
         * Getter for code writer
         * @return Code writer
         */
        virtual GSCodeWriterPtr GetCodeWriter() = 0;

    public:

        /*
         *
         * GS_CGBackend PUBLIC VIRTUAL METHODS
         *
         */

        /**
         * Getter for code generation backend type
         * @return Code generation backend type
         */
        virtual CGBackendType GetBackendType() const = 0;
    };

    /**
     * Code generation backend type
     */
    using GSCGBackendPtr = std::shared_ptr<GS_CGBackend>;

}

#endif //GSLANGUAGE_GS_CGBACKEND_H
