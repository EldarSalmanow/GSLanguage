#ifndef GSLANGUAGE_GS_WRITER_H
#define GSLANGUAGE_GS_WRITER_H

#include <Driver/GS_Session.h>

namespace GSLanguageCompiler {

    namespace CodeGenerator {

        class GS_CodeHolder;

        using GSCodeHolderPtr = std::shared_ptr<GS_CodeHolder>;

        class GS_CGBackend;

        using GSCGBackendPtr = std::shared_ptr<GS_CGBackend>;

    }

    namespace IO {

        class GS_Writer {
        public:

            GS_Writer(LRef<Driver::GS_Session> session,
                      CodeGenerator::GSCGBackendPtr backend);

        public:

            Void Write(UString fileName,
                       CodeGenerator::GSCodeHolderPtr codeHolder);
        };

    }

}

#endif //GSLANGUAGE_GS_WRITER_H
