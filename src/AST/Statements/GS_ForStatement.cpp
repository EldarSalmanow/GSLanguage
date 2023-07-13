#include <Statements/GS_ForStatement.h>

namespace GSLanguageCompiler::AST {

    GS_ForStatement::GS_ForStatement(UString name,
                                     GSExpressionPtr expression,
                                     GSStatementPtrArray body)
            : _name(std::move(name)),
              _expression(std::move(expression)),
              _body(std::move(body)) {}

    std::shared_ptr<GS_ForStatement> GS_ForStatement::Create(UString name,
                                                             GSExpressionPtr expression,
                                                             GSStatementPtrArray body) {
        return std::make_shared<GS_ForStatement>(std::move(name),
                                                 std::move(expression),
                                                 std::move(body));
    }

    std::shared_ptr<GS_ForStatement> GS_ForStatement::Create(UString name,
                                                             GSExpressionPtr expression) {
        return GS_ForStatement::Create(std::move(name),
                                       std::move(expression),
                                       GSStatementPtrArray());
    }

    LRef<GSStatementPtr> GS_ForStatement::AddStatement(GSStatementPtr statement) {
        _body.emplace_back(std::move(statement));

        return _body[_body.size() - 1];
    }

    LRef<UString> GS_ForStatement::GetName() {
        return _name;
    }

    LRef<GSExpressionPtr> GS_ForStatement::GetExpression() {
        return _expression;
    }

    LRef<GSStatementPtrArray> GS_ForStatement::GetBody() {
        return _body;
    }

    StatementType GS_ForStatement::GetStatementType() const {
        return StatementType::ForStatement;
    }

}
