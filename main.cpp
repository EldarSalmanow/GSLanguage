#include <Starter/GS_Starter.h>

//using namespace GSLanguageCompiler;
//
//class SymbolsTable {
//public:
//
//    std::map<GSString, Parser::GSValuePtr> nameToValue;
//};
//
//class Scope {
//public:
//
//    SymbolsTable symbolsTable;
//
//    std::vector<Scope> scopes;
//};

/**
 * Main function in GSLanguageCompiler
 * @param argc Arguments count
 * @param argv Arguments array
 * @return Status number for operation system
 */
GSInt main(GSInt argc, GSChar *argv[]) {
//    auto globalScope = std::make_shared<Scope>();
//
//    globalScope->symbolsTable.nameToValue["x"] = std::make_shared<Parser::GS_IntegerValue>(12);
//
//    globalScope->scopes.emplace_back(Scope());
//
//    globalScope->scopes[0].symbolsTable.nameToValue["y"] = std::make_shared<Parser::GS_StringValue>("Hello!");
//
    return Starter::GS_Starter::start(argc, argv);
}
