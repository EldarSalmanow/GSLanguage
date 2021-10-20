#include <Reader/GS_Reader.h>
#include <Lexer/GS_Lexer.h>
#include <Parser/GS_Parser.h>

using namespace GSLanguageCompiler;

Reader::GS_Code read(const String &filename) {
    IFStream stream;
    stream.open(filename);

    Reader::GS_Reader reader(std::move(stream));

    return reader.read();
}

Lexer::GSTokenArray tokenize(Reader::GS_Code code) {
    Lexer::GS_Lexer lexer(std::move(code));

    return lexer.tokenize();
}

AST::GSDeclarationPtrArray parse(Lexer::GS_TokenStream stream) {
    Parser::GS_Parser parser(stream);

    return parser.parse();
}

class GS_Pass {
public:

    explicit GS_Pass(AST::GS_Visitor *visitor)
            : _visitor(visitor) {}

public:

    virtual ~GS_Pass() = default;

public:

    virtual Void run(AST::GSDeclarationPtrArray &declarations) {}

protected:

    AST::GS_Visitor *_visitor;
};

class CalculateVariablesPass;

Void incrementVariablesNumberInPass(CalculateVariablesPass *pass);

class CalculateVariablesVisitor : public AST::GS_Visitor {
public:

    explicit CalculateVariablesVisitor(CalculateVariablesPass *pass)
            : _pass(pass) {}

public:

    Void visit(AST::GS_VariableDeclarationStatement *variableDeclarationStatement) override {
        incrementVariablesNumberInPass(_pass);
    }

protected:

    CalculateVariablesPass *_pass;
};

class CalculateVariablesPass : public GS_Pass {
public:

    CalculateVariablesPass()
            : GS_Pass(new CalculateVariablesVisitor(this)), _variablesNumber(0) {}

public:

    Void run(AST::GSDeclarationPtrArray &declarations) override {
        for (auto &declaration : declarations) {
            declaration->accept(_visitor);
        }

        std::cout << "Variables Number: " << _variablesNumber << std::endl;
    }

public:

    I32 _variablesNumber;
};

Void incrementVariablesNumberInPass(CalculateVariablesPass *pass) {
    ++pass->_variablesNumber;
}

class CalculateVariableUsingPass;

Void incrementVariableUsingNumberInPass(CalculateVariableUsingPass *pass);

class CalculateVariableUsingVisitor : public AST::GS_Visitor {
public:

    explicit CalculateVariableUsingVisitor(CalculateVariableUsingPass *pass)
            : _pass(pass) {}

public:

    Void visit(AST::GS_VariableUsingExpression *variableUsingExpression) override {
        incrementVariableUsingNumberInPass(_pass);
    }

protected:

    CalculateVariableUsingPass *_pass;
};

class CalculateVariableUsingPass : public GS_Pass {
public:

    CalculateVariableUsingPass()
            : GS_Pass(new CalculateVariableUsingVisitor(this)), _variableUsingNumber(0) {}

public:

    void run(AST::GSDeclarationPtrArray &declarations) override {
        for (auto &declaration : declarations) {
            declaration->accept(_visitor);
        }

        std::cout << "Variable Using Number: " << _variableUsingNumber << std::endl;
    }

public:

    I32 _variableUsingNumber;
};

Void incrementVariableUsingNumberInPass(CalculateVariableUsingPass *pass) {
    ++pass->_variableUsingNumber;
}

I32 main() {
    try {
        auto code = read("../test.gs");

        auto tokens = tokenize(code);

        auto tokenIterator = tokens.begin();

        auto tokenStream = Lexer::GS_TokenStream(tokenIterator);

        auto ast = parse(tokenStream);

        CalculateVariablesPass calculateVariablesPass;

        calculateVariablesPass.run(ast);

        CalculateVariableUsingPass calculateVariableUsingPass;

        calculateVariableUsingPass.run(ast);
    } catch (std::exception &exception) {
        std::cerr << exception.what() << std::endl;

        return 1;
    }

    return 0;
}

//#include <Starter/GS_Starter.h>

/**
 * Main function in GSLanguageCompiler
 * @param argc Arguments count
 * @param argv Arguments array
 * @return Status number for operation system
 */
//GSInt main(GSInt argc, GSChar *argv[]) {
//    return Starter::GS_Starter::start(argc, argv);
//}
