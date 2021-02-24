#include "../../../include/Compiler/Parser/GS_Parser.h"


namespace GSLanguageCompiler {

    std::vector<std::shared_ptr<GS_Expression>> GS_Parser::parse() {
        this->tokenIterator = this->tokens.begin();
        while (this->tokenIterator != tokens.end()) {
            this->analyzeToken();
            ++this->tokenIterator;
        }
        return this->expressions;
    }

    void GS_Parser::analyzeToken() {
        this->expressions.emplace_back(std::shared_ptr<GS_Expression>(this->higherOrder()));
    }

    GS_Expression *GS_Parser::higherOrder() {

        GS_Expression *expression = this->middleOrder();
        
        switch (this->tokenIterator[0].getType()) {
            case TokenType::TYPE_NUMBER:
                break;
//                return new GS_NumberExpression();
        }
        return expression;
    }

    GS_Expression *GS_Parser::middleOrder() {
        GS_Expression *expression = this->lowerOrder();
        return expression;
    }

    GS_Expression *GS_Parser::lowerOrder() {
        GS_Expression *expression;
        switch (this->tokenIterator[0].getType()) {
            case TokenType::TYPE_NUMBER:
                break;
            case TokenType::TYPE_STRING:
                break;
        }
        return expression;
    }

}