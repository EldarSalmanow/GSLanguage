#ifndef GSLANGUAGE_GS_VMIMAGE_H
#define GSLANGUAGE_GS_VMIMAGE_H

#include <CrossPlatform/GS_ClassUtilities.h>

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
         * @param byte
         * @return
         */
        GSVoid emitValue(GSByte byte);

    public:

        /**
         *
         * @return
         */
        GETTER(GSByteCode, bytecode, ByteCode)

    private:

        /**
         *
         */
        GSByteCode _bytecode;
    };

}

#endif //GSLANGUAGE_GS_VMIMAGE_H
