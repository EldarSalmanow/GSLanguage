#include <Lexer/Lexer.h>
#include <Parser/Parser.h>

#include <Debug/Debug.h>

#include <GS_Session.h>

namespace GSLanguageCompiler::Driver {

    class CompilationUnit {
    public:

        explicit CompilationUnit(IO::GSSourcePtr source)
                : _source(std::move(source)), _tokens(Lexer::GSTokenArray()), _node(AST::GSNodePtr()) {}

    public:

        static std::shared_ptr<CompilationUnit> Create(IO::GSSourcePtr source) {
            return std::make_shared<CompilationUnit>(std::move(source));
        }

    public:

        CompilingResult Compile() {
            auto lexer = Lexer::GS_Lexer::Create(_source);

            _tokens = lexer.Tokenize();

            auto parser = Parser::GS_Parser::Create(_tokens);

            _node = parser.ParseProgram();

            return CompilingResult::Success;
        }

    public:

        IO::GSSourcePtr GetSource() const {
            return _source;
        }

        Lexer::GSTokenArray GetTokens() const {
            return _tokens;
        }

        AST::GSNodePtr GetNode() const {
            return _node;
        }

    private:

        IO::GSSourcePtr _source;

        Lexer::GSTokenArray _tokens;

        AST::GSNodePtr _node;
    };

    using CompilationUnitPtr = std::shared_ptr<CompilationUnit>;

    using CompilationUnitPtrArray = std::vector<CompilationUnitPtr>;

    GS_Session::GS_Session(GSContextPtr context)
            : _context(std::move(context)) {}

    std::shared_ptr<GS_Session> GS_Session::Create(GSContextPtr context) {
        return std::make_shared<GS_Session>(std::move(context));
    }

    std::shared_ptr<GS_Session> GS_Session::Create() {
        return GS_Session::Create(GS_Context::Create());
    }

    CompilingResult GS_Session::Run() {
        // TODO

        CompilationUnitPtrArray compilationUnits;

        for (auto &source : source) {
            auto compilationUnit = CompilationUnit::Create(source);

            compilationUnit.Compile();

            Debug::DumpAST(compilationUnit.GetNode());

            compilationUnits.emplace_back(compilationUnit);
        }

//        AST::GSTranslationUnitDeclarationPtrArray units;
//
//        for (auto &inputSource : _context->GetInputSources()) {
//            auto source = inputSource->GetSource();
//
//            auto tokens = Lexer::GS_Lexer::Create(source, _context).Tokenize();
//
//            auto unit = Parser::GS_Parser::Create(tokens, _context).ParseProgram();
//
//            units.emplace_back(unit);
//
//            Debug::DumpAST(unit);
//        }

        return CompilingResult::Success;
    }

    GSContextPtr GS_Session::GetContext() const {
        return _context;
    }

    I32 Compile(ConstPtr<C> string) {
        auto unicodeString = UString(string);

        auto source = IO::GS_Source::CreateString(unicodeString);

        auto compilationUnit = CompilationUnit::Create(source);

        auto compilationResult = compilationUnit->Compile();

        if (compilationResult != CompilingResult::Success) {
            std::cout << "Can`t compile compilation unit!" << std::endl;
        }

        return StaticCast<I32>(compilationResult);
    }

    void f() {
        int res = Compile("func main() {}");
    }

}
