#include <Declarations/GS_VariableDeclaration.h>

namespace GSLanguageCompiler::AST {

    GS_VariableDeclaration::GS_VariableDeclaration(String name, GSTypePtr type, GSExpressionPtr expression)
            : _name(std::move(name)), _type(std::move(type)), _expression(std::move(expression)) {}

    String GS_VariableDeclaration::getName() {
        return _name;
    }

    GSTypePtr GS_VariableDeclaration::getType() {
        return _type;
    }

    GSExpressionPtr GS_VariableDeclaration::getExpression() {
        return _expression;
    }

    Void GS_VariableDeclaration::accept(GS_Visitor *visitor) {
        visitor->visit(this);
    }

    DeclarationType GS_VariableDeclaration::getDeclarationType() {
        return DeclarationType::VariableDeclaration;
    }

}
