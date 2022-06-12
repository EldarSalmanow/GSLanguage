//#include <Driver/Driver.h>
//
//using namespace GSLanguageCompiler;
//
///**
// * Entry point for GSLanguageCompiler
// * @return Compiler result
// */
//I32 main(I32 argc, Ptr<Ptr<C>> argv) {
//    return Driver::GS_Compiler::Start(argc, argv);
//}

#include <rang.hpp>

#include <IO/IO.h>
#include <AST/AST.h>

using namespace GSLanguageCompiler;

//UString TTypeToString(Lexer::TokenType type) {
//    UString types[] = {
//#define GS_TOKENTYPE(type) #type
//#include <Lexer/GS_Keywords.def>
//    };
//
//    return types[StaticCast<I32>(type)];
//}

Void Error(UString error, AST::GSNodePtr node, UString code, IO::GSOutStreamPtr stream) {
    auto BeginPrintLine = [] (LRef<IO::GSOutStreamPtr> stream) {
        stream->GetOutStream() << rang::style::reset << rang::fg::reset << rang::style::bold << "|> "_us;
    };

    auto EndPrintLine = [] (LRef<IO::GSOutStreamPtr> stream) {
        stream->GetOutStream() << rang::style::reset << rang::fg::reset << std::endl;
    };

    auto nodeLocation = node->GetLocation();

    auto startTokenLocation = nodeLocation.GetStartLocation();
    auto endTokenLocation = nodeLocation.GetEndLocation();

    BeginPrintLine(stream);

    stream->GetOutStream() << rang::fg::red << "Error: " << error;

    EndPrintLine(stream);

    BeginPrintLine(stream);

    EndPrintLine(stream);

    BeginPrintLine(stream);

    stream->GetOutStream() << rang::fg::red << startTokenLocation.GetStartLocation().GetLine() << ": >> " << code;

    EndPrintLine(stream);

    BeginPrintLine(stream);

    stream->GetOutStream() << rang::fg::red;

    for (U64 i = 0; i < std::to_string(startTokenLocation.GetStartLocation().GetLine()).size() + 6; ++i) {
        stream->GetOutStream() << " ";
    }

    for (U64 i = 0; i < endTokenLocation.GetEndLocation().GetColumn(); ++i) {
        stream->GetOutStream() << " ";
    }

    stream->GetOutStream() << "^^^";

    EndPrintLine(stream);
}

Void StdError(UString error, AST::GSNodePtr node, UString code) {
    Error(std::move(error), std::move(node), std::move(code), IO::GS_OutConsoleStream::CreateCErr());
}

inline Void ColoursAndStyles() {
    rang::style styles[] = {
            rang::style::bold,
            rang::style::dim,
            rang::style::italic,
            rang::style::underline,
            rang::style::blink,
            rang::style::rblink,
            rang::style::reversed,
            rang::style::conceal,
            rang::style::crossed
    };

    rang::fg fgs[] = {
            rang::fg::black,
            rang::fg::red,
            rang::fg::green,
            rang::fg::yellow,
            rang::fg::blue,
            rang::fg::magenta,
            rang::fg::cyan,
            rang::fg::gray
    };

    for (auto &style : styles) {
        for (auto &fg : fgs) {
            std::cout << rang::style::reset << rang::fg::reset << style << fg << "Hello!" << rang::style::reset << rang::fg::reset << std::endl;
        }
    }
}

int main(int argc, char *argv[]) {
    AST::GSNodePtr node = std::make_shared<AST::GS_Node>(
            AST::GS_NodeLocation::Create(
                    Lexer::GS_TokenLocation::Create(IO::GS_SymbolLocation::Create("main.gs", 1, 1), IO::GS_SymbolLocation::Create("main.gs", 1, 3)),
                    Lexer::GS_TokenLocation::Create(IO::GS_SymbolLocation::Create("main.gs", 1, 14), IO::GS_SymbolLocation::Create("main.gs", 1, 15))));

    StdError("Unknown type!"_us, node, "var a: I32 = 10");

//    auto textStream = IO::GS_Reader::Create(IO::GS_InFileStream::CreateInFile(argv[1])).CreateStream();
//    auto tokenStream = Lexer::GS_Lexer::Create(textStream).CreateStream();
//
//    auto streamToken = tokenStream.CurrentToken();
//
//    Lexer::GSTokenArray tokens;
//
//    while (streamToken.GetType() != Lexer::TokenType::EndOfFile) {
//        tokens.emplace_back(streamToken);
//
//        tokenStream.NextToken();
//
//        streamToken = tokenStream.CurrentToken();
//    }
//
//    for (U64 i = 0; i < tokens.size(); ++i) {
//        auto token = tokens[i];
//
//        auto type = token.GetType();
//        auto value = token.GetValue();
//        auto location = token.GetLocation();
//
//        std::cout << "№" << i + 1 << std::endl <<
//                  "\tType: " << TTypeToString(type) << std::endl <<
//                  "\tValue: " << value << std::endl <<
//                  "\tLocation: " << location.GetStartLocation().GetSourceName() << " " << location.GetStartLocation().GetLine() << " " << location.GetStartLocation().GetColumn() << " " <<
//                  location.GetEndLocation().GetSourceName() << " " << location.GetEndLocation().GetLine() << " " << location.GetEndLocation().GetColumn() << std::endl;
//    }

    return 0;
}
