//#include <rapidjson/rapidjson.h> TODO test converting AST to JSON

#include <llvm/IR/LegacyPassManager.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#include <IO/IO.h>
#include <Lexer/Lexer.h>
#include <Parser/Parser.h>
#include <AST/AST.h>
#include <Optimizer/Optimizer.h>
#include <Semantic/Semantic.h>
#include <CodeGenerator/CodeGenerator.h>
#include <Debug/Debug.h>

#include <GS_TranslationUnit.h>

namespace GSLanguageCompiler::Driver {

    class TypeCheckVisitor : public AST::GS_Visitor {
    public:

        explicit TypeCheckVisitor(Semantic::GSTableOfSymbolsPtr tableOfSymbols)
                : _tableOfSymbols(std::move(tableOfSymbols)) {}

    public:

        Void VisitVariableDeclarationStatement(LRef<std::shared_ptr<AST::GS_VariableDeclarationStatement>> variableDeclarationStatement) override {
            auto type = variableDeclarationStatement->GetType();
            auto expression = variableDeclarationStatement->GetExpression();

            auto calculatedExpressionType = CalculateType(expression);

            auto typeName = type->GetName();
            auto calculatedExpressionTypeName = calculatedExpressionType->GetName();

            if (typeName != calculatedExpressionTypeName) {
                std::cout << typeName << " != "_us << calculatedExpressionTypeName << std::endl;
            }
        }

    public:

        Semantic::GSTypePtr CalculateType(LRef<AST::GSExpressionPtr> expression) {
            if (auto constantExpression = AST::ToExpression<AST::GS_ConstantExpression>(expression)) {
                return CalculateType(constantExpression);
            }

            if (auto unaryExpression = AST::ToExpression<AST::GS_UnaryExpression>(expression)) {
                return CalculateType(unaryExpression);
            }

            if (auto binaryExpression = AST::ToExpression<AST::GS_BinaryExpression>(expression)) {
                return CalculateType(binaryExpression);
            }

            if (auto variableUsingExpression = AST::ToExpression<AST::GS_VariableUsingExpression>(expression)) {
                return CalculateType(variableUsingExpression);
            }

            if (auto functionCallingExpression = AST::ToExpression<AST::GS_FunctionCallingExpression>(expression)) {
                return CalculateType(functionCallingExpression);
            }

            return nullptr;
        }

        Semantic::GSTypePtr CalculateType(std::shared_ptr<AST::GS_ConstantExpression> constantExpression) {
            auto value = constantExpression->GetValue();

            auto valueType = value->GetType();

            return valueType;
        }

        Semantic::GSTypePtr CalculateType(std::shared_ptr<AST::GS_UnaryExpression> unaryExpression) {
            auto expression = unaryExpression->GetExpression();

            return CalculateType(expression);
        }

        Semantic::GSTypePtr CalculateType(std::shared_ptr<AST::GS_BinaryExpression> binaryExpression) {
            auto firstExpression = binaryExpression->GetFirstExpression();
            auto secondExpression = binaryExpression->GetSecondExpression();

            auto firstExpressionType = CalculateType(firstExpression);
            auto secondExpressionType = CalculateType(secondExpression);

            if (firstExpressionType->GetName() == secondExpressionType->GetName()) {
                return firstExpressionType;
            }

            return nullptr;
        }

        Semantic::GSTypePtr CalculateType(std::shared_ptr<AST::GS_VariableUsingExpression> variableUsingExpression) {
            auto name = variableUsingExpression->GetName();

            if (auto variable = _tableOfSymbols->FindVariable(name)) {
                auto variableType = variable->GetType();

                return variableType;
            }

            return nullptr;
        }

        Semantic::GSTypePtr CalculateType(std::shared_ptr<AST::GS_FunctionCallingExpression> functionCallingExpression) {
            return nullptr;
        }

    private:

        Semantic::GSTableOfSymbolsPtr _tableOfSymbols;
    };

    class TypeCheckPass : public AST::GS_Pass {
    public:

        explicit TypeCheckPass(Semantic::GSTableOfSymbolsPtr tableOfSymbols)
                : _tableOfSymbols(std::move(tableOfSymbols)) {}

    public:

        Void Run(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration) override {
            TypeCheckVisitor visitor(_tableOfSymbols);

            visitor.VisitTranslationUnitDeclaration(translationUnitDeclaration);
        }

    private:

        Semantic::GSTableOfSymbolsPtr _tableOfSymbols;
    };

    AST::GSPassPtr CreateTypeCheckPass(Semantic::GSTableOfSymbolsPtr tableOfSymbols) {
        return std::make_shared<TypeCheckPass>(std::move(tableOfSymbols));
    }

    class Mangler {
    public:

        virtual ~Mangler() = default;

    public:

