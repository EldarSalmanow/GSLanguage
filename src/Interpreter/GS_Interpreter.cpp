#include <GS_Interpreter.h>

namespace GSLanguageCompiler::Interpreter {

    GS_Interpreter::GS_Interpreter(Parser::GSNodePtrArray nodes)
            : _nodes(std::move(nodes)) {}

    GSVoid GS_Interpreter::startInterpret() {
        for (auto &node : _nodes) {
            node->interpret();
        }
    }

}
