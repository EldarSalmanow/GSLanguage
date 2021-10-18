#include <llvm/Bitcode/BitcodeWriter.h>

#include <GS_CodeGenerator.h>

#include <AST/GS_Node.h>

#include <Exceptions/GS_ErrorHandler.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CodeGenerator::GS_CodeGenerator() = default;

    GSVoid GS_CodeGenerator::run(Starter::GSContextPtr &context) {
        GS_LLVMCodeGenVisitor visitor;

        visitor.setup(context);

        context->getOptimizedRootNode()->accept(&visitor);

        std::error_code errorCode;
        llvm::raw_fd_ostream stream("test.bc", errorCode);

        if (errorCode) {
            Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                           errorCode.message());

            Exceptions::errorHandler.throw_();
        }

        llvm::WriteBitcodeToFile(*context->getLLVMModule(), stream);
    }

}