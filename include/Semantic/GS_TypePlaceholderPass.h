#ifndef GSLANGUAGE_GS_TYPEPLACEHOLDERPASS_H
#define GSLANGUAGE_GS_TYPEPLACEHOLDERPASS_H

#include <Semantic/GS_SemanticPass.h>

namespace GSLanguageCompiler::Semantic {

    class GS_TypePlaceholderPass : public GS_SemanticPass {
    public:

        GS_TypePlaceholderPass();

    public:

        GSVoid visit(Parser::GS_AssignmentNode *assignmentNode) override;
    };

}

#endif //GSLANGUAGE_GS_TYPEPLACEHOLDERPASS_H
