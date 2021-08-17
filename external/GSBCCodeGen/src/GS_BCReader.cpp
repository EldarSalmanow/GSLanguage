#include <GS_BCReader.h>

namespace GSBCCodeGen {

    GS_BCReader::GS_BCReader(GSString filename)
            : _filename(std::move(filename)) {}

    GSByteCode GS_BCReader::read() {
        std::ifstream stream;

        stream.open(_filename, std::ios::binary);

        if (!stream.is_open()) {
            throw std::runtime_error("Can`t open file!");
        }

        GSByteCode bytecode;

        GSChar symbol;

        while (true) {
            stream.get(symbol);

            if (stream.eof()) {
                break;
            }

            bytecode.emplace_back(static_cast<GSByte>(symbol));
        }

        stream.close();

        return bytecode;
    }

}