        virtual UString MangleUnitName(UString name) = 0;

        virtual UString MangleFunctionName(UString name) = 0;
    };

    class ABI {
    public:

        virtual ~ABI() = default;

    public:

        virtual std::shared_ptr<Mangler> GetMangler() = 0;
    };

    class GS_Mangler : public Mangler {
    public:

        static std::shared_ptr<GS_Mangler> Create() {
            return std::make_shared<GS_Mangler>();
        }

    public:

        /**
         * _GS_U + name size + name
         * ex: main -> _GS_U4main
         */
        UString MangleUnitName(UString name) override {
            return UString("_GS_U" + std::to_string(name.Size()) + name.AsUTF8());
        }

        /**
         * _GS_F + name size + name
         * ex: main -> _GS_F4main
         */
        UString MangleFunctionName(UString name) override {
            return UString("_GS_F" + std::to_string(name.Size()) + name.AsUTF8());
        }
    };

    class GS_ABI : public ABI {
    public:

        static std::shared_ptr<GS_ABI> Create() {
            return std::make_shared<GS_ABI>();
        }

    public:

        std::shared_ptr<Mangler> GetMangler() override {
            return GS_Mangler::Create();
        }
    };

    class MangleVisitor : public AST::GS_Visitor {
    public:

        explicit MangleVisitor(std::shared_ptr<Mangler> mangler)
                : _mangler(std::move(mangler)) {}

    public:

        Void VisitTranslationUnitDeclaration(LRef<std::shared_ptr<AST::GS_TranslationUnitDeclaration>> translationUnitDeclaration) override {
            AST::GS_Visitor::VisitTranslationUnitDeclaration(translationUnitDeclaration);

            auto &name = translationUnitDeclaration->GetName();

            name = _mangler->MangleUnitName(name);
        }

        Void VisitFunctionDeclaration(LRef<std::shared_ptr<AST::GS_FunctionDeclaration>> functionDeclaration) override {
            AST::GS_Visitor::VisitFunctionDeclaration(functionDeclaration);

            auto &name = functionDeclaration->GetName();

            name = _mangler->MangleFunctionName(name);
        }

    private:

        std::shared_ptr<Mangler> _mangler;
    };

    class ManglePass : public AST::GS_Pass {
    public:

        explicit ManglePass(std::shared_ptr<Mangler> mangler)
                : _mangler(std::move(mangler)) {}

    public:

        Void Run(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration) override {
            MangleVisitor visitor(_mangler);

            visitor.VisitTranslationUnitDeclaration(translationUnitDeclaration);
        }

    private:

        std::shared_ptr<Mangler> _mangler;
    };

    AST::GSPassPtr CreateManglePass(std::shared_ptr<Mangler> mangler) {
        return std::make_shared<ManglePass>(mangler);
    }

    GS_TranslationUnit::GS_TranslationUnit(GSTranslationUnitConfigPtr config)
            : _config(std::move(config)) {}

    std::shared_ptr<GS_TranslationUnit> GS_TranslationUnit::Create(GSTranslationUnitConfigPtr config) {
        return std::make_shared<GS_TranslationUnit>(std::move(config));
    }

    Bool Write(UString outputName, CodeGenerator::GSCGContextPtr context) {
        switch (context->GetBackend()) {
            case CodeGenerator::CGBackend::LLVM: {
                auto llvmCodeGenerationContext = std::reinterpret_pointer_cast<CodeGenerator::GS_LLVMCGContext>(std::move(context));

                auto &module = llvmCodeGenerationContext->GetModule();

                module.print(llvm::errs(), nullptr);

                auto targetTriple = llvm::sys::getDefaultTargetTriple();

                llvm::InitializeNativeTarget();
                llvm::InitializeNativeTargetAsmParser();
                llvm::InitializeNativeTargetAsmPrinter();

                std::string error;

                auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);

                if (!target) {
                    llvm::errs() << error;

                    return false;
                }

                auto cpu = "generic";
                auto features = "";

                llvm::TargetOptions options;

                auto model = llvm::Optional<llvm::Reloc::Model>();

                auto machine = target->createTargetMachine(targetTriple, cpu, features, options, model);

                module.setDataLayout(machine->createDataLayout());
                module.setTargetTriple(targetTriple);

                std::error_code errorCode;

                llvm::raw_fd_ostream stream(outputName.AsUTF8(), errorCode);

                if (errorCode) {
                    llvm::errs() << errorCode.message();

                    return false;
                }

                llvm::legacy::PassManager manager;

                if (machine->addPassesToEmitFile(manager, stream, nullptr, llvm::CodeGenFileType::CGFT_ObjectFile)) {
                    return false;
                }

                manager.run(module);

                stream.flush();

                return true;
            }
        }

