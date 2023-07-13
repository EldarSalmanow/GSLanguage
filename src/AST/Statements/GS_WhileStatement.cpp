#include <Statements/GS_WhileStatement.h>

namespace GSLanguageCompiler::AST {

    GS_WhileStatement::GS_WhileStatement(GSExpressionPtr condition,
                                         GSStatementPtrArray body)
            : _condition(std::move(condition)),
              _body(std::move(body)) {}

    std::shared_ptr<GS_WhileStatement> GS_WhileStatement::Create(GSExpressionPtr condition,
                                                                 GSStatementPtrArray body) {
        return std::make_shared<GS_WhileStatement>(std::move(condition),
                                                   std::move(body));
    }

    std::shared_ptr<GS_WhileStatement> GS_WhileStatement::Create(GSExpressionPtr condition) {
        return GS_WhileStatement::Create(std::move(condition),
                                         GSStatementPtrArray());
    }

    LRef<GSStatementPtr> GS_WhileStatement::AddStatement(GSStatementPtr statement) {
        _body.emplace_back(std::move(statement));

        return _body[_body.size() - 1];
    }

    LRef<GSExpressionPtr> GS_WhileStatement::GetCondition() {
        return _condition;
    }

    LRef<GSStatementPtrArray> GS_WhileStatement::GetBody() {
        return _body;
    }

    StatementType GS_WhileStatement::GetStatementType() const {
        return StatementType::WhileStatement;
    }

}
