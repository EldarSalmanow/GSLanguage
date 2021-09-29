#ifndef GSLANGUAGE_GS_VARIABLESPLACEHOLDERPASS_H
#define GSLANGUAGE_GS_VARIABLESPLACEHOLDERPASS_H

#include <Semantic/GS_SemanticPass.h>

namespace GSLanguageCompiler::Semantic {

    class GS_VariablesPlaceholderPass : public GS_SemanticPass {
    public:

        GS_VariablesPlaceholderPass();

    public:

        GSVoid visit(Parser::GS_AssignmentNode *assignmentNode) override;
    };

}

#endif //GSLANGUAGE_GS_VARIABLESPLACEHOLDERPASS_H
