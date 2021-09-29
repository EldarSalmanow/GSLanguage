#include <GS_ReaderRunner.h>

namespace GSLanguageCompiler::Reader {

    GS_ReaderRunner::GS_ReaderRunner() = default;

    GSVoid GS_ReaderRunner::run(Starter::GSContextPtr &context) {
        auto filename = context->getArguments()->getInputFilename();

        IFStream stream;

        GS_Reader reader(std::move(stream), filename);

        auto code = reader.read();

        context->setInputCode(code);
    }

}
