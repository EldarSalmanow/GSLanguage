#include <LLVM/GS_LLVMVisitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_LLVMVisitor::GS_LLVMVisitor(LRef<GS_LLVMCodeHolder> codeHolder)
            : _codeHolder(codeHolder),
              _builder(_codeHolder.GetContext()) {
        _types["Void"] = llvm::Type::getVoidTy(GetContext());
        _types["Bool"] = llvm::Type::getInt8Ty(GetContext());
        _types["Char"] = llvm::Type::getInt8Ty(GetContext());
        _types["I8"] = llvm::Type::getInt8Ty(GetContext());
        _types["I16"] = llvm::Type::getInt16Ty(GetContext());
        _types["I32"] = llvm::Type::getInt32Ty(GetContext());
        _types["I64"] = llvm::Type::getInt64Ty(GetContext());
        _types["U8"] = llvm::Type::getInt8Ty(GetContext());
        _types["U16"] = llvm::Type::getInt16Ty(GetContext());
        _types["U32"] = llvm::Type::getInt32Ty(GetContext());
        _types["U64"] = llvm::Type::getInt64Ty(GetContext());
        _types["String"] = llvm::Type::getInt8PtrTy(GetContext());
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
            case AST::DeclarationType::ModuleDeclaration: {
                auto moduleDeclaration = AST::ToDeclaration<AST::GS_ModuleDeclaration>(declaration);

                return GenerateModuleDeclaration(session,
                                                 moduleDeclaration);
            }
            case AST::DeclarationType::ImportDeclaration: {
                auto importDeclaration = AST::ToDeclaration<AST::GS_ImportDeclaration>(declaration);

                return GenerateImportDeclaration(session,
                                                 importDeclaration);
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
            case AST::StatementType::IfStatement: {
                auto ifStatement = AST::ToStatement<AST::GS_IfStatement>(statement);

                return GenerateIfStatement(session,
                                           ifStatement);
            }
            case AST::StatementType::ForStatement: {
                auto forStatement = AST::ToStatement<AST::GS_ForStatement>(statement);

                return GenerateForStatement(session,
                                            forStatement);
            }
            case AST::StatementType::WhileStatement: {
                auto whileStatement = AST::ToStatement<AST::GS_WhileStatement>(statement);

                return GenerateWhileStatement(session,
                                              whileStatement);
            }
            case AST::StatementType::MatchStatement: {
                auto matchStatement = AST::ToStatement<AST::GS_MatchStatement>(statement);

                return GenerateMatchStatement(session,
                                              matchStatement);
            }
            case AST::StatementType::ReturnStatement: {
                auto returnStatement = AST::ToStatement<AST::GS_ReturnStatement>(statement);

                return GenerateReturnStatement(session,
                                               returnStatement);
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
            case AST::ExpressionType::LiteralExpression: {
                auto literalExpression = AST::ToExpression<AST::GS_LiteralExpression>(expression);

                return GenerateLiteralExpression(session,
                                                 literalExpression);
            }
            case AST::ExpressionType::ArrayExpression: {
                auto arrayExpression = AST::ToExpression<AST::GS_ArrayExpression>(expression);

                return GenerateArrayExpression(session,
                                               arrayExpression);
            }
            case AST::ExpressionType::RangeExpression: {
                auto rangeExpression = AST::ToExpression<AST::GS_RangeExpression>(expression);

                return GenerateRangeExpression(session,
                                               rangeExpression);
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
            case AST::ExpressionType::IndexExpression: {
                auto indexExpression = AST::ToExpression<AST::GS_IndexExpression>(expression);

                return GenerateIndexExpression(session,
                                               indexExpression);
            }
            case AST::ExpressionType::CastExpression: {
                auto castExpression = AST::ToExpression<AST::GS_CastExpression>(expression);

                return GenerateCastExpression(session,
                                              castExpression);
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

    // this node may be desugared
    Ptr<llvm::Value> GS_LLVMVisitor::GenerateModuleDeclaration(LRef<Driver::GS_Session> session,
                                                               AST::NodePtrLRef<AST::GS_ModuleDeclaration> moduleDeclaration) {
        return nullptr;
    }

    // this node may be desugared
    Ptr<llvm::Value> GS_LLVMVisitor::GenerateImportDeclaration(LRef<Driver::GS_Session> session,
                                                               AST::NodePtrLRef<AST::GS_ImportDeclaration> importDeclaration) {
        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateFunctionDeclaration(LRef<Driver::GS_Session> session,
                                                                 AST::NodePtrLRef<AST::GS_FunctionDeclaration> functionDeclaration) {
        auto name = functionDeclaration->GetName();
        auto signature = functionDeclaration->GetSignature();
        auto body = functionDeclaration->GetBody();

        auto params = signature.GetParams();
        auto returnType = signature.GetReturnType();
        auto qualifiers = signature.GetQualifiers();

        std::vector<Ptr<llvm::Type>> llvmParamTypes;

        for (auto &param : params) {
            auto paramType = param.GetType();

            auto llvmParamType = _types[paramType->GetName()];

            llvmParamTypes.emplace_back(llvmParamType);
        }

        Ptr<llvm::Type> llvmReturnType;

        if (!returnType) {
            llvmReturnType = llvm::Type::getVoidTy(GetContext());
        } else {
            llvmReturnType = _types[returnType->GetName()];
        }

        auto llvmFunctionType = llvm::FunctionType::get(llvmReturnType,
                                                        llvmParamTypes,
                                                        false);

        auto llvmFunction = llvm::Function::Create(llvmFunctionType,
                                                   llvm::Function::LinkageTypes::ExternalLinkage,
                                                   name.AsUTF8(),
                                                   GetModule());

        _functions[name] = llvmFunction;

        U64 index = 0;
        for (auto &argument : llvmFunction->args()) {
            argument.setName(params[index].GetName().AsUTF8());

            ++index;
        }

        if (qualifiers.IsExtern()) {
            return llvmFunction;
        }

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

        auto llvmAllocaInstruction = _builder.CreateAlloca(_types[type->GetName()]);

        _variables[name] = llvmAllocaInstruction;

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

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateIfStatement(LRef<Driver::GS_Session> session,
                                                         AST::NodePtrLRef<AST::GS_IfStatement> ifStatement) {
        auto condition = ifStatement->GetCondition();
        auto ifBody = ifStatement->GetIfBody();
        auto elseBody = ifStatement->GetElseBody();

        auto llvmCondition = GenerateExpression(session,
                                                condition);

        auto llvmFunction = _builder.GetInsertBlock()->getParent();

        auto ifBranch = llvm::BasicBlock::Create(GetContext(),
                                                 "if_branch",
                                                 llvmFunction);
        auto elseBranch = llvm::BasicBlock::Create(GetContext(),
                                                   "else_branch");
        auto exitBranch = llvm::BasicBlock::Create(GetContext(),
                                                   "exit_branch");

        _builder.CreateCondBr(llvmCondition, ifBranch, elseBranch);

        _builder.SetInsertPoint(ifBranch);

        for (auto &statement : ifBody) {
            GenerateStatement(session,
                              statement);
        }

        _builder.CreateBr(exitBranch);

        ifBranch = _builder.GetInsertBlock();

        _builder.SetInsertPoint(elseBranch);

        for (auto &statement : elseBody) {
            GenerateStatement(session,
                              statement);
        }

        _builder.CreateBr(exitBranch);

        elseBranch = _builder.GetInsertBlock();

        _builder.SetInsertPoint(exitBranch);

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateForStatement(LRef<Driver::GS_Session> session,
                                                          AST::NodePtrLRef<AST::GS_ForStatement> forStatement) {
        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateWhileStatement(LRef<Driver::GS_Session> session,
                                                            std::shared_ptr<GSLanguageCompiler::AST::GS_WhileStatement> &whileStatement) {
        auto condition = whileStatement->GetCondition();
        auto body = whileStatement->GetBody();

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateMatchStatement(LRef<Driver::GS_Session> session,
                                                            std::shared_ptr<GSLanguageCompiler::AST::GS_MatchStatement> &matchStatement) {
        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateReturnStatement(LRef<Driver::GS_Session> session,
                                                             std::shared_ptr<GSLanguageCompiler::AST::GS_ReturnStatement> &returnStatement) {
        auto expression = returnStatement->GetExpression();

        if (expression) {
            return _builder.CreateRet(GenerateExpression(session,
                                                         expression));
        } else {
            return _builder.CreateRetVoid();
        }
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateExpressionStatement(LRef<Driver::GS_Session> session,
                                                                 AST::NodePtrLRef<AST::GS_ExpressionStatement> expressionStatement) {
        auto expression = expressionStatement->GetExpression();

        return GenerateExpression(session,
                                  expression);
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateLiteralExpression(LRef<Driver::GS_Session> session,
                                                               AST::NodePtrLRef<AST::GS_LiteralExpression> literalExpression) {
        auto value = literalExpression->GetValue();

        auto literalValue = AST::ToValue<AST::GS_LiteralValue>(value);

        auto type = literalValue->GetType();

        auto typeType = type->GetType();

        switch (typeType) {
            case Semantic::TypeType::Void:
                return nullptr;
            case Semantic::TypeType::Bool: {
                auto boolValue = literalValue->GetValueWithCast<Bool>();

                return llvm::ConstantInt::get(_types[type->GetName()],
                                              boolValue ? 1 : 0);
            }
            case Semantic::TypeType::Char: {
                auto symbol = literalValue->GetValueWithCast<USymbol>();

                return llvm::ConstantInt::get(_types[type->GetName()],
                                              (I8) symbol.CodePoint());
            }
            case Semantic::TypeType::Integer: {
                auto integerValue = AST::ToValue<AST::GS_IntegerValue>(literalValue);

                auto integerType = integerValue->GetIntegerType();

                auto integerTypeType = integerType->GetIntegerType();

                switch (integerTypeType) {
                    case Semantic::IntegerType::I8: {
                        auto number = integerValue->GetValueWithCast<I8>();

                        return llvm::ConstantInt::get(_types[type->GetName()],
                                                      number);
                    }
                    case Semantic::IntegerType::I16: {
                        auto number = integerValue->GetValueWithCast<I16>();

                        return llvm::ConstantInt::get(_types[type->GetName()],
                                                      number);
                    }
                    case Semantic::IntegerType::I32: {
                        auto number = integerValue->GetValueWithCast<I32>();

                        return llvm::ConstantInt::get(_types[type->GetName()],
                                                      number);
                    }
                    case Semantic::IntegerType::I64: {
                        auto number = integerValue->GetValueWithCast<I64>();

                        return llvm::ConstantInt::get(_types[type->GetName()],
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

                        return llvm::ConstantInt::get(_types[type->GetName()],
                                                      number);
                    }
                    case Semantic::UIntegerType::U16: {
                        auto number = uIntegerValue->GetValueWithCast<I16>();

                        return llvm::ConstantInt::get(_types[type->GetName()],
                                                      number);
                    }
                    case Semantic::UIntegerType::U32: {
                        auto number = uIntegerValue->GetValueWithCast<I32>();

                        return llvm::ConstantInt::get(_types[type->GetName()],
                                                      number);
                    }
                    case Semantic::UIntegerType::U64: {
                        auto number = uIntegerValue->GetValueWithCast<I64>();

                        return llvm::ConstantInt::get(_types[type->GetName()],
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

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateArrayExpression(LRef<Driver::GS_Session> session,
                                                             AST::NodePtrLRef<AST::GS_ArrayExpression> arrayExpression) {
        auto expressions = arrayExpression->GetExpressions();

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateRangeExpression(LRef<Driver::GS_Session> session,
                                                             AST::NodePtrLRef<AST::GS_RangeExpression> rangeExpression) {
        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateUnaryExpression(LRef<Driver::GS_Session> session,
                                                             AST::NodePtrLRef<AST::GS_UnaryExpression> unaryExpression) {
        auto operation = unaryExpression->GetUnaryOperation();
        auto expression = unaryExpression->GetExpression();

        switch (operation) {
            case AST::UnaryOperation::Neg:
                return _builder.CreateFNeg(GenerateExpression(session,
                                                              expression));
            case AST::UnaryOperation::Not:
                return _builder.CreateNot(GenerateExpression(session,
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
            case AST::BinaryOperation::Add:
                return _builder.CreateAdd(GenerateExpression(session,
                                                             firstExpression),
                                          GenerateExpression(session,
                                                             secondExpression));
            case AST::BinaryOperation::Sub:
                return _builder.CreateSub(GenerateExpression(session,
                                                             firstExpression),
                                          GenerateExpression(session,
                                                             secondExpression));
            case AST::BinaryOperation::Mul:
                return _builder.CreateMul(GenerateExpression(session,
                                                             firstExpression),
                                          GenerateExpression(session,
                                                             secondExpression));
            case AST::BinaryOperation::Div:
                return _builder.CreateSDiv(GenerateExpression(session,
                                                              firstExpression),
                                           GenerateExpression(session,
                                                              secondExpression));
            case AST::BinaryOperation::Rem:
                return _builder.CreateSRem(GenerateExpression(session,
                                                              firstExpression),
                                           GenerateExpression(session,
                                                              secondExpression));

            case AST::BinaryOperation::And:
            case AST::BinaryOperation::Or:
                return nullptr;

            case AST::BinaryOperation::BitXor:
                return _builder.CreateXor(GenerateExpression(session,
                                                             firstExpression),
                                          GenerateExpression(session,
                                                             secondExpression));
            case AST::BinaryOperation::BitAnd:
                return _builder.CreateAnd(GenerateExpression(session,
                                                             firstExpression),
                                          GenerateExpression(session,
                                                             secondExpression));
            case AST::BinaryOperation::BitOr:
                return _builder.CreateOr(GenerateExpression(session,
                                                            firstExpression),
                                         GenerateExpression(session,
                                                            secondExpression));
            case AST::BinaryOperation::Shl:
                return _builder.CreateShl(GenerateExpression(session,
                                                             firstExpression),
                                          GenerateExpression(session,
                                                             secondExpression));
            case AST::BinaryOperation::Shr:
                return _builder.CreateAShr(GenerateExpression(session,
                                                              firstExpression),
                                           GenerateExpression(session,
                                                              secondExpression));

            case AST::BinaryOperation::Eq:
                return _builder.CreateICmpEQ(GenerateExpression(session,
                                                                firstExpression),
                                             GenerateExpression(session,
                                                                secondExpression));
            case AST::BinaryOperation::Ne:
                return _builder.CreateICmpNE(GenerateExpression(session,
                                                                firstExpression),
                                             GenerateExpression(session,
                                                                secondExpression));
            case AST::BinaryOperation::Gt:
                return _builder.CreateICmpSGT(GenerateExpression(session,
                                                                 firstExpression),
                                              GenerateExpression(session,
                                                                 secondExpression));
            case AST::BinaryOperation::Ge:
                return _builder.CreateICmpSGE(GenerateExpression(session,
                                                                 firstExpression),
                                              GenerateExpression(session,
                                                                 secondExpression));
            case AST::BinaryOperation::Lt:
                return _builder.CreateICmpSLT(GenerateExpression(session,
                                                                 firstExpression),
                                              GenerateExpression(session,
                                                                 secondExpression));
            case AST::BinaryOperation::Le:
                return _builder.CreateICmpSLE(GenerateExpression(session,
                                                                 firstExpression),
                                              GenerateExpression(session,
                                                                 secondExpression));
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateIndexExpression(LRef<Driver::GS_Session> session,
                                                             AST::NodePtrLRef<AST::GS_IndexExpression> indexExpression) {
        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateCastExpression(LRef<Driver::GS_Session> session,
                                                            AST::NodePtrLRef<AST::GS_CastExpression> castExpression) {
        auto expression = castExpression->GetExpression();
        auto type = castExpression->GetType();

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateVariableUsingExpression(LRef<Driver::GS_Session> session,
                                                                     AST::NodePtrLRef<AST::GS_VariableUsingExpression> variableUsingExpression) {
        auto name = variableUsingExpression->GetName();

        auto llvmAllocaInstruction = _variables[name];

        return _builder.CreateLoad(llvmAllocaInstruction->getAllocatedType(),
                                   llvmAllocaInstruction,
                                   name.AsUTF8());
    }

    Ptr<llvm::Value> GS_LLVMVisitor::GenerateFunctionCallingExpression(LRef<Driver::GS_Session> session,
                                                                       AST::NodePtrLRef<AST::GS_FunctionCallingExpression> functionCallingExpression) {
        auto name = functionCallingExpression->GetName();
        auto params = functionCallingExpression->GetArguments();

        auto llvmFunction = GetModule().getFunction(name.AsUTF8());

        std::vector<llvm::Value *> arguments;
        for (U64 index = 0; index < llvmFunction->arg_size(); ++index) {
            arguments.emplace_back(GenerateExpression(session,
                                                      params[index]));
        }

        return _builder.CreateCall(llvmFunction, arguments);
    }

    LRef<llvm::LLVMContext> GS_LLVMVisitor::GetContext() {
        return _codeHolder.GetContext();
    }

    LRef<llvm::Module> GS_LLVMVisitor::GetModule() {
        return _codeHolder.GetModule();
    }

}
