#include <Statements/GS_IfStatement.h>

namespace GSLanguageCompiler::AST {

    GS_IfStatement::GS_IfStatement(GSExpressionPtr condition,
                                   GSStatementPtrArray ifBody,
                                   GSStatementPtrArray elseBody)
            : _condition(std::move(condition)),
              _ifBody(std::move(ifBody)),
              _elseBody(std::move(elseBody)) {}

    std::shared_ptr<GS_IfStatement> GS_IfStatement::Create(GSExpressionPtr condition,
                                                           GSStatementPtrArray ifBody,
                                                           GSStatementPtrArray elseBody) {
        return std::make_shared<GS_IfStatement>(std::move(condition),
                                                std::move(ifBody),
                                                std::move(elseBody));
    }

    std::shared_ptr<GS_IfStatement> GS_IfStatement::Create(GSExpressionPtr condition,
                                                           GSStatementPtrArray ifBody) {
        return GS_IfStatement::Create(std::move(condition),
                                      std::move(ifBody),
                                      GSStatementPtrArray());
    }

    std::shared_ptr<GS_IfStatement> GS_IfStatement::Create(GSExpressionPtr condition) {
        return GS_IfStatement::Create(std::move(condition),
                                      GSStatementPtrArray());
    }

    LRef<GSStatementPtr> GS_IfStatement::AddIfStatement(GSStatementPtr statement) {
        _ifBody.emplace_back(std::move(statement));

        return _ifBody[_ifBody.size() - 1];
    }

    LRef<GSStatementPtr> GS_IfStatement::AddElseStatement(GSStatementPtr statement) {
        _elseBody.emplace_back(std::move(statement));

        return _elseBody[_elseBody.size() - 1];
    }

    LRef<GSExpressionPtr> GS_IfStatement::GetCondition() {
        return _condition;
    }

    LRef<GSStatementPtrArray> GS_IfStatement::GetIfBody() {
        return _ifBody;
    }

    LRef<GSStatementPtrArray> GS_IfStatement::GetElseBody() {
        return _elseBody;
    }

    StatementType GS_IfStatement::GetStatementType() const {
        return StatementType::IfStatement;
    }

}
