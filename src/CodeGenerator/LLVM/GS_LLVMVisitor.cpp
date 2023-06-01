#include <map>

#include <LLVM/GS_LLVMVisitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    // TODO update

//    class GS_LLVMTableOfSymbols {
//    public:
//
//        GS_LLVMTableOfSymbols();
//
//    public:
//
//        Void AddType(ConstLRef<Semantic::GSTypePtr> type,
//                     Ptr<llvm::Type> llvmType) {
//            _types.emplace(type, llvmType);
//        }
//
//        Ptr<llvm::Type> GetType(ConstLRef<Semantic::GSTypePtr> type) {
//            return _types[type];
//        }
//
//    private:
//
//        std::map<Semantic::GSTypePtr, Ptr<llvm::Type>> _types;
//    };
//
//    void f() {
//        AST::GS_ASTContext context;
//
//        llvm::LLVMContext llvmContext;
//        GS_LLVMTableOfSymbols tos;
//
//        tos.AddType(context.GetVoidType(),
//                    llvm::Type::getVoidTy(llvmContext));
//
//        tos.AddType(context.GetCharType(),
//                    llvm::Type::getInt8Ty(llvmContext));
//
//        tos.AddType(context.GetI8Type(),
//                    llvm::Type::getInt8Ty(llvmContext));
//        tos.AddType(context.GetI16Type(),
//                    llvm::Type::getInt16Ty(llvmContext));
//        tos.AddType(context.GetI32Type(),
//                    llvm::Type::getInt32Ty(llvmContext));
//        tos.AddType(context.GetI64Type(),
//                    llvm::Type::getInt64Ty(llvmContext));
//        tos.AddType(context.GetU8Type(),
//                    llvm::Type::getInt8Ty(llvmContext));
//        tos.AddType(context.GetU16Type(),
//                    llvm::Type::getInt16Ty(llvmContext));
//        tos.AddType(context.GetU32Type(),
//                    llvm::Type::getInt32Ty(llvmContext));
//        tos.AddType(context.GetU64Type(),
//                    llvm::Type::getInt64Ty(llvmContext));
//
//        tos.AddType(context.GetStringType(),
//                    llvm::Type::getInt8PtrTy(llvmContext));
//
//        auto ty = Semantic::GS_I32Type::Create();
//
//        tos.GetType(ty); // llvm i32 type
//    }
//
//    Ptr<llvm::Constant> ToLLVMConstant(AST::GSValuePtr value, LRef<llvm::LLVMContext> context, LRef<llvm::IRBuilder<>> builder) {
//        auto literalValue = AST::ToValue<AST::GS_LiteralValue>(value);
//
//        auto type = literalValue->GetType();
//
//        auto typeName = type->GetName();
//
//        Ptr<llvm::Type> llvmType;
//
//        if (typeName == "I32"_us) {
//            auto number = literalValue->GetValueWithCast<I32>();
//
//            return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), number);
//        } else if (typeName == "String"_us) {
//            auto string = literalValue->GetValueWithCast<UString>();
//
//            return builder.CreateGlobalStringPtr(string.AsUTF8());
//        }
//
//        return nullptr;
//    }

    std::map<UString, Ptr<llvm::Type>> LLVMTypes;
    std::map<UString, Ptr<llvm::AllocaInst>> Variables;

    GS_LLVMVisitor::GS_LLVMVisitor(LRef<GS_LLVMCodeHolder> codeHolder)
            : _codeHolder(codeHolder),
              _builder(_codeHolder.GetContext()) {
        LLVMTypes["Void"_us]   = llvm::Type::getVoidTy(GetContext());

        LLVMTypes["Char"_us]   = llvm::Type::getInt8Ty(GetContext());

        LLVMTypes["I8"_us]     = llvm::Type::getInt8Ty(GetContext());
        LLVMTypes["I16"_us]    = llvm::Type::getInt16Ty(GetContext());
        LLVMTypes["I32"_us]    = llvm::Type::getInt32Ty(GetContext());
        LLVMTypes["I64"_us]    = llvm::Type::getInt64Ty(GetContext());
        LLVMTypes["U8"_us]     = llvm::Type::getInt8Ty(GetContext());
        LLVMTypes["U16"_us]    = llvm::Type::getInt16Ty(GetContext());
        LLVMTypes["U32"_us]    = llvm::Type::getInt32Ty(GetContext());
        LLVMTypes["U64"_us]    = llvm::Type::getInt64Ty(GetContext());

        LLVMTypes["String"_us] = llvm::Type::getInt8PtrTy(GetContext());
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateNode(LRef<Driver::GS_Session> session,
                                                  LRef<AST::GSNodePtr> node) {
        if (node->IsDeclaration()) {
            auto declaration = AST::ToDeclaration(node);

            return GenerateDeclaration(session,
                                       declaration);
        }

        if (node->IsStatement()) {
            auto statement = AST::ToStatement(node);

            return GenerateStatement(session,
                                     statement);
        }

        if (node->IsExpression()) {
            auto expression = AST::ToExpression(node);

            return GenerateExpression(session,
                                      expression);
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateDeclaration(LRef<Driver::GS_Session> session,
                                                         LRef<AST::GSDeclarationPtr> declaration) {
        auto declarationType = declaration->GetDeclarationType();

        switch (declarationType) {
            case AST::DeclarationType::TranslationUnitDeclaration: {
                auto translationUnitDeclaration = AST::ToDeclaration<AST::GS_TranslationUnitDeclaration>(declaration);

                return GenerateTranslationUnitDeclaration(session,
                                                          translationUnitDeclaration);
            }
            case AST::DeclarationType::FunctionDeclaration: {
                auto functionDeclaration = AST::ToDeclaration<AST::GS_FunctionDeclaration>(declaration);

                return GenerateFunctionDeclaration(session,
                                                   functionDeclaration);
            }
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateStatement(LRef<Driver::GS_Session> session,
                                                       LRef<AST::GSStatementPtr> statement) {
        auto statementType = statement->GetStatementType();

        switch (statementType) {
            case AST::StatementType::VariableDeclarationStatement: {
                auto variableDeclarationStatement = AST::ToStatement<AST::GS_VariableDeclarationStatement>(statement);

                return GenerateVariableDeclarationStatement(session,
                                                            variableDeclarationStatement);
            }
            case AST::StatementType::AssignmentStatement: {
                auto assignmentStatement = AST::ToStatement<AST::GS_AssignmentStatement>(statement);

                return GenerateAssignmentStatement(session,
                                                   assignmentStatement);
            }
            case AST::StatementType::ExpressionStatement: {
                auto expressionStatement = AST::ToStatement<AST::GS_ExpressionStatement>(statement);

                return GenerateExpressionStatement(session,
                                                   expressionStatement);
            }
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateExpression(LRef<Driver::GS_Session> session,
                                                        LRef<AST::GSExpressionPtr> expression) {
        auto expressionType = expression->GetExpressionType();

        switch (expressionType) {
            case AST::ExpressionType::ConstantExpression: {
                auto constantExpression = AST::ToExpression<AST::GS_ConstantExpression>(expression);

                return GenerateConstantExpression(session,
                                                  constantExpression);
            }
            case AST::ExpressionType::UnaryExpression: {
                auto unaryExpression = AST::ToExpression<AST::GS_UnaryExpression>(expression);

                return GenerateUnaryExpression(session,
                                               unaryExpression);
            }
            case AST::ExpressionType::BinaryExpression: {
                auto binaryExpression = AST::ToExpression<AST::GS_BinaryExpression>(expression);

                return GenerateBinaryExpression(session,
                                                binaryExpression);
            }
            case AST::ExpressionType::ArrayExpression: {
                auto arrayExpression = AST::ToExpression<AST::GS_ArrayExpression>(expression);

                return GenerateArrayExpression(session,
                                               arrayExpression);
            }
            case AST::ExpressionType::VariableUsingExpression: {
                auto variableUsingExpression = AST::ToExpression<AST::GS_VariableUsingExpression>(expression);

                return GenerateVariableUsingExpression(session,
                                                       variableUsingExpression);
            }
            case AST::ExpressionType::FunctionCallingExpression: {
                auto functionCallingExpression = AST::ToExpression<AST::GS_FunctionCallingExpression>(expression);

                return GenerateFunctionCallingExpression(session,
                                                         functionCallingExpression);
            }
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateTranslationUnitDeclaration(LRef<Driver::GS_Session> session,
                                                                        AST::NodePtrLRef<AST::GS_TranslationUnitDeclaration> translationUnitDeclaration) {
        auto name = translationUnitDeclaration->GetName();
        auto nodes = translationUnitDeclaration->GetNodes();

        _codeHolder.CreateModule(name);

        for (auto &node : nodes) {
            GenerateNode(session,
                         node);
        }

        GetModule().print(llvm::outs(),
                          nullptr);

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateFunctionDeclaration(LRef<Driver::GS_Session> session,
                                                                 AST::NodePtrLRef<AST::GS_FunctionDeclaration> functionDeclaration) {
        auto name = functionDeclaration->GetName();
        auto signature = functionDeclaration->GetSignature();
        auto body = functionDeclaration->GetBody();

        auto paramTypes = signature.GetParamTypes();
        auto returnType = signature.GetReturnType();

        std::vector<Ptr<llvm::Type>> llvmParamTypes;

        for (auto &paramType : paramTypes) {
            auto llvmParamType = LLVMTypes[paramType->GetName()];

            llvmParamTypes.emplace_back(llvmParamType);
        }

        auto llvmReturnType = LLVMTypes[returnType->GetName()];

        auto llvmFunctionType = llvm::FunctionType::get(llvmReturnType,
                                                        llvmParamTypes,
                                                        false);

        auto llvmFunction = llvm::Function::Create(llvmFunctionType,
                                                   llvm::Function::LinkageTypes::ExternalLinkage,
                                                   name.AsUTF8(),
                                                   GetModule());

        auto block = llvm::BasicBlock::Create(GetContext(),
                                              "entry",
                                              llvmFunction);

        _builder.SetInsertPoint(block);

        for (auto &statement : body) {
            GenerateStatement(session,
                              statement);
        }

        _builder.CreateRetVoid();

        return llvmFunction;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                                                          AST::NodePtrLRef<AST::GS_VariableDeclarationStatement> variableDeclarationStatement) {
        auto name = variableDeclarationStatement->GetName();
        auto type = variableDeclarationStatement->GetType();
        auto expression = variableDeclarationStatement->GetExpression();

        auto llvmType = LLVMTypes[type->GetName()];

        auto llvmAllocaInstruction = _builder.CreateAlloca(llvmType);

        Variables[name] = llvmAllocaInstruction;

        return _builder.CreateStore(GenerateExpression(session,
                                                       expression),
                                    llvmAllocaInstruction);
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateAssignmentStatement(LRef<Driver::GS_Session> session,
                                                                 AST::NodePtrLRef<AST::GS_AssignmentStatement> assignmentStatement) {
        auto lvalueExpression = assignmentStatement->GetLValueExpression();
        auto rvalueExpression = assignmentStatement->GetRValueExpression();

        return _builder.CreateStore(GenerateExpression(session,
                                                       lvalueExpression),
                                    GenerateExpression(session,
                                                       rvalueExpression));
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateExpressionStatement(LRef<Driver::GS_Session> session,
                                                                 AST::NodePtrLRef<AST::GS_ExpressionStatement> expressionStatement) {
        auto expression = expressionStatement->GetExpression();

        return GenerateExpression(session,
                                  expression);
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateConstantExpression(LRef<Driver::GS_Session> session,
                                                                AST::NodePtrLRef<AST::GS_ConstantExpression> constantExpression) {
        auto value = constantExpression->GetValue();

        auto literalValue = AST::ToValue<AST::GS_LiteralValue>(value);

        auto type = literalValue->GetType();

        auto typeType = type->GetType();

        switch (typeType) {
            case Semantic::TypeType::Void:
                return nullptr;
            case Semantic::TypeType::Char: {
                auto symbol = literalValue->GetValueWithCast<USymbol>();

                return llvm::ConstantInt::get(LLVMTypes[type->GetName()],
                                              (I8) symbol.CodePoint());
            }
            case Semantic::TypeType::Integer: {
                auto integerValue = AST::ToValue<AST::GS_IntegerValue>(literalValue);

                auto integerType = integerValue->GetIntegerType();

                auto integerTypeType = integerType->GetIntegerType();

                switch (integerTypeType) {
                    case Semantic::IntegerType::I8: {
                        auto number = integerValue->GetValueWithCast<I8>();

                        return llvm::ConstantInt::get(LLVMTypes[type->GetName()],
                                                      number);
                    }
                    case Semantic::IntegerType::I16: {
                        auto number = integerValue->GetValueWithCast<I16>();

                        return llvm::ConstantInt::get(LLVMTypes[type->GetName()],
                                                      number);
                    }
                    case Semantic::IntegerType::I32: {
                        auto number = integerValue->GetValueWithCast<I32>();

                        return llvm::ConstantInt::get(LLVMTypes[type->GetName()],
                                                      number);
                    }
                    case Semantic::IntegerType::I64: {
                        auto number = integerValue->GetValueWithCast<I64>();

                        return llvm::ConstantInt::get(LLVMTypes[type->GetName()],
                                                      number);
                    }
                    case Semantic::IntegerType::User: {
                        return nullptr;
                    }
                }
            }
            case Semantic::TypeType::UInteger: {
                auto uIntegerValue = AST::ToValue<AST::GS_UIntegerValue>(literalValue);

                auto uIntegerType = uIntegerValue->GetUIntegerType();

                auto uIntegerTypeType = uIntegerType->GetUIntegerType();

                switch (uIntegerTypeType) {
                    case Semantic::UIntegerType::U8: {
                        auto number = uIntegerValue->GetValueWithCast<I8>();

                        return llvm::ConstantInt::get(LLVMTypes[type->GetName()],
                                                      number);
                    }
                    case Semantic::UIntegerType::U16: {
                        auto number = uIntegerValue->GetValueWithCast<I16>();

                        return llvm::ConstantInt::get(LLVMTypes[type->GetName()],
                                                      number);
                    }
                    case Semantic::UIntegerType::U32: {
                        auto number = uIntegerValue->GetValueWithCast<I32>();

                        return llvm::ConstantInt::get(LLVMTypes[type->GetName()],
                                                      number);
                    }
                    case Semantic::UIntegerType::U64: {
                        auto number = uIntegerValue->GetValueWithCast<I64>();

                        return llvm::ConstantInt::get(LLVMTypes[type->GetName()],
                                                      number);
                    }
                    case Semantic::UIntegerType::User: {
                        return nullptr;
                    }
                }
            }
            case Semantic::TypeType::String: {
                auto string = literalValue->GetValueWithCast<UString>();

                return _builder.CreateGlobalStringPtr(string.AsUTF8());
            }
            case Semantic::TypeType::Array: {
                return nullptr;
            }
            case Semantic::TypeType::User: {
                return nullptr;
            }
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateUnaryExpression(LRef<Driver::GS_Session> session,
                                                             AST::NodePtrLRef<AST::GS_UnaryExpression> unaryExpression) {
        auto operation = unaryExpression->GetUnaryOperation();
        auto expression = unaryExpression->GetExpression();

        switch (operation) {
            case AST::UnaryOperation::Minus:
                return _builder.CreateUnOp(llvm::Instruction::UnaryOps::FNeg,
                                           GenerateExpression(session,
                                                              expression));
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateBinaryExpression(LRef<Driver::GS_Session> session,
                                                              AST::NodePtrLRef<AST::GS_BinaryExpression> binaryExpression) {
        auto operation = binaryExpression->GetBinaryOperation();
        auto firstExpression = binaryExpression->GetFirstExpression();
        auto secondExpression = binaryExpression->GetSecondExpression();

        switch (operation) {
            case AST::BinaryOperation::Plus:
                return _builder.CreateAdd(GenerateExpression(session,
                                                             firstExpression),
                                          GenerateExpression(session,
                                                             secondExpression));
            case AST::BinaryOperation::Minus:
                return _builder.CreateSub(GenerateExpression(session,
                                                             firstExpression),
                                          GenerateExpression(session,
                                                             secondExpression));
            case AST::BinaryOperation::Star:
                return _builder.CreateMul(GenerateExpression(session,
                                                             firstExpression),
                                          GenerateExpression(session,
                                                             secondExpression));
            case AST::BinaryOperation::Slash:
                return _builder.CreateSDiv(GenerateExpression(session,
                                                              firstExpression),
                                           GenerateExpression(session,
                                                              secondExpression));
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateArrayExpression(LRef<Driver::GS_Session> session,
                                                             AST::NodePtrLRef<AST::GS_ArrayExpression> arrayExpression) {
        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateVariableUsingExpression(LRef<Driver::GS_Session> session,
                                                                     AST::NodePtrLRef<AST::GS_VariableUsingExpression> variableUsingExpression) {
        auto name = variableUsingExpression->GetName();

        auto llvmAllocaInstruction = Variables[name];

        return _builder.CreateLoad(llvmAllocaInstruction->getAllocatedType(),
                                   llvmAllocaInstruction,
                                   name.AsUTF8());
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateFunctionCallingExpression(LRef<Driver::GS_Session> session,
                                                                       AST::NodePtrLRef<AST::GS_FunctionCallingExpression> functionCallingExpression) {
        auto name = functionCallingExpression->GetName();

        auto llvmFunction = GetModule().getFunction(name.AsUTF8());

        return _builder.CreateCall(llvmFunction);
    }

    LRef<llvm::LLVMContext> GS_LLVMVisitor::GetContext() {
        return _codeHolder.GetContext();
    }

    LRef<llvm::Module> GS_LLVMVisitor::GetModule() {
        return _codeHolder.GetModule();
    }

}
