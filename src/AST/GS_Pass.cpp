#include <GS_Pass.h>

namespace GSLanguageCompiler::AST {

    GS_Pass::GS_Pass(GSVisitorPtr visitor)
            : _visitor(std::move(visitor)) {}

    GS_Pass::~GS_Pass() = default;

    GSVisitorPtr GS_Pass::getVisitor() {
        return _visitor;
    }

    Void GS_Pass::runForDeclarations(GSDeclarationPtrArray &declarations) {}

    Void GS_Pass::runForStatements(GSStatementPtrArray &statements) {}

    Void GS_Pass::runForExpressions(GSExpressionPtrArray &expressions) {}

}
