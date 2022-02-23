#include <GS_Pass.h>

namespace GSLanguageCompiler::AST {

    GS_Pass::GS_Pass(GSVisitorPtr visitor)
            : _visitor(std::move(visitor)), _transformer(nullptr) {}

    GS_Pass::GS_Pass(GSTransformerPtr transformer)
            : _visitor(nullptr), _transformer(std::move(transformer)) {}

    Bool GS_Pass::run(GSNodePtrArray nodes) {
        if (_visitor != nullptr) {
            for (auto &node : nodes) {
                _visitor->visitNode(node);
            }

            return true;
        }

        if (_transformer != nullptr) {
            for (auto &node : nodes) {
                _transformer->visitNode(node);
            }

            return true;
        }

        return false;
    }

    Bool GS_Pass::runForDeclarations(GSDeclarationPtrArray declarations) {
        if (_visitor != nullptr) {
            for (auto &declaration : declarations) {
                _visitor->visitDeclaration(declaration);
            }

            return true;
        }

        if (_transformer != nullptr) {
            for (auto &declaration : declarations) {
                _transformer->visitDeclaration(declaration);
            }

            return true;
        }

        return false;
    }

    Bool GS_Pass::runForStatements(GSStatementPtrArray statements) {
        if (_visitor != nullptr) {
            for (auto &statement : statements) {
                _visitor->visitStatement(statement);
            }

            return true;
        }

        if (_transformer != nullptr) {
            for (auto &statement : statements) {
                _transformer->visitStatement(statement);
            }

            return true;
        }

        return false;
    }

    Bool GS_Pass::runForExpressions(GSExpressionPtrArray expressions) {
        if (_visitor != nullptr) {
            for (auto &expression : expressions) {
                _visitor->visitExpression(expression);
            }

            return true;
        }

        if (_transformer != nullptr) {
            for (auto &expression : expressions) {
                _transformer->visitExpression(expression);
            }

            return true;
        }

        return false;
    }

}
