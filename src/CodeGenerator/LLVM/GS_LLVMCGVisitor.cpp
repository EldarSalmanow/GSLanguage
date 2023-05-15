#include <LLVM/GS_LLVMCGVisitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    // TODO update

    Ptr<llvm::Type> ToLLVMType(Semantic::GSTypePtr type, LRef<llvm::LLVMContext> context) {
        auto typeName = type->GetName();

        if (typeName == "Void"_us) {
            return llvm::Type::getVoidTy(context);
        } else if (typeName == "I32"_us) {
            return llvm::Type::getInt32Ty(context);
        } else if (typeName == "String"_us) {
            return llvm::Type::getInt8PtrTy(context);
        }

        return nullptr;
    }

    Ptr<llvm::Constant> ToLLVMConstant(AST::GSValuePtr value, LRef<llvm::LLVMContext> context, LRef<llvm::IRBuilder<>> builder) {
        auto literalValue = AST::ToValue<AST::GS_LiteralValue>(std::move(value));

        auto type = literalValue->GetType();

        auto typeName = type->GetName();

        Ptr<llvm::Type> llvmType;

        if (typeName == "I32"_us) {
            auto number = literalValue->GetValueWithCast<I32>();

            return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), number);
        } else if (typeName == "String"_us) {
            auto string = literalValue->GetValueWithCast<UString>();

            return builder.CreateGlobalStringPtr(string.AsUTF8());
        }

        return nullptr;
    }

    GS_LLVMCGVisitor::GS_LLVMCGVisitor(LRef<GS_LLVMCodeHolder> codeHolder)
            : _codeHolder(codeHolder),
              _builder(_codeHolder.GetContext()) {}

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateNode(LRef<Driver::GS_Session> session,
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

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateDeclaration(LRef<Driver::GS_Session> session,
                                                           LRef<AST::GSDeclarationPtr> declaration) {
        switch (declaration->GetDeclarationType()) {
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

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateStatement(LRef<Driver::GS_Session> session,
                                                         LRef<AST::GSStatementPtr> statement) {
        switch (statement->GetStatementType()) {
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

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateExpression(LRef<Driver::GS_Session> session,
                                                          LRef<AST::GSExpressionPtr> expression) {
        switch (expression->GetExpressionType()) {
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

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateTranslationUnitDeclaration(LRef<Driver::GS_Session> session,
                                                                          AST::NodePtrLRef<AST::GS_TranslationUnitDeclaration> translationUnitDeclaration) {
        auto name = translationUnitDeclaration->GetName();
        auto nodes = translationUnitDeclaration->GetNodes();

        _codeHolder.CreateModule(name);

        for (auto &node : nodes) {
            GenerateNode(session,
                         node);
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateFunctionDeclaration(LRef<Driver::GS_Session> session,
                                                                   AST::NodePtrLRef<AST::GS_FunctionDeclaration> functionDeclaration) {
        auto name = functionDeclaration->GetName();
        auto signature = functionDeclaration->GetSignature();
        auto body = functionDeclaration->GetBody();

        auto paramTypes = signature.GetParamTypes();
        auto returnType = signature.GetReturnType();

        std::vector<Ptr<llvm::Type>> llvmParamTypes;

        for (auto &paramType : paramTypes) {
            llvmParamTypes.emplace_back(ToLLVMType(paramType, GetContext()));
        }

        auto llvmReturnType = ToLLVMType(returnType, GetContext());

        auto llvmFunctionType = llvm::FunctionType::get(llvmReturnType, llvmParamTypes, false);

        auto llvmFunction = llvm::Function::Create(llvmFunctionType, llvm::Function::LinkageTypes::ExternalLinkage, name.AsUTF8(), GetModule());

        auto block = llvm::BasicBlock::Create(GetContext(), "entry", llvmFunction);

        _builder.SetInsertPoint(block);

        for (auto &statement : body) {
            GenerateStatement(session,
                              statement);
        }

        _builder.CreateRetVoid();

        return llvmFunction;
    }

    std::vector<std::pair<UString, Ptr<llvm::AllocaInst>>> Variables;

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                                                            AST::NodePtrLRef<AST::GS_VariableDeclarationStatement> variableDeclarationStatement) {
        auto name = variableDeclarationStatement->GetName();
        auto type = variableDeclarationStatement->GetType();
        auto expression = variableDeclarationStatement->GetExpression();

        auto typeName = type->GetName();

        Ptr<llvm::Type> llvmType;

        if (typeName == "I32"_us) {
            llvmType = llvm::Type::getInt32Ty(GetContext());
        } else {
            return nullptr;
        }

        auto llvmAllocaInstruction = _builder.CreateAlloca(llvmType);

        Variables.emplace_back(std::make_pair(name, llvmAllocaInstruction));

        return _builder.CreateStore(GenerateExpression(session,
                                                       expression),
                                    llvmAllocaInstruction);
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateAssignmentStatement(LRef<Driver::GS_Session> session,
                                                                   AST::NodePtrLRef<AST::GS_AssignmentStatement> assignmentStatement) {
        auto lvalueExpression = assignmentStatement->GetLValueExpression();
        auto rvalueExpression = assignmentStatement->GetRValueExpression();

        return _builder.CreateStore(GenerateExpression(session,
                                                       lvalueExpression),
                                    GenerateExpression(session,
                                                       rvalueExpression));
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateExpressionStatement(LRef<Driver::GS_Session> session,
                                                                   AST::NodePtrLRef<AST::GS_ExpressionStatement> expressionStatement) {
        auto expression = expressionStatement->GetExpression();

        return GenerateExpression(session,
                                  expression);
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateConstantExpression(LRef<Driver::GS_Session> session,
                                                                  AST::NodePtrLRef<AST::GS_ConstantExpression> constantExpression) {
        auto value = constantExpression->GetValue();

        return ToLLVMConstant(value, GetContext(), _builder);
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateUnaryExpression(LRef<Driver::GS_Session> session,
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

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateBinaryExpression(LRef<Driver::GS_Session> session,
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

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateArrayExpression(LRef<Driver::GS_Session> session,
                                                               AST::NodePtrLRef<AST::GS_ArrayExpression> arrayExpression) {
        // TODO

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateVariableUsingExpression(LRef<Driver::GS_Session> session,
                                                                       AST::NodePtrLRef<AST::GS_VariableUsingExpression> variableUsingExpression) {
        auto name = variableUsingExpression->GetName();

        Ptr<llvm::AllocaInst> llvmAllocaInstruction;

        for (auto &pair : Variables) {
            if (name == pair.first) {
                llvmAllocaInstruction = pair.second;

                break;
            }
        }

        return _builder.CreateLoad(llvmAllocaInstruction->getAllocatedType(), llvmAllocaInstruction, name.AsUTF8());
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateFunctionCallingExpression(LRef<Driver::GS_Session> session,
                                                                         AST::NodePtrLRef<AST::GS_FunctionCallingExpression> functionCallingExpression) {
        auto name = functionCallingExpression->GetName();

        auto llvmFunction = GetModule().getFunction(name.AsUTF8());

        if (llvmFunction != nullptr) {
            return _builder.CreateCall(llvmFunction);
        }

        return nullptr;
    }

    LRef<llvm::LLVMContext> GS_LLVMCGVisitor::GetContext() {
        return _codeHolder.GetContext();
    }

    LRef<llvm::Module> GS_LLVMCGVisitor::GetModule() {
        return _codeHolder.GetModule();
    }

}
