#include <GS_BCCompiler.h>

namespace GSBCCodeGen {

    GS_BCCompiler::GS_BCCompiler()
            : _rootNode(new GS_BCRootNode()), _blockNode(new GS_BCBlockNode()) {
        _rootNode->setNode(_blockNode);
    }

    GSByteCode GS_BCCompiler::createBytecode() {
        GS_BCCodeGenVisitor visitor;

        visitor.visit(_rootNode);

        return visitor.getBytecode();
    }

    GSVoid GS_BCCompiler::createConstant(GSInt id, GSString string) {
        _blockNode->addNode(_builder.createConstant(id, std::move(string)));
    }

    GSVoid GS_BCCompiler::createVariable(GSInt id, GSString name) {
        _blockNode->addNode(_builder.createVariable(id, std::move(name)));
    }

    GSVoid GS_BCCompiler::createPush(GSInt value) {
        _blockNode->addNode(_builder.createPush(value));
    }

    GSVoid GS_BCCompiler::createPop() {
        _blockNode->addNode(_builder.createPop());
    }

    GSVoid GS_BCCompiler::createPushConstant(GSInt id) {
        _blockNode->addNode(_builder.createPushConstant(id));
    }

    GSVoid GS_BCCompiler::createToReg(GSInt registerNumber) {
        _blockNode->addNode(_builder.createToReg(registerNumber));
    }

    GSVoid GS_BCCompiler::createFromReg(GSInt registerNumber) {
        _blockNode->addNode(_builder.createFromReg(registerNumber));
    }

    GSVoid GS_BCCompiler::createSave(GSInt variableId) {
        _blockNode->addNode(_builder.createSave(variableId));
    }

    GSVoid GS_BCCompiler::createGet(GSInt variableId) {
        _blockNode->addNode(_builder.createGet(variableId));
    }

    GSVoid GS_BCCompiler::createCall(GSInt functionId) {
        _blockNode->addNode(_builder.createCall(functionId));
    }

    GSVoid GS_BCCompiler::createAdd() {
        _blockNode->addNode(_builder.createAdd());
    }

    GSVoid GS_BCCompiler::createSub() {
        _blockNode->addNode(_builder.createSub());
    }

    GSVoid GS_BCCompiler::createMul() {
        _blockNode->addNode(_builder.createMul());
    }

    GSVoid GS_BCCompiler::createDiv() {
        _blockNode->addNode(_builder.createDiv());
    }

    GSVoid GS_BCCompiler::createDone() {
        _blockNode->addNode(_builder.createDone());
    }

    GS_BCRootNode *GS_BCCompiler::getRootNode() {
        return _rootNode;
    }

}
