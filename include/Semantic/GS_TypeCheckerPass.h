#ifndef GSLANGUAGE_GS_TYPECHECKERPASS_H
#define GSLANGUAGE_GS_TYPECHECKERPASS_H

#include <Semantic/GS_SemanticPass.h>

namespace GSLanguageCompiler::Semantic {

    class GS_TypeCheckerPass : public GS_SemanticPass {
    public:

        GS_TypeCheckerPass();

    public:

        GSVoid visit(Parser::GS_AssignmentNode *assignmentNode) override;
    };

}

#endif //GSLANGUAGE_GS_TYPECHECKERPASS_H
