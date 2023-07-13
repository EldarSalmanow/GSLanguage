#include <Statements/GS_MatchStatement.h>

namespace GSLanguageCompiler::AST {

    GS_MatchArm::GS_MatchArm(GSExpressionPtr pattern,
                             GSStatementPtrArray body)
            : _pattern(std::move(pattern)),
              _body(std::move(body)) {}

    GS_MatchArm GS_MatchArm::Create(GSExpressionPtr pattern,
                                    GSStatementPtrArray body) {
        return GS_MatchArm(std::move(pattern),
                           std::move(body));
    }

    GS_MatchArm GS_MatchArm::Create(GSExpressionPtr pattern) {
        return GS_MatchArm::Create(std::move(pattern),
                                   GSStatementPtrArray());
    }

    LRef<GSStatementPtr> GS_MatchArm::AddStatement(GSStatementPtr statement) {
        _body.emplace_back(std::move(statement));

        return _body[_body.size() - 1];
    }

    LRef<GSExpressionPtr> GS_MatchArm::GetPattern() {
        return _pattern;
    }

    LRef<GSStatementPtrArray> GS_MatchArm::GetBody() {
        return _body;
    }

    GS_MatchStatement::GS_MatchStatement(GSExpressionPtr expression,
                                         GSMatchArmArray arms)
            : _expression(std::move(expression)),
              _arms(std::move(arms)) {}

    std::shared_ptr<GS_MatchStatement> GS_MatchStatement::Create(GSExpressionPtr expression,
                                                                 GSMatchArmArray arms) {
        return std::make_shared<GS_MatchStatement>(std::move(expression),
                                                   std::move(arms));
    }

    std::shared_ptr<GS_MatchStatement> GS_MatchStatement::Create(GSExpressionPtr expression) {
        return GS_MatchStatement::Create(std::move(expression),
                                         GSMatchArmArray());
    }

    LRef<GS_MatchArm> GS_MatchStatement::AddArm(GS_MatchArm arm) {
        _arms.emplace_back(std::move(arm));

        return _arms[_arms.size() - 1];
    }

    LRef<GSExpressionPtr> GS_MatchStatement::GetExpression() {
        return _expression;
    }

    LRef<GSMatchArmArray> GS_MatchStatement::GetArms() {
        return _arms;
    }

    StatementType GS_MatchStatement::GetStatementType() const {
        return StatementType::MatchStatement;
    }

}