        return false;
    }

    enum class SourceNameType {
        File,
        String
    };

    class SourceName {
    public:

        SourceName(UString name, SourceNameType type)
                : _name(std::move(name)), _type(type), _hash(0) {
            std::hash<std::string> hasher;

            _hash = hasher(_name.AsUTF8());
        }

    public:

        static SourceName Create(UString name, SourceNameType type) {
            return SourceName(std::move(name), type);
        }

        static SourceName CreateFile(UString name) {
            return SourceName::Create(std::move(name), SourceNameType::File);
        }

        static SourceName CreateString() {
            return SourceName::Create("<string>", SourceNameType::String);
        }

    public:

        UString GetName() const {
            return _name;
        }

        SourceNameType GetType() const {
            return _type;
        }

        U64 GetHash() const {
            return _hash;
        }

    public:

        Bool operator==(ConstLRef<SourceName> name) const {
            return _hash == name.GetHash();
        }

        Bool operator!=(ConstLRef<SourceName> name) const {
            return !(*this == name);
        }

    private:

        UString _name;

        SourceNameType _type;

        U64 _hash;
    };

    class Source {
    public:

        Source(UString source, SourceName name)
                : _source(std::move(source)), _name(std::move(name)), _hash(0) {
            std::hash<std::string> hasher;

            _hash = hasher(_source.AsUTF8());

            _hash ^= _name.GetHash();
        }

    public:

        static std::shared_ptr<Source> Create(UString source, SourceName name) {
            return std::make_shared<Source>(std::move(source), std::move(name));
        }

        static std::shared_ptr<Source> CreateFile(SourceName name) {
            return Source::Create(IO::GS_Reader::Create(IO::GS_InFileStream::CreateInFile(name.GetName())).Read(), std::move(name));
        }

        static std::shared_ptr<Source> CreateString(UString source) {
            return Source::Create(std::move(source), SourceName::CreateString());
        }

    public:

        UString GetSource() const {
            return _source;
        }

        SourceName GetName() const {
            return _name;
        }

        U64 GetHash() const {
            return _hash;
        }

    public:

        Bool operator==(ConstLRef<Source> source) const {
            return _hash == source.GetHash();
        }

        Bool operator!=(ConstLRef<Source> source) const {
            return !(*this == source);
        }

    private:

        UString _source;

        SourceName _name;

        U64 _hash;
    };

    using SourcePtr = std::shared_ptr<Source>;

    using SourcePtrArray = std::vector<SourcePtr>;

    class SourceManager {
    public:

        explicit SourceManager(SourcePtrArray sources)
                : _sources(std::move(sources)) {}

    public:

        static std::shared_ptr<SourceManager> Create(SourcePtrArray sources) {
            return std::make_shared<SourceManager>(std::move(sources));
        }

        static std::shared_ptr<SourceManager> Create() {
            return SourceManager::Create(SourcePtrArray());
        }

    public:

        Bool AddSource(SourcePtr source) {
            for (auto &source_ : _sources) {
                if (source_ == source) {
                    return false;
                }
            }

            _sources.emplace_back(std::move(source));

            return true;
        }

        // TODO
        SourcePtr GetSource(U64 hash) const {
            for (auto &source : _sources) {
                if (source->GetHash() == hash) {
                    return source;
                }
            }

            return nullptr;
        }

    public:

        SourcePtrArray GetSources() const {
            return _sources;
        }

    private:

        SourcePtrArray _sources;
    };

    void f() {
        auto SM = SourceManager::Create();

        SM->AddSource(Source::CreateString("func main() { println(\"Hello, World!\") }"));
    }

    CompilingResult GS_TranslationUnit::Compile() {
        auto fileStream = IO::GS_InFileStream::CreateInFile(_config->GetInputName());

        auto content = IO::GS_Reader::Create(std::move(fileStream)).Read();

        auto tokens = Lexer::GS_Lexer::Create(content).Tokenize();

        auto unit = Parser::GS_Parser::Create(tokens, AST::GS_ASTContext::Create()).ParseProgram();

        if (!unit) {
            return CompilingResult::Failure;
        }

//        auto Optimizer = Optimizer::GS_Optimizer::Create();
//
//        Optimizer->Optimize(unit);

        Debug::DumpAST(unit);

//        auto codeGenerator = CodeGenerator::GS_CodeGenerator::CreateLLVMCG();
//
//        codeGenerator->Generate(unit);
//
//        auto codeGenerationContext = codeGenerator->GetContext();
//
//        if (!Write(_config->GetInputName() + ".o"_us, codeGenerationContext)) {
//            return CompilingResult::Failure;
//        }

        return CompilingResult::Success;
    }

    GSTranslationUnitConfigPtr GS_TranslationUnit::GetConfig() const {
        return _config;
    }

}
