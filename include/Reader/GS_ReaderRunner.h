#ifndef GSLANGUAGE_GS_READERRUNNER_H
#define GSLANGUAGE_GS_READERRUNNER_H

#include <Starter/GS_Runnable.h>

#include <Reader/GS_Reader.h>

namespace GSLanguageCompiler::Reader {

    class GS_ReaderRunner : public Starter::GS_Runnable {
    public:

        GS_ReaderRunner();

    public:

        Void run(Starter::GSContextPtr &context) override;
    };

}

#endif //GSLANGUAGE_GS_READERRUNNER_H
