#ifndef GSLANGUAGE_GS_VMIMAGE_H
#define GSLANGUAGE_GS_VMIMAGE_H

#include <CodeGenerator/GS_Opcode.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     *
     */
    class GS_VMImage {
    public:

        /**
         *
         */
        GS_VMImage();

    public:

        /**
         *
         * @param opcode
         * @return
         */
        GSVoid emitOpcode(Opcode opcode);

        /**
         *
         * @param index
         * @param value
         * @return
         */
        GSVoid emitConstantValue(GSInt index, GSInt value);

        /**
         *
         * @param index
         * @param variableName
         * @return
         */
        GSVoid emitVariable(GSInt index, GSString variableName);

        /**
         *
         * @param byte
         * @return
         */
        GSVoid emitValue(GSByte byte);

    public:

        /**
         *
         * @return
         */
        GSByteCode getByteCode();

    private:

        /**
         *
         */
        GSByteCode _constantTable;

        /**
         *
         */
        GSByteCode _variablesTable;

        /**
         *
         */
        GSByteCode _bytecode;
    };

}

#endif //GSLANGUAGE_GS_VMIMAGE_H
