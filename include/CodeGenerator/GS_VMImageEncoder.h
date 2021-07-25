#ifndef GSLANGUAGE_GS_VMIMAGEENCODER_H
#define GSLANGUAGE_GS_VMIMAGEENCODER_H

#include <CodeGenerator/GS_Opcode.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     *
     */
    class GS_VMImageEncoder {
    public:

        /**
         *
         */
        GS_VMImageEncoder();

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
        GSVoid emitNumberConstant(GSInt index, GSInt value);

        /**
         *
         * @param index
         * @param value
         * @return
         */
        GSVoid emitStringConstant(GSInt index, GSString value);

        /**
         *
         * @param index
         * @param variableName
         * @return
         */
        GSVoid emitNumberVariable(GSInt index, GSString variableName);

        /**
         *
         * @param index
         * @param variableName
         * @return
         */
        GSVoid emitStringVariable(GSInt index, GSString variableName);

        /**
         *
         * @param index
         * @param functionName
         * @return
         */
        GSVoid emitFunction(GSInt index, GSString functionName);

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
        GSByteCode _variableTable;

        /**
         *
         */
        GSByteCode _functionTable;

        /**
         *
         */
        GSByteCode _bytecode;
    };

}

#endif //GSLANGUAGE_GS_VMIMAGEENCODER_H
