#include <GS_BCCompiler.h>

namespace GSBCCodeGen {

    GS_BCCompiler::GS_BCCompiler()
            : _rootNode(new GS_BCRootNode()), _blockNode(new GS_BCBlockNode()) {
        _rootNode->setNode(_blockNode);
    }

    GSByteCode GS_BCCompiler::createBytecode() {
        GS_BCLabelVisitor labelVisitor;

        _rootNode->accept(&labelVisitor);

        GS_BCCodeGenVisitor codegenVisitor(labelVisitor.getLabelsTable());

        _rootNode->accept(&codegenVisitor);

        return codegenVisitor.getBytecode();
    }

    GSVoid GS_BCCompiler::createConstant(GSInt id, GSString string) {
        _blockNode->addNode(_builder.createConstant(*_builder.createInt(id), *_builder.createString(std::move(string))));
    }

    GSVoid GS_BCCompiler::createVariable(GSInt id, GSString name) {
        _blockNode->addNode(_builder.createVariable(*_builder.createInt(id), *_builder.createString(std::move(name))));
    }

    GSVoid GS_BCCompiler::createPush(GSInt value) {
        _blockNode->addNode(_builder.createPush(*_builder.createInt(value)));
    }

    GSVoid GS_BCCompiler::createPush(GSString value) {
        _blockNode->addNode(_builder.createPush(*_builder.createString(std::move(value))));
    }

    GSVoid GS_BCCompiler::createPop() {
        _blockNode->addNode(_builder.createPop());
    }

    GSVoid GS_BCCompiler::createToReg(GSInt registerNumber) {
        _blockNode->addNode(_builder.createToReg(*_builder.createInt(registerNumber)));
    }

    GSVoid GS_BCCompiler::createFromReg(GSInt registerNumber) {
        _blockNode->addNode(_builder.createFromReg(*_builder.createInt(registerNumber)));
    }

    GSVoid GS_BCCompiler::createSave(GSInt variableId) {
        _blockNode->addNode(_builder.createSave(*_builder.createInt(variableId)));
    }

    GSVoid GS_BCCompiler::createGet(GSInt variableId) {
        _blockNode->addNode(_builder.createGet(*_builder.createInt(variableId)));
    }

    GSVoid GS_BCCompiler::createCmp() {
        _blockNode->addNode(_builder.createCmp());
    }

    GSVoid GS_BCCompiler::createJmp(GS_BCLabelNode *label) {
        _blockNode->addNode(_builder.createJmp(*label));
    }

    GSVoid GS_BCCompiler::createJie(GS_BCLabelNode *label) {
        _blockNode->addNode(_builder.createJie(*label));
    }

    GSVoid GS_BCCompiler::createJine(GS_BCLabelNode *label) {
        _blockNode->addNode(_builder.createJine(*label));
    }

    GSVoid GS_BCCompiler::createJig(GS_BCLabelNode *label) {
        _blockNode->addNode(_builder.createJig(*label));
    }

    GSVoid GS_BCCompiler::createJil(GS_BCLabelNode *label) {
        _blockNode->addNode(_builder.createJil(*label));
    }

    GSVoid GS_BCCompiler::createJieg(GS_BCLabelNode *label) {
        _blockNode->addNode(_builder.createJieg(*label));
    }

    GSVoid GS_BCCompiler::createJiel(GS_BCLabelNode *label) {
        _blockNode->addNode(_builder.createJiel(*label));
    }

    GSVoid GS_BCCompiler::createCall(GSInt functionId) {
        _blockNode->addNode(_builder.createCall(*_builder.createInt(functionId)));
    }

    GSVoid GS_BCCompiler::createI2s() {
        _blockNode->addNode(_builder.createI2s());
    }

    GSVoid GS_BCCompiler::createS2i() {
        _blockNode->addNode(_builder.createS2i());
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

    GS_BCLabelNode *GS_BCCompiler::createLabel(GSString name) {
        return _builder.createLabel(*_builder.createString(std::move(name)));
    }

    GSVoid GS_BCCompiler::bindLabel(GS_BCLabelNode *label) {
        _blockNode->addNode(label);
    }

    GS_BCRootNode *GS_BCCompiler::getRootNode() {
        return _rootNode;
    }

}
