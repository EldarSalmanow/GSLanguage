#ifndef GSLANGUAGE_GS_DEBUG_H
#define GSLANGUAGE_GS_DEBUG_H

#include <memory>
#include <iostream>

#include <CrossPlatform/GS_PlatformTypes.h>

namespace GSLanguageCompiler {

    namespace Reader {

        typedef std::vector<GSString> GSText;

    }

    namespace Lexer {

        class GS_Token;

        typedef std::vector<GS_Token> GSTokenArray;

    }

    namespace Parser {

        class GS_Node;

        typedef std::shared_ptr<GS_Node> GSNodePtr;

    }

}

namespace Debug {

    /**
     * Class for debugging and testing input and output compilation parameters GSLanguageCompiler
     */
    class GS_Debug {
    public:

        GS_Debug();

    public:

        /**
         *
         * @param message
         * @return
         */
        GSVoid printMessage(const GSString &message);

        /**
         *
         * @param text
         * @return
         */
        GSVoid startReaderDebugMode(GSLanguageCompiler::Reader::GSText &text);

        /**
         *
         * @param tokens
         * @return
         */
        GSVoid startLexerDebugMode(GSLanguageCompiler::Lexer::GSTokenArray &tokens);

        /**
         *
         * @param root
         * @return
         */
        GSVoid startParserDebugMode(GSLanguageCompiler::Parser::GSNodePtr &root);

        /**
         *
         * @param optimizedRoot
         * @return
         */
        GSVoid startOptimizerDebugMode(GSLanguageCompiler::Parser::GSNodePtr &optimizedRoot);
    };

}

#endif //GSLANGUAGE_GS_DEBUG_H
