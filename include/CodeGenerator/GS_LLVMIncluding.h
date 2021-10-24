#ifndef GSLANGUAGE_GS_LLVMINCLUDING_H
#define GSLANGUAGE_GS_LLVMINCLUDING_H

#include <llvm/IR/IRBuilder.h>

namespace LLVM {

    /**
     * LLVM context type
     */
    using Context = llvm::LLVMContext;

    /**
    * LLVM module type
    */
    using Module = llvm::Module;

    /**
    * IR builder type
    */
    using IRBuilder = llvm::IRBuilder<>;
}

#endif //GSLANGUAGE_GS_LLVMINCLUDING_H
