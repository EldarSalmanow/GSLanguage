#ifndef GSLANGUAGE_GS_TABLEOFSYMBOLSDUMPER_H
#define GSLANGUAGE_GS_TABLEOFSYMBOLSDUMPER_H

#include <Semantic/GS_TableOfSymbols.h>

#include <Debug/GS_Dumper.h>

namespace GSLanguageCompiler::Debug {

    /**
     * Class for dumping table of symbols
     */
    class GS_TableOfSymbolsDumper : public GS_Dumper {
    public:

        /**
         * Constructor for table of symbols dumper
         * @param tableOfSymbols Table of symbols dumper
         */
        explicit GS_TableOfSymbolsDumper(Semantic::GSTableOfSymbolsPtr tableOfSymbols);

    public:

        /**
         * Creating table of symbols dumper
         * @param tableOfSymbols Table of symbols
         * @return Table of symbols dumper ptr
         */
        static std::shared_ptr<GS_TableOfSymbolsDumper> Create(Semantic::GSTableOfSymbolsPtr tableOfSymbols);

    public:

        /**
         * Dump table of symbols
         * @return
         */
        Void Dump() override;

    private:

        /**
         * Table of symbols
         */
        Semantic::GSTableOfSymbolsPtr _tableOfSymbols;
    };

    /**
     * Dump table of symbols
     * @param tableOfSymbols Table of symbols
     * @return
     */
    Void DumpTableOfSymbols(Semantic::GSTableOfSymbolsPtr tableOfSymbols);

}

#endif //GSLANGUAGE_GS_TABLEOFSYMBOLSDUMPER_H
