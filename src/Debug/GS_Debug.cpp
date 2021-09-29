#include <GS_Debug.h>

#include <Lexer/GS_Token.h>

#include <Parser/Nodes/GS_Node.h>
#include <Parser/Visitors/GS_PrintVisitor.h>

namespace Debug {

    GS_Debug::GS_Debug() = default;

    GSVoid GS_Debug::printMessage(const GSString &message) {
        std::cout << message << std::endl;
    }

    GSVoid GS_Debug::startReaderDebugMode(GSLanguageCompiler::Reader::GSText &text) {
        for (GSInt index = 0; index < text.size(); ++index) {
            std::cout << index + 1 << ": " << text[index];
        }
    }

    GSVoid GS_Debug::startLexerDebugMode(GSLanguageCompiler::Lexer::GSTokenArray &tokens) {
        for (auto &token : tokens) {
            std::cout << "Type: " << GSLanguageCompiler::Lexer::tokenTypeToString[token.getType()];

            if (!token.getValue().empty()) {
                std::cout << " Data: " << token.getValue();
            }

            std::cout << std::endl;
        }
    }

    GSVoid GS_Debug::startParserDebugMode(GSLanguageCompiler::Parser::GSNodePtr &root) {
        GSLanguageCompiler::Parser::GS_PrintVisitor visitor;

        root->accept(&visitor);
    }

    GSVoid GS_Debug::startOptimizerDebugMode(GSLanguageCompiler::Parser::GSNodePtr &optimizedRoot) {
        GSLanguageCompiler::Parser::GS_PrintVisitor visitor;

        optimizedRoot->accept(&visitor);
    }

}
