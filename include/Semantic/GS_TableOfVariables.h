#ifndef GSLANGUAGE_GS_TABLEOFVARIABLES_H
#define GSLANGUAGE_GS_TABLEOFVARIABLES_H

#include <map>

#include <Exceptions/GS_ErrorHandler.h>

namespace GSLanguageCompiler::Parser {

    class GS_Node;

    typedef std::shared_ptr<GS_Node> GSNodePtr;

    enum class ValueType;

    class GS_VariableDeclarationNode;

}

namespace GSLanguageCompiler::Semantic {

    class GS_TableOfVariables {
    public:

        GS_TableOfVariables();

    public:

        GSVoid addVariable(Parser::GS_VariableDeclarationNode *variable, Parser::GSNodePtr node);

        Parser::ValueType getValueTypeByName(GSString name);

        Parser::GSNodePtr getNodePtrByName(GSString name);

        GSVoid setNodePtrByName(GSString name, Parser::GSNodePtr node);

        std::pair<Parser::GS_VariableDeclarationNode*, Parser::GSNodePtr> getVariableByName(GSString name);

    public:

        std::map<Parser::GS_VariableDeclarationNode*, Parser::GSNodePtr> getVariables();

    private:

        std::map<Parser::GS_VariableDeclarationNode*, Parser::GSNodePtr> _variables;
    };

    typedef std::shared_ptr<GS_TableOfVariables> GSTableOfVariablesPtr;

}

#endif //GSLANGUAGE_GS_TABLEOFVARIABLES_H
