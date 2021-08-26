#include <GS_Optimizer.h>

namespace GSLanguageCompiler::Optimizer {

    GS_Optimizer::GS_Optimizer(Parser::GSNodePtr nodes, GSOptimizerPassPtrArray passes)
            : _nodes(std::move(nodes)), _passes(std::move(passes)) {}

    Parser::GSNodePtr GS_Optimizer::optimize() {
        for (auto &pass : _passes) {
            _nodes = _nodes->accept(pass.get());
        }

        return _nodes;
    }

}