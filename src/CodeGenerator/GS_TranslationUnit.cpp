#include <GS_CompilerUnit.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CompilerUnit::GS_CompilerUnit(const String &name)
            : _module(name, _context), _builder(_context) {}

    LLVM::Context &GS_CompilerUnit::getContext() {
        return _context;
    }

    LLVM::Module &GS_CompilerUnit::getModule() {
        return _module;
    }

    LLVM::IRBuilder &GS_CompilerUnit::getBuilder() {
        return _builder;
    }

}
