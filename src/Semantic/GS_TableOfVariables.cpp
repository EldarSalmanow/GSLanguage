#include <GS_TableOfVariables.h>

#include <Parser/Nodes/GS_VariableDeclarationNode.h>

namespace GSLanguageCompiler::Semantic {

    GS_TableOfVariables::GS_TableOfVariables() = default;

    GSVoid GS_TableOfVariables::addVariable(Parser::GS_VariableDeclarationNode *variable, Parser::GSNodePtr node) {
        _variables[variable] = std::move(node);
    }

    Parser::ValueType GS_TableOfVariables::getValueTypeByName(GSString name) {
        for (auto &[declaration, node] : _variables) {
            if (declaration->getName() == name) {
                return declaration->getType();
            }
        }

        Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                       "Can`t find variable with name \"" + name + "\"!");

        Exceptions::errorHandler.throw_();

        return Parser::ValueType::VOID;
    }

    Parser::GSNodePtr GS_TableOfVariables::getNodePtrByName(GSString name) {
        for (auto &[declaration, node] : _variables) {
            if (declaration->getName() == name) {
                return node;
            }
        }

        Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                       "Can`t find variable with name \"" + name + "\"!");

        Exceptions::errorHandler.throw_();

        return nullptr;
    }

    GSVoid GS_TableOfVariables::setNodePtrByName(GSString name, Parser::GSNodePtr node) {
        for (auto &[declaration, expression] : _variables) {
            if (declaration->getName() == name) {
                expression = std::move(node);
            }
        }
    }

    std::pair<Parser::GS_VariableDeclarationNode*, Parser::GSNodePtr> GS_TableOfVariables::getVariableByName(GSString name) {
        for (auto &pair : _variables) {
            if (pair.first->getName() == name) {
                return pair;
            }
        }

        Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                       "Can`t find variable with name \"" + name + "\"!");

        Exceptions::errorHandler.throw_();

        return std::make_pair(nullptr, nullptr);
    }

    std::map<Parser::GS_VariableDeclarationNode*, Parser::GSNodePtr> GS_TableOfVariables::getVariables() {
        return _variables;
    }

}
